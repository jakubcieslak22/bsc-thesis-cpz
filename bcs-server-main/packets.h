#pragma once

#ifndef PACKETS_H
#define PACKETS_H

#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

struct MeasurementsPacket //curl -X POST -d "00.00.0000;00:00;14.3;18.3;970;10.23;2.04;2;2;1;0;xxxxxxxxxPoznan" localhost:9999
{
	std::string sDate = ""; // Data
	std::string sTime = ""; // Godzina
	float fTemp = 0; // Temperatura
	float fHumAir = 0; // Wilgotnoœæ powietrza
	int iPs = 0; // Ciœnienie atmosferyczne
	float fLum = 0; // Natê¿enie œwiat³a
	int iPrec = 0; // Intensywnoœæ opadów
	int iWspd = 0; // Prêdkoœæ wiatru
	int iHumGnd1 = 0; // Wilgotnoœæ gleby 10cm
	int iHumGnd2 = 0; // Wilgotnoœæ gleby 20cm
	int iHumGnd3 = 0; // Wilgotnoœæ gleby 30cm
	std::string sLocation = ""; // Lokalizacja
};

inline bool ConstructMeasurementPacket(MeasurementsPacket& pkt, std::string req)
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
		auto t = std::time(nullptr);
#ifdef _CRT_SECURE_NO_WARNINGS
		auto tm = *std::localtime(&t);
#else
		struct tm tm;
		auto err = localtime_s(&tm, &t);
#endif
		std::stringstream ss;
		ss << std::put_time(&tm, "%d.%m.%Y|%H:%M") << std::endl;
		std::string sDateAndTime(ss.str());

		pkt.sDate = vSegments[0];
		if (pkt.sDate == std::string("00.00.0000"))
			pkt.sDate = sDateAndTime.substr(0, sDateAndTime.find('|'));
		
		pkt.sTime = vSegments[1];
		if (pkt.sTime == std::string("00:00"))
			pkt.sTime = sDateAndTime.substr(sDateAndTime.find('|') + 1);

		// rzutowanie na float, poniewaz atof zwraca double z jakiegos powodu (mimo, ze jest funkcja atod, ktora zwraca double)
		pkt.fTemp = static_cast<float>(atof(vSegments[2].c_str())); 
		pkt.fHumAir = static_cast<float>(atof(vSegments[3].c_str()));
		pkt.iPs = atoi(vSegments[4].c_str());
		pkt.fLum = static_cast<float>(atof(vSegments[5].c_str()));
		pkt.iPrec = atoi(vSegments[6].c_str());
		if (pkt.iPrec < 0 || pkt.iWspd > 3)
			return false;

		pkt.iWspd = atoi(vSegments[7].c_str());
		if (pkt.iWspd < 0 || pkt.iWspd > 3)
			return false;
		
		pkt.iHumGnd1 = atoi(vSegments[8].c_str());
		pkt.iHumGnd2 = atoi(vSegments[9].c_str());
		pkt.iHumGnd3 = atoi(vSegments[10].c_str());
		if ((pkt.iHumGnd1 < 0 || pkt.iHumGnd1 > 2) ||
			(pkt.iHumGnd2 < 0 || pkt.iHumGnd2 > 2) ||
			(pkt.iHumGnd3 < 0 || pkt.iHumGnd3 > 2))
			return false;

		std::string sLoc = vSegments[11];
		sLoc.erase(std::remove(sLoc.begin(), sLoc.end(), 'x'), sLoc.end());
		pkt.sLocation = sLoc;
	}
	catch (...)
	{
		return false;
	}

	return true;
}

#endif // PACKETS_H