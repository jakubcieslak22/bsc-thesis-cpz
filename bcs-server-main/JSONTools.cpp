#include "JSONTools.h"

#include <fstream>
#include "DBTools.h"

bool JSONTools::packJSON()
{
    std::vector<std::pair<int, TestPacket> > vec;
    if (DBTools::fetchDataTest(vec))
    {
        std::ofstream hJson("html/json/measurements.json", std::ios::out);
        if (hJson.is_open())
        {
            int iCurrId;
            TestPacket xPkt;
            hJson << "[\n";
            for (int i = 0; i < static_cast<int>(vec.size()); ++i)
            {
                iCurrId = vec[i].first;
                xPkt = vec[i].second;
                
                hJson << "{\n";
                hJson << "\"id\": " << iCurrId << ",\n";
                hJson << "\"measure_date\": \"" << xPkt.date << "\",\n";
                hJson << "\"measure_time\": \"" << xPkt.time << "\",\n";
                hJson << "\"temperature\": " << xPkt.temp << ",\n";
                hJson << "\"air_humidity\": " << xPkt.humAir << ",\n";
                hJson << "\"pressure\": " << xPkt.ps << ",\n";
                hJson << "\"luminance\": " << xPkt.lum << ",\n";
                hJson << "\"precipitation\": " << xPkt.prec << ",\n";
                hJson << "\"wind\": " << xPkt.wspd << ",\n";
                hJson << "\"gnd_humidity1\": " << xPkt.humGnd1 << ",\n";
                hJson << "\"gnd_humidity2\": " << xPkt.humGnd2 << ",\n";
                hJson << "\"gnd_humidity3\": " << xPkt.humGnd3 << ",\n";
                hJson << "\"location\": \"" << xPkt.location << "\"\n";
                if (i < static_cast<int>(vec.size()) - 1)
                    hJson << "},\n\n";
                else
                    hJson << "}\n";
            }
            hJson << "]\n";
            hJson.close();
            return true;
        }
    }
    return false;
}
