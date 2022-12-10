#include <iostream>

#include "MyServer.h"

int main()
{
	try
	{
		MyServer::Create();
	}
	catch (std::exception)
	{
		std::cout << "Config file not found or corrupted. Exiting\n";
	}
}
