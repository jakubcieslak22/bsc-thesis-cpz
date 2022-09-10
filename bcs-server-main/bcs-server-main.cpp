#include <iostream>

#include "MyServer.h"

#include "DBTools.h"

int main()
{
	if (!DBTools::init())
		std::cout << "Failed to connect to MySQL" << std::endl;
	else
		std::cout << "Connected to MySQL" << std::endl;

	MyServer::Create(9999);
}
