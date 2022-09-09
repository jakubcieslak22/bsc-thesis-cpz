#include "ServerBase.h"

#include "packets.h"

std::string ServerBase::serverExecuteFun()
{
    return "Hello world!";
}

ServerBase::ServerBase(int _iPort, bool _bDefaultRouting, bool _bInitRunning) : m_iPort(_iPort)
{
    if (_bDefaultRouting)
    {
        CROW_ROUTE(m_app, "/")([&]() 
            {
            return serverExecuteFun();
            });
    }

    if (_bInitRunning)
        Run();
}

ServerRetCode ServerBase::AddRoute(server_fun_string fun_post, server_fun_string fun_get)
{
    auto ret = srcSuccess;
    CROW_ROUTE(m_app, "/").methods(crow::HTTPMethod::GET, crow::HTTPMethod::POST)([&](const crow::request& req)
        {
            if (req.method == crow::HTTPMethod::GET)
                return fun_get();
            else if (req.method == crow::HTTPMethod::POST)
            {
                TestPacket Pkt = TestPacketForm(req.body);
                std::cout << "[+] Packet received" << std::endl;
                std::cout << req.body << std::endl;
                return req.body;
            }
        });
    return ret;
}

ServerRetCode ServerBase::AddJSONRoute(server_fun_json fun)
{
    auto ret = srcSuccess;
    CROW_ROUTE(m_app, "/json")([&]() 
        {
            return fun();
        });
    return ret;
}

void ServerBase::Run()
{
    m_app.port(m_iPort).multithreaded().run();
}
