#pragma once
#ifndef MYSERVER_H
#define MYSERVER_H

#define CROW_JSON_USE_MAP
#include "crow.h"

#include <fstream>

#include "Windows.h"

#include "DBTools.h"
#include "HTMLTools.h"
#include "JSONTools.h"
#include "packets.h"

#define DEFAULT_INDEX_ROUTE "/"
#define DEFAULT_GRAPHS_ROUTE "/graphs/"
#define DEFAULT_JSON_ROUTE "/json/"
#define DEFAULT_JSON_ROUTE_RAW "/json/raw/"
#define DEFAULT_FAVICON_ROUTE "/favicon.ico"

namespace MyServer
{
	namespace // prywatne pole aktualizowane przy otrzymaniu POST
	{
		std::vector <std::pair <int, MeasurementsPacket> > vCachedPackets;
	}

	inline std::string GetMethod()
	{
		std::vector<std::pair<int, MeasurementsPacket> > vPackets;
		if (!DBTools::fetchMeasurementData(vPackets))
			return "Blad komunikacji z baza danych.";

		return HTMLTools::drawMeasurementsTable(vPackets);
	}

	inline std::string PostMethod(const crow::request& xReq)
	{
		CROW_LOG_INFO << "Packet received: " << xReq.body;
		MeasurementsPacket Pkt;
		if (ConstructMeasurementPacket(Pkt, xReq.body))
		{
			if (DBTools::putMeasurementData(Pkt))
			{
				CROW_LOG_INFO << "Data placed in database.";
				if (JSONTools::packJSON(vCachedPackets))
					return std::string("RES: recv + acc");
				else
					CROW_LOG_ERROR << "Failed to pack JSON file.";
			}
			else
				CROW_LOG_ERROR << "Could not send data to database.";
		}
		else
			CROW_LOG_ERROR << "Failed to construct packet from request: " << xReq.body;

		return std::string("RES: recv + err");
	}

	/**
	* @brief Inicjalizuje i uruchamia serwer
	* @param iPort - nr portu, na ktorym ma sluchac serwer
	*/
	inline void Initialize(int iPort)
	{
		crow::SimpleApp App;

		char szBuf[_MAX_DIR] = {};
		GetCurrentDirectoryA(sizeof(szBuf), szBuf);

		std::string sDir = szBuf;
		sDir += "\\html\\";

		crow::mustache::set_global_base(sDir);

		JSONTools::packJSON(vCachedPackets);

		CROW_ROUTE(App, DEFAULT_INDEX_ROUTE).methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&](const crow::request& req)
			{
				if (req.method == crow::HTTPMethod::GET)
				{
					auto mainPage = crow::mustache::load_unsafe("index.html");
					return mainPage.render();
				}
				else if (req.method == crow::HTTPMethod::POST)
				{
					PostMethod(req);
					return crow::mustache::rendered_template();
				}
			});

		CROW_ROUTE(App, DEFAULT_GRAPHS_ROUTE).methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&](const crow::request& req)
			{
				if (req.method == crow::HTTPMethod::GET)
				{
					auto mainPage = crow::mustache::load_unsafe("graphs.html");
					return mainPage.render();
				}
				else if (req.method == crow::HTTPMethod::POST)
				{
					PostMethod(req);
					return crow::mustache::rendered_template();
				}
			});

		CROW_ROUTE(App, DEFAULT_JSON_ROUTE)([]
			{
				crow::json::wvalue::list xList;
		for (const auto& pair : vCachedPackets)
		{

			auto pkt = pair.second;

			std::string sWspd;

			std::string sPrec;
			std::string sHumGnd1;
			std::string sHumGnd2;
			std::string sHumGnd3;

			switch (pkt.iPrec)
			{
			case 0: sPrec = "Brak opadow"; break;
			case 1: sPrec = "Lekkie opady"; break;
			case 2: sPrec = "Umiarkowane opady"; break;
			case 3: sPrec = "Silne opady"; break;
			default: sPrec = "Niepoprawny pomiar";
			}

			switch (pkt.iWspd)
			{
			case 0: sWspd = "Brak wiatru"; break;
			case 1: sWspd = "Lekki wiatr"; break;
			case 2: sWspd = "Umiarkowany wiatr"; break;
			case 3: sWspd = "Silny wiatr"; break;
			default: sWspd = "Niepoprawny pomiar";
			}

			switch (pkt.iHumGnd1)
			{
			case 0: sHumGnd1 = "Gleba sucha"; break;
			case 1: sHumGnd1 = "Gleba wilgotna"; break;
			case 2: sHumGnd1 = "Gleba mokra"; break;
			default: sHumGnd1 = "Niepoprawny pomiar";
			}
			switch (pkt.iHumGnd2)
			{
			case 0: sHumGnd2 = "Gleba sucha"; break;
			case 1: sHumGnd2 = "Gleba wilgotna"; break;
			case 2: sHumGnd2 = "Gleba mokra"; break;
			default: sHumGnd2 = "Niepoprawny pomiar";
			}
			switch (pkt.iHumGnd3)
			{
			case 0: sHumGnd3 = "Gleba sucha"; break;
			case 1: sHumGnd3 = "Gleba wilgotna"; break;
			case 2: sHumGnd3 = "Gleba mokra"; break;
			default: sHumGnd3 = "Niepoprawny pomiar";
			}

			crow::json::wvalue x = {
				{ "Nr pomiaru", pair.first },
				{ "Data pomiaru", pkt.sDate },
				{ "Godzina pomiaru", pkt.sTime },
				{ "Temperatura", pkt.fTemp },
				{ "Wilgotnosc powietrza", pkt.fHumAir },
				{ "Cisnienie atmosferyczne", pkt.iPs },
				{ "Natezenie swiatla", pkt.fLum },
				{ "Intensywnosc opadow", sPrec },
				{ "Predkosc wiatru", sWspd },
				{ "Wilgotnosc gleby (10cm)", sHumGnd1 },
				{ "Wilgotnosc gleby (30cm)", sHumGnd2 },
				{ "Wilgotnosc gleby (60cm)", sHumGnd3 },
				{ "Lokalizacja", pkt.sLocation }
			};
			xList.emplace_back(x);
		}
		crow::json::wvalue xJSON = xList;
		return xJSON;
			});

		CROW_ROUTE(App, DEFAULT_JSON_ROUTE_RAW)([]
			{
				std::ifstream hFile("html/json/measurements.json");
		std::string sLine, sContents = "";
		if (hFile.is_open())
			while (std::getline(hFile, sLine))
				sContents += sLine;
		hFile.close();
		return sContents;
			});

		CROW_ROUTE(App, DEFAULT_FAVICON_ROUTE)([sDir]() {
			crow::response resp = crow::response(200);
		resp.set_static_file_info(("img/favicon.png"));
		return resp;
			});

		App.port(iPort).multithreaded().run();
	}

	inline void Create()
	{
		int iPort = 0;
		std::ifstream hCfg("config.cfg");
		if (hCfg.is_open())
		{
			std::string sPort;
			std::getline(hCfg, sPort);
			iPort = std::atoi(sPort.c_str());
			hCfg.close();
		}

		if (!iPort)
			throw std::exception();

		if (!DBTools::init())
			std::cout << "Failed to connect to MySQL" << std::endl;
		else
			std::cout << "Connected to MySQL" << std::endl;

		MyServer::Initialize(iPort);
	}
}


#endif //MYSERVER_H
