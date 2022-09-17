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
#define MYSQL_TBNAME "pomiary_test"

namespace DBTools
{
	namespace
	{
		MYSQL* Session; // pola "prywatne"
		bool bInitialized = false; 
	}

	// #ifdef _USING_SQL w kazdej funkcji zeby dalo sie odpalic bez zainstalowanego MySQL

	bool init();
	bool fetchData(std::vector<std::pair<int, DefaultPacket> >& vPackets);
	bool putData(const DefaultPacket& Packet);
	
	bool fetchDataTest(std::vector<std::pair<int, TestPacket> >& vPackets);
	bool putDataTest(const TestPacket& Packet);
}

#endif //DBTOOLS_H