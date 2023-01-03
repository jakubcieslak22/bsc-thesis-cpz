#include "JSONTools.h"

#include <fstream>
#include "DBTools.h"

/** 
* \brief Eksportuje dane pobrane z bazy danych do pliku JSON w formie listy obiektów
* \return true, jeœli operacja siê powiod³a
*/
bool JSONTools::packJSON(std::vector<std::pair<int, MeasurementsPacket> >& vCachedPackets)
{
    std::vector<std::pair<int, MeasurementsPacket> > vec;
    if (DBTools::fetchMeasurementData(vec))
    {
        vCachedPackets = vec;
        std::ofstream hJson("html/json/measurements.json", std::ios::out);
        if (hJson.is_open())
        {
            int iCurrId;
            MeasurementsPacket xPkt;
            hJson << "[\n";
            for (int i = 0; i < static_cast<int>(vec.size()); ++i)
            {
                iCurrId = vec[i].first;
                xPkt = vec[i].second;
                
                hJson << "{\n";
                hJson << "\"Nr pomiaru\": " << iCurrId << ",\n";
                hJson << "\"Data pomiaru\": \"" << xPkt.sDate << "\",\n";
                hJson << "\"Godzina pomiaru\": \"" << xPkt.sTime << "\",\n";
                hJson << "\"Temperatura\": \"" << xPkt.fTemp << " st. C\",\n";
                hJson << "\"Wilgotnosc powietrza\": \"" << xPkt.fHumAir << "%\",\n";
                hJson << "\"Cisnienie atmosferyczne\": \"" << xPkt.iPs << " hPa\",\n";
                hJson << "\"Natezenie swiatla\": \"" << xPkt.fLum << " lx\",\n";

                std::string sPrec;
                switch (xPkt.iPrec)
                {
                case 0: sPrec = "Brak opadow"; break;
                case 1: sPrec = "Opady lekkie"; break;
                case 2: sPrec = "Opady umiarkowane"; break;
                case 3: sPrec = "Opady silne"; break;
                default: sPrec = "Niepoprawny pomiar";
                }
                hJson << "\"Intensywnosc opadow\": \"" << sPrec << "\",\n";

                std::string sWspd;
                switch (xPkt.iWspd)
                {
                case 0: sWspd = "Brak wiatru"; break;
                case 1: sWspd = "Wiatr lekki"; break;
                case 2: sWspd = "Wiatr umiarkowany"; break;
                case 3: sWspd = "Wiatr silny"; break;
                default: sWspd = "Niepoprawny pomiar";
                }
                hJson << "\"Predkosc wiatru\": \"" << sWspd << "\",\n";

                hJson << "\"Wilgotnosc gleby (10cm)\": \"" << xPkt.iHumGnd1 << "%\",\n";
                hJson << "\"Wilgotnosc gleby (30cm)\": \"" << xPkt.iHumGnd2 << "%\",\n";
                hJson << "\"Wilgotnosc gleby (60cm)\": \"" << xPkt.iHumGnd3 << "%\",\n";

                hJson << "\"Lokalizacja\": \"" << xPkt.sLocation << "\"\n";
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
