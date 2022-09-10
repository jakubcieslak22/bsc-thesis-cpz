#include <iostream>

#include "MyServer.h"

#define _USING_SQL
#include "DBTools.h"

int main()
{
	MyServer::Create(9999, ptDefault);
}
