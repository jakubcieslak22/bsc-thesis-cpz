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
//#define MYSQL_DBNAME "bsctest"
//#define MYSQL_TBNAME "measurements_november_test"
#define MYSQL_DBNAME "bsc_measurements"
//#define MYSQL_TBNAME "measurements__december_predeploy"
#define MYSQL_TBNAME "measurements"

namespace DBTools
{
	namespace // pola "prywatne"
	{
		MYSQL* Session;
		bool bInitialized = false; 
	}

	bool init();
	
	bool fetchMeasurementData(std::vector<std::pair<int, MeasurementsPacket> >& vPackets);
	bool putMeasurementData(const MeasurementsPacket& Packet);
}

#endif // DBTOOLS_H