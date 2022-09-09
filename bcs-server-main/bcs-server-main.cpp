#include <iostream>

#include "ServerBase.h"

std::string defaultRoute()
{
	return "This is the default route";
}

crow::json::wvalue jsonRoute()
{
	crow::json::wvalue ret;
	ret["line1"] = "this is line 1";
	ret["line2"] = "this is line 2";
	return ret;
}

int main()
{
	ServerBase Server(9999, false, false);
	Server.AddRoute(defaultRoute, defaultRoute);
	//Server.AddJSONRoute(jsonRoute); do poprawy
	Server.Run();
}
