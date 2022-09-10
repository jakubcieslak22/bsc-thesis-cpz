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
	time_t time; // Godzina
	int temp; // Temperatura
	int ps; // Ci�nienie atmosferyczne
	int lum; // Nat�enie �wiat�a
	int humGnd; // Wilgotno�� gleby
	int humAir; // Wilgotno�� powietrza
	int prec; // Intensywno�� opad�w
	int wspd; // Pr�dko�� wiatru
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

	try
	{
		pkt.date = vSegments[0];

		struct std::tm tm;
		std::istringstream ss(vSegments[1]);
		ss >> std::get_time(&tm, "%H:%M:%S");
		pkt.time = mktime(&tm);

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