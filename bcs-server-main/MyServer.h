#pragma once
#ifndef MYSERVER_H
#define MYSERVER_H

//#define CROW_JSON_USE_MAP
#include "crow.h"

#include "Windows.h"

#include "DBTools.h"
#include "HTMLTools.h"
#include "JSONTools.h"
#include "packets.h"

#define DEFAULT_ROUTE "/"
#define DEFAULT_JSON_ROUTE "/json"
#define DEFAULT_JSON_ROUTE_RAW "/json/raw"

namespace MyServer
{
	inline std::string GetMethod()
	{
		std::vector<std::pair<int, MeasurementsPacket> > vPackets;
		if (!DBTools::fetchMeasurementData(vPackets))
			return "B³¹d komunikacji z baz¹ danych.";

		return HTMLTools::drawMeasurementsTable(vPackets);
	}

	inline std::string PostMethod(const crow::request& xReq)
	{
		CROW_LOG_INFO << "Packet received: " << xReq.body;
		MeasurementsPacket Pkt;
		if (ConstructTestPacket(Pkt, xReq.body))
		{
			if (DBTools::putMeasurementData(Pkt))
			{
				CROW_LOG_INFO << "Data placed in database.";
				if (JSONTools::packJSON())
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

		crow::mustache::set_global_base(sDir.c_str());

		JSONTools::packJSON();
	
		CROW_ROUTE(App, DEFAULT_ROUTE).methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&](const crow::request& req)
			{
				if (req.method == crow::HTTPMethod::GET)
				{
					auto mainPage = crow::mustache::load_unsafe("sample.html");
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
				std::vector<std::pair<int, MeasurementsPacket> > vPackets;
				if (!DBTools::fetchMeasurementData(vPackets))
					return crow::json::wvalue("B³¹d komunikacji z baz¹ danych");
				else
				{
					crow::json::wvalue::list xList;
					for (const auto& pair : vPackets)
					{

						auto pkt = pair.second;
						
						std::string sWspd;

						std::string sHumGnd1;
						std::string sHumGnd2;
						std::string sHumGnd3;
						
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
							{ "Intensywnosc opadow", pkt.fPrec },
							{ "Predkosc wiatru", sWspd },
							{ "Wilgotnosc gleby (10cm)", sHumGnd1 },
							{ "Wilgotnosc gleby (20cm)", sHumGnd2 },
							{ "Wilgotnosc gleby (30cm)", sHumGnd3 },
							{ "Lokalizacja", pkt.sLocation }
						};
						xList.emplace_back(x);
					}
					crow::json::wvalue xJSON = xList;
					return xJSON;
				}

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

		App.port(iPort).multithreaded().run();
	}

	inline void Create(int iPort)
	{
		if (!DBTools::init())
			std::cout << "Failed to connect to MySQL" << std::endl;
		else
			std::cout << "Connected to MySQL" << std::endl;

		MyServer::Initialize(iPort);
	}
}


#endif //MYSERVER_H
