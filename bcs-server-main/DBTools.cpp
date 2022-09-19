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
bool DBTools::fetchData(std::vector<std::pair<int, DefaultPacket> >& vPackets)
{
#ifdef _USING_SQL
    if (!bInitialized)
        return false;

    std::string query = "SELECT * FROM ";
    query += MYSQL_TBNAME;
    query += ";";
    mysql_query(Session, query.c_str());

    MYSQL_RES* Result = mysql_store_result(Session);
    uint64_t uiRowCount = Result->row_count;
    uint64_t uiIter = 0;
    MYSQL_ROW row;
    try
    {
        while (uiIter < uiRowCount)
        {
            row = mysql_fetch_row(Result);
            DefaultPacket pkt;
            pkt.date = row[1];
            pkt.time = row[2];
            pkt.temp = atof(row[3]);
            pkt.ps = atof(row[4]);
            pkt.lum = atof(row[5]);
            pkt.humGnd = atof(row[6]);
            pkt.humAir = atof(row[7]);
            pkt.prec = atof(row[8]);
            pkt.wspd = atof(row[9]);

            vPackets.emplace_back(std::make_pair(atoi(row[0]), pkt));
            ++uiIter;
        } 

    }
    catch (...)
    {
        return false;
    }

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

bool DBTools::fetchDataTest(std::vector<std::pair<int, TestPacket>>& vPackets)
{
#ifdef _USING_SQL
    if (!bInitialized)
        return false;

    std::string query = "SELECT * FROM ";
    query += MYSQL_TBNAME;
    query += ";";
    mysql_query(Session, query.c_str());

    MYSQL_RES* Result = mysql_store_result(Session);
    uint64_t uiRowCount = Result->row_count;
    uint64_t uiIter = 0;
    MYSQL_ROW row;
    try
    {
        while (uiIter < uiRowCount)
        {
            row = mysql_fetch_row(Result);
            TestPacket pkt;
            pkt.date = row[1];
            pkt.time = row[2];
            pkt.temp = atof(row[3]);
            pkt.humAir = atof(row[4]);
            pkt.ps = atof(row[5]);
            pkt.lum = atof(row[6]);
            pkt.prec = atof(row[7]);
            pkt.wspd = atof(row[8]);
            pkt.humGnd1 = atof(row[9]);
            pkt.humGnd2 = atof(row[10]);
            pkt.humGnd3 = atof(row[11]);
            pkt.location = row[12];

            vPackets.emplace_back(std::make_pair(atoi(row[0]), pkt));
            ++uiIter;
        }

    }
    catch (...)
    {
        return false;
    }

#endif
    return true;
}

bool DBTools::putDataTest(const TestPacket& Packet)
{
#ifdef _USING_SQL
    if (!bInitialized)
        return false;

    TestPacket xPacket = Packet;

    std::string cmd;
    cmd = "INSERT INTO " + std::string(MYSQL_TBNAME) + " VALUES(DEFAULT, \"" + xPacket.date + "\", \"" + xPacket.time + "\", " +
        std::to_string(xPacket.temp) + ", " + std::to_string(xPacket.humAir) + ", " + std::to_string(xPacket.ps) + ", " +
        std::to_string(xPacket.lum) + ", " + std::to_string(xPacket.prec) + ", " + std::to_string(xPacket.wspd) +
        ", " + std::to_string(xPacket.humGnd1) + ", " + std::to_string(xPacket.humGnd2) + ", " + std::to_string(xPacket.humGnd3) + 
        ", \"" + xPacket.location + "\");";

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
