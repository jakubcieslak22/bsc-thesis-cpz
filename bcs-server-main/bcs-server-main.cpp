#include <iostream>

#include "MyServer.h"

#include "DBTools.h"

int main()
{
	MyServer::Create(9999, ptTest);
}
