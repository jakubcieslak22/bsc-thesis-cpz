#pragma once
#ifndef MYSERVER_H
#define MYSERVER_H

#include "crow.h"
#include "DBTools.h"
#include "HTMLTools.h"
#include "packets.h"

#define DEFAULT_ROUTE "/"
#define DEFAULT_JSON_ROUTE "/json"

#define USE_HTML

namespace MyServer
{
	inline std::string GetMethod(PacketType ptType)
	{
		if (ptType == ptDefault)
		{
			std::vector<std::pair<int, DefaultPacket> > vPackets;
			if (!DBTools::fetchData(vPackets))
				return "B³¹d komunikacji z baz¹ danych.";

			return HTMLTools::drawTable(vPackets);
		}
		else if (ptType == ptTest)
		{
			std::vector<std::pair<int, TestPacket> > vPackets;
			if (!DBTools::fetchDataTest(vPackets))
				return "B³¹d komunikacji z baz¹ danych.";

			return HTMLTools::drawTestTable(vPackets);
		}
	}

	inline std::string PostMethod(const crow::request& req, PacketType ptType)
	{
		CROW_LOG_INFO << "Packet received: " << req.body;
		if (ptType == ptDefault)
		{
			DefaultPacket Pkt;
			if (ConstructDefaultPacket(Pkt, req.body))
			{
				if (DBTools::putData(Pkt))
				{
					CROW_LOG_INFO << "Data placed in database.";
					return std::string("RES: recv + acc");
				}
				else
					CROW_LOG_ERROR << "Could not send data to database.";
			}
			else
				CROW_LOG_ERROR << "Failed to construct packet from request: " << req.body;
		}
		else if (ptType == ptTest)
		{
			TestPacket Pkt;
			if (ConstructTestPacket(Pkt, req.body))
			{
				if (DBTools::putDataTest(Pkt))
				{
					CROW_LOG_INFO << "Data placed in database.";
					return std::string("RES: recv + acc");
				}
				else
					CROW_LOG_ERROR << "Could not send data to database.";
			}
			else
				CROW_LOG_ERROR << "Failed to construct packet from request: " << req.body;
		}

		return std::string("RES: recv + err");
	}

	/**
	* @brief Inicjalizuje i uruchamia serwer
	* @param iPort - nr portu, na ktorym ma sluchac serwer
	* @param ptType - rodzaj pakietu (domyslnie DefaultPacket)
	*/
	inline void Initialize(int iPort, PacketType ptType)
	{
		crow::SimpleApp App;
#ifndef USE_HTML
		CROW_ROUTE(App, DEFAULT_ROUTE).methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&](const crow::request& req)
			{
				if (req.method == crow::HTTPMethod::GET)
					return GetMethod(ptType);
				else if (req.method == crow::HTTPMethod::POST)
					return PostMethod(req, ptType);
			});
#else
		crow::mustache::set_global_base("C:\\Users\\kasax\\Desktop\\AiR\\ROK 4\\Sem 7\\INZYNIERKA\\bsc-thesis-cpz-main\\bcs-server-main\\html\\");
		CROW_ROUTE(App, "/")([]()
			{
				crow::mustache::context ctx;
				auto mainPage = crow::mustache::load_unsafe("sample.html");
				return mainPage.render();
			});
#endif

		CROW_ROUTE(App, DEFAULT_JSON_ROUTE)([]
			{
				crow::json::wvalue x({ {"message", "Hello, World!"}, {"field2", "whatsup" } });
				//x["message2"] = "Hello, World.. Again!";
				return x;
			});

		App.port(iPort).multithreaded().run();
	}

	inline void Create(int iPort, PacketType ptType = ptDefault)
	{
		if (!DBTools::init())
			std::cout << "Failed to connect to MySQL" << std::endl;
		else
			std::cout << "Connected to MySQL" << std::endl;

		MyServer::Initialize(iPort, ptType);
	}
}


#endif //MYSERVER_H
