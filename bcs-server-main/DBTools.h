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
#define MYSQL_TBNAME "bsctest"

namespace DBTools
{
	namespace
	{
		MYSQL* Session; // pola "prywatne"
		bool bInitialized = false; 
	}

	// #ifdef _USING_SQL w kazdej funkcji zeby dalo sie odpalic bez zainstalowanego MySQL

	bool init();
	bool fetchData(std::vector<DefaultPacket>& vPackets);
	bool putData(const DefaultPacket& Packet);
}

#endif //DBTOOLS_H