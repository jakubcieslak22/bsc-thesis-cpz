#pragma once

#ifndef PACKETS_H
#define PACKETS_H

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

enum PacketType
{
	ptDefault = 0
};

struct DefaultPacket
{
	std::string date; // Data
	std::string time; // Godzina
	int temp; // Temperatura
	int ps; // Ciœnienie atmosferyczne
	int lum; // Natê¿enie œwiat³a
	int humGnd; // Wilgotnoœæ gle	by
	int humAir; // Wilgotnoœæ powietrza
	int prec; // Intensywnoœæ opadów
	int wspd; // Prêdkoœæ wiatru
};

inline bool ConstructDefaultPacket(DefaultPacket& pkt, std::string req)
{
	std::vector<std::string> vSegments;
	size_t pos = 0;
	std::string segment;
	
	while ((pos = req.find(';')) != std::string::npos)
	{
		segment = req.substr(0, pos);
		vSegments.emplace_back(segment);
		req.erase(0, pos + 1);
	}
	vSegments.emplace_back(req);

	if ((int)vSegments.size() != 9)
		return false;

	try
	{
		pkt.date = vSegments[0];
		pkt.time = vSegments[1];
		pkt.temp = std::stoi(vSegments[2]);
		pkt.ps = std::stoi(vSegments[3]);
		pkt.lum = std::stoi(vSegments[4]);
		pkt.humGnd = std::stoi(vSegments[5]);
		pkt.humAir = std::stoi(vSegments[6]);
		pkt.prec = std::stoi(vSegments[7]);
		pkt.wspd = std::stoi(vSegments[8]);
	}
	catch (...)
	{
		return false;
	}

	return true;
}

#endif //PACKETS_H