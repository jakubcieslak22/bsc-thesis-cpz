#include "DBTools.h"

bool DBTools::init()
{
#ifdef _USING_SQL
    MYSQL* Session;
    if (!(Session = mysql_init(0)))
        return false;
    else
    {
        if (!mysql_real_connect(Session, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, "bsctest", 3306, NULL, 0))
            return false;
        else
            return true;
    }
#endif
    return true;
}

bool DBTools::fetchData(std::vector<DefaultPacket>& vPackets)
{
#ifdef _USING_SQL
    return false;
#endif
    return true;
}

bool DBTools::putData(const DefaultPacket& Packet)
{
#ifdef _USING_SQL
    return false;
#endif
    return true;
}
