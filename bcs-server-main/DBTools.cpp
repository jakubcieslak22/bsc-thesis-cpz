#include "DBTools.h"

#include <iostream>

bool DBTools::init()
{
#ifdef _USING_SQL
    if (!(Session = mysql_init(0)))
        return false;
    else
    {
        if (!mysql_real_connect(Session, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DBNAME, 3306, NULL, 0))
            return false;
        else
        {
            bInitialized = true;
            return true;
        }
    }
#endif
    return true;
}


/**
* \brief Pobiera pakiety z bazy danych
* \param vPackets - umieszcza pobrane dane w tym wektorze
*/
bool DBTools::fetchData(std::vector<DefaultPacket>& vPackets)
{
#ifdef _USING_SQL
    if (!bInitialized)
        return false;

#endif
    return true;
}

bool DBTools::putData(const DefaultPacket& Packet)
{
#ifdef _USING_SQL
    if (!bInitialized)
		return false;

	DefaultPacket xPacket = Packet;

	std::string cmd;
	cmd = "INSERT INTO " + std::string(MYSQL_TBNAME) + " VALUES(DEFAULT, \"" + xPacket.date + "\", \"" + xPacket.time + "\", " +
		std::to_string(xPacket.temp) + ", " + std::to_string(xPacket.ps) + ", " + std::to_string(xPacket.lum) + ", " +
		std::to_string(xPacket.humGnd) + ", " + std::to_string(xPacket.humAir) + ", " + std::to_string(xPacket.prec) +
		", " + std::to_string(xPacket.wspd) + ");";

	if (mysql_ping(Session))
		return false;

    if (mysql_query(Session, cmd.c_str()))
    {
        std::cout << mysql_error(Session) << std::endl;
        return false;
    }
#endif
    return true;
}
