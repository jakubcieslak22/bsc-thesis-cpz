#pragma once
#ifndef MYSERVER_H
#define MYSERVER_H

#include "crow.h"
#include "DBTools.h"
#include "packets.h"

#define DEFAULT_ROUTE "/"
#define DEFAULT_JSON_ROUTE "/json"

namespace MyServer
{
	inline std::string SimpleGet()
	{
		return "got";
	}

	/**
	* @brief Inicjalizuje i uruchamia serwer
	* @param iPort - nr portu, na ktorym ma sluchac serwer
	* @param ptType - rodzaj pakietu (domyslnie DefaultPacket)
	*/
	inline void Create(int iPort, PacketType ptType = ptDefault)
	{
		crow::SimpleApp App;
		CROW_ROUTE(App, DEFAULT_ROUTE).methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&](const crow::request& req)
			{
				if (req.method == crow::HTTPMethod::GET)
					return SimpleGet();
				else if (req.method == crow::HTTPMethod::POST)
				{
					if (ptType == ptDefault)
					{
						CROW_LOG_INFO << "Packet received: " << req.body;
						DefaultPacket Pkt;
						bool res = ConstructDefaultPacket(Pkt, req.body);
						if (res)
						{
							if (!DBTools::putData(Pkt))
								CROW_LOG_ERROR << "Could not send data to database.";
							else
								CROW_LOG_INFO << "Data placed in database.";
						}
						else
							CROW_LOG_ERROR << "Failed to construct packet from request: " << req.body;

					}
					return std::string("RESPONSE: received");

				}
			});

		CROW_ROUTE(App, DEFAULT_JSON_ROUTE)([]
			{
				crow::json::wvalue x({ {"message", "Hello, World!"}, {"field2", "whatsup" } });
				//x["message2"] = "Hello, World.. Again!";
				return x;
			});

		App.port(iPort).multithreaded().run();
	}
}


#endif //MYSERVER_H
