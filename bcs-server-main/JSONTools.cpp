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
                hJson << "\"Nr pomiaru\": " << iCurrId << ",\n";
                hJson << "\"Data pomiaru\": \"" << xPkt.date << "\",\n";
                hJson << "\"Godzina pomiaru\": \"" << xPkt.time << "\",\n";
                hJson << "\"Temperatura\": \"" << xPkt.temp << " st. C\",\n";
                hJson << "\"Wilgotnosc powietrza\": \"" << xPkt.humAir << "%\",\n";
                hJson << "\"Cisnienie atmosferyczne\": \"" << xPkt.ps << " hPa\",\n";
                hJson << "\"Natezenie swiatla\": \"" << xPkt.lum << " lx\",\n";
                hJson << "\"Intensywnosc opadow\": \"" << xPkt.prec << " mm\",\n";
                std::string sWspd;
                switch (xPkt.wspd)
                {
                case 0: sWspd = "Brak wiatru"; break;
                case 1: sWspd = "Lekki wiatr"; break;
                case 2: sWspd = "Umiarkowany wiatr"; break;
                case 3: sWspd = "Silny wiatr"; break;
                default: sWspd = "Niepoprawny pomiar";
                }
                hJson << "\"Predkosc wiatru\": \"" << sWspd << "\",\n";
                hJson << "\"Wilgotnosc gleby (10cm)\": " << xPkt.humGnd1 << ",\n";
                hJson << "\"Wilgotnosc gleby (20cm)\": " << xPkt.humGnd2 << ",\n";
                hJson << "\"Wilgotnosc gleby (30cm)\": " << xPkt.humGnd3 << ",\n";
                hJson << "\"Lokalizacja\": \"" << xPkt.location << "\"\n";
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
