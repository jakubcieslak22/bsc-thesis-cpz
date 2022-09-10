#include <iostream>

#include "MyServer.h"

#define _USING_SQL
#include "DBTools.h"

int main()
{
	if (!DBTools::init())
		CROW_LOG_ERROR << "Failed to connect to MySQL";
	MyServer::Create(9999);
}
