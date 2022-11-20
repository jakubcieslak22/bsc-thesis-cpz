#include "DBTools.h"

#include <iostream>

/**
* \brief Inicjalizuje po³¹czenie z baz¹ danych
* \return true, jeœli operacja siê powiod³a
*/
bool DBTools::init()
{
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
}

/**
* \brief Pobiera dane z bazy danych
* \param vPackets - wektor struktur, w którym s¹ umieszczane pobrane dane
* \return true, jeœli operacja siê powiod³a
*/
bool DBTools::fetchMeasurementData(std::vector<std::pair<int, MeasurementsPacket> >& vPackets)
{
    if (!bInitialized)
        return false;

    std::string query = "SELECT * FROM ";
    query += MYSQL_TBNAME;
    query += ";";
    mysql_query(Session, query.c_str());

    MYSQL_RES* Result = mysql_store_result(Session);
    uint64_t uiRowCount = Result->row_count;
    uint64_t uiIter = 0;
    MYSQL_ROW xRow;
    try
    {
        while (uiIter < uiRowCount)
        {
            xRow = mysql_fetch_row(Result);
            MeasurementsPacket pkt;
            pkt.sDate = xRow[1];
            pkt.sTime = xRow[2];
            pkt.fTemp = atof(xRow[3]);
            pkt.fHumAir = atof(xRow[4]);
            pkt.iPs = atoi(xRow[5]);
            pkt.fLum = atof(xRow[6]);
            pkt.fPrec = atof(xRow[7]);
            pkt.iWspd = atoi(xRow[8]);
            pkt.iHumGnd1 = atoi(xRow[9]);
            pkt.iHumGnd2 = atoi(xRow[10]);
            pkt.iHumGnd3 = atoi(xRow[11]);
            pkt.sLocation = xRow[12];

            vPackets.emplace_back(std::make_pair(atoi(xRow[0]), pkt));
            ++uiIter;
        }

    }
    catch (...)
    {
        return false;
    }

    return true;
}

/**
* \brief Umieszcza dane w bazie danych
* \param vPackets - wektor struktur, którego dane s¹ przesy³ane do bazy danych
* \return true, jeœli operacja siê powiod³a
*/
bool DBTools::putMeasurementData(const MeasurementsPacket& Packet)
{
    if (!bInitialized)
        return false;

    MeasurementsPacket xPacket = Packet;

    std::string cmd;
    cmd = "INSERT INTO " + std::string(MYSQL_TBNAME) + " VALUES(DEFAULT, \"" + xPacket.sDate + "\", \"" + xPacket.sTime + "\", " 
        + std::to_string(xPacket.fTemp) + ", " + std::to_string(xPacket.fHumAir) + ", " + std::to_string(xPacket.iPs) + ", " 
        + std::to_string(xPacket.fLum) + ", " + std::to_string(xPacket.fPrec) + ", " + std::to_string(xPacket.iWspd) + ", " 
        + std::to_string(xPacket.iHumGnd1) + ", " + std::to_string(xPacket.iHumGnd2) + ", " + std::to_string(xPacket.iHumGnd3) + ", \"" 
        + xPacket.sLocation + "\");";

    if (mysql_ping(Session))
        return false;

    if (mysql_query(Session, cmd.c_str()))
    {
        std::cout << mysql_error(Session) << std::endl;
        return false;
    }
    
    return true;
}
