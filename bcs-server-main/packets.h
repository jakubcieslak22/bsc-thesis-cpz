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

struct DefaultPacket // Docelowa struktura: "dd.mm.rrrr;hh:mm;temp;ps;lum;humGnd;humAir;prec;wspd"
{
	std::string date; // Data
	std::string time; // Godzina
	float temp; // Temperatura
	float ps; // Ciœnienie atmosferyczne
	float lum; // Natê¿enie œwiat³a
	float humGnd; // Wilgotnoœæ gle	by
	float humAir; // Wilgotnoœæ powietrza
	float prec; // Intensywnoœæ opadów
	float wspd; // Prêdkoœæ wiatru
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
		pkt.temp = atof(vSegments[2].c_str());
		pkt.ps = atof(vSegments[3].c_str());
		pkt.lum = atof(vSegments[4].c_str());
		pkt.humGnd = atof(vSegments[5].c_str());
		pkt.humAir = atof(vSegments[6].c_str());
		pkt.prec = atof(vSegments[7].c_str());
		pkt.wspd = atof(vSegments[8].c_str());
	}
	catch (...)
	{
		return false;
	}

	return true;
}

#endif //PACKETS_H