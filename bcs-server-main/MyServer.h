#pragma once
#ifndef MYSERVER_H
#define MYSERVER_H

#include "crow.h"
#include "packets.h"

namespace MyServer
{
	std::string SimpleGet()
	{
		return "got";
	}

	void Create(int iPort, PacketType ptType)
	{
		crow::SimpleApp App;
		CROW_ROUTE(App, "/").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&](const crow::request& req)
			{
				if (req.method == crow::HTTPMethod::GET)
					return SimpleGet();
				else if (req.method == crow::HTTPMethod::POST)
				{
					if (ptType = ptDefault)
					{
						DefaultPacket Pkt;
						if (!ConstructDefaultPacket(Pkt, req.body))
							CROW_LOG_ERROR << "Failed to construct packet from request: " << req.body;
						else
							CROW_LOG_INFO << "Packet received: " << req.body;
					}
					return std::string("RESPONSE: received");

				}
			});

		CROW_ROUTE(App, "/json")([]
			{
				crow::json::wvalue x({ {"message", "Hello, World!"}, {"field2", "whatsup" } });
				//x["message2"] = "Hello, World.. Again!";
				return x;
			});

		App.port(iPort).multithreaded().run();
	}
}


#endif //MYSERVER_H
