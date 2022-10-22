#pragma once

#ifndef PACKETS_H
#define PACKETS_H

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

enum PacketType
{
	ptDefault = 0,
	ptTest
};

struct DefaultPacket // Docelowa struktura: "dd.mm.rrrr;hh:mm;temp;ps;lum;humGnd;humAir;prec;wspd"
{
	std::string date; // Data
	std::string time; // Godzina
	float temp; // Temperatura
	float ps; // Ci�nienie atmosferyczne
	float lum; // Nat�enie �wiat�a
	float humGnd; // Wilgotno�� gleby
	float humAir; // Wilgotno�� powietrza
	float prec; // Intensywno�� opad�w
	float wspd; // Pr�dko�� wiatru
};

struct TestPacket //curl -X POST -d "17.09.2022;11:05;14.3;18.3;970;10.23;2.04;2;30;20;10;cycki" localhost:9999
{
	std::string date = ""; // Data
	std::string time = ""; // Godzina
	float temp = 0; // Temperatura
	float humAir = 0; // Wilgotno�� powietrza
	float ps = 0; // Ci�nienie atmosferyczne
	float lum = 0; // Nat�enie �wiat�a
	float prec = 0; // Intensywno�� opad�w
	float wspd = 0; // Pr�dko�� wiatru
	float humGnd1 = 0; // Wilgotno�� gleby 10cm
	float humGnd2 = 0; // Wilgotno�� gleby 20cm
	float humGnd3 = 0; // Wilgotno�� gleby 30cm
	std::string location = "";
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

inline bool ConstructTestPacket(TestPacket& pkt, std::string req)
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

	if ((int)vSegments.size() != 12)
		return false;

	try
	{
		pkt.date = vSegments[0];
		pkt.time = vSegments[1];
		pkt.temp = atof(vSegments[2].c_str());
		pkt.humAir = atof(vSegments[3].c_str());
		pkt.ps = atof(vSegments[4].c_str());
		pkt.lum = atof(vSegments[5].c_str());
		pkt.prec = atof(vSegments[6].c_str());
		pkt.wspd = atof(vSegments[7].c_str());
		pkt.humGnd1 = atof(vSegments[8].c_str());
		pkt.humGnd2 = atof(vSegments[9].c_str());
		pkt.humGnd3 = atof(vSegments[10].c_str());
		pkt.location = vSegments[11];
	}
	catch (...)
	{
		return false;
	}

	return true;
}

#endif //PACKETS_H