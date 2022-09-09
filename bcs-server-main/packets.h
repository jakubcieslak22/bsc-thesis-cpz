#pragma once

#ifndef PACKETS_H
#define PACKETS_H

#include <string>
#include <vector>

struct TestPacket
{
	int num1 = 0;
	int num2 = 0;
	bool b1 = false;
	std::string s1 = "";
};

TestPacket TestPacketForm(std::string req)
{
	// przyjmijmy strukture taka: nazwa1=wartosc;nazwa2=wartosc itd.
	TestPacket Pkt;

	std::vector<std::string> vSegments;
	size_t pos = 0;
	std::string token;

	while ((pos = req.find(';')) != std::string::npos) 
	{
		token = req.substr(0, pos);
		vSegments.emplace_back(token);
		req.erase(0, pos + 1);
	}
	vSegments.emplace_back(req); // ostatni, bez srednikow

	for (const auto& item : vSegments)
	{
		std::string sKey = item.substr(0, item.find("="));
		if (sKey == "num1")
		{
			std::string sNum1 = item.substr(item.find("=") + 1, item.size());
			Pkt.num1 = std::stoi(sNum1);
		}
		else if (sKey == "num2")
		{
			std::string sNum2 = item.substr(item.find("=") + 1, item.size());
			Pkt.num2 = std::stoi(sNum2);
		}
		else if (sKey == "b1")
		{
			if (item.substr(item.find("=") + 1, item.size()) == "true")
				Pkt.b1 = true;
			else
				Pkt.b1 = false;
		}
		else if (sKey == "s1")
			Pkt.s1 = item.substr(item.find("=") + 1, item.size());
	}

	return Pkt;
}

#endif //PACKETS_H