#include <iostream>
#include "crow.h"

int main()
{
	crow::SimpleApp app;
	CROW_ROUTE(app, "/")([]()
		{
			return "Hello world!";
		});

	app.port(9999).multithreaded().run();
}
