#pragma once
#ifndef DBTOOLS_H
#define DBTOOLS_H

#include <vector>

#include "mysql.h"
#include "mysqlx/xdevapi.h"
#include "packets.h"

#define MYSQL_USER "root"
#define MYSQL_PASS "root"
#define MYSQL_HOST "localhost"
#define MYSQL_DBNAME "bsctest"
#define MYSQL_TBNAME "measurements_november_test"

namespace DBTools
{
	namespace // pola "prywatne"
	{
		MYSQL* Session;
		bool bInitialized = false; 
	}

	// #ifdef _USING_SQL w kazdej funkcji zeby dalo sie odpalic bez zainstalowanego MySQL

	bool init();
	
	bool fetchMeasurementData(std::vector<std::pair<int, MeasurementsPacket> >& vPackets);
	bool putMeasurementData(const MeasurementsPacket& Packet);
}

#endif // DBTOOLS_H