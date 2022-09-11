#include <iostream>

#include "MyServer.h"

#include "DBTools.h"

int main()
{
	if (!DBTools::init())
		CROW_LOG_ERROR << "Failed to connect to MySQL";
	else
		CROW_LOG_INFO << "Connected to MySQL";

	MyServer::Create(9999);
}
