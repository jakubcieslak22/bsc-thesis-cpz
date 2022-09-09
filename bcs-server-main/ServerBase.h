#pragma once
#ifndef SERVERBASE_H
#define SERVERBASE_H

#include <string>

#include "crow.h"

typedef std::string (*server_fun_string)(void);
typedef crow::json::wvalue (*server_fun_json)(void);

enum ServerRetCode: int
{
	srcSuccess = 0,
	srcError,
	srcUnknown
};

class ServerBase
{
protected:
	int m_iPort;
	crow::SimpleApp m_app;

	std::string serverExecuteFun();

public:
	ServerBase(int _iPort, bool _bDefaultRouting, bool _bInitRunning);

	ServerRetCode AddRoute(server_fun_string fun, server_fun_string fun_get);
	ServerRetCode AddJSONRoute(server_fun_json fun);
	void Run();
};

#endif //SERVERBASE_H
