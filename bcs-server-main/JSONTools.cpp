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

                std::string sHumGnd1;
                switch (xPkt.iHumGnd1)
                {
                case 0: sHumGnd1 = "Gleba sucha"; break;
                case 1: sHumGnd1 = "Gleba wilgotna"; break;
                case 2: sHumGnd1 = "Gleba mokra"; break;
                default: sHumGnd1 = "Niepoprawny pomiar";
                }
                hJson << "\"Wilgotnosc gleby (10cm)\": \"" << sHumGnd1 << "\",\n";

                std::string sHumGnd2;
                switch (xPkt.iHumGnd2)
                {
                case 0: sHumGnd2 = "Gleba sucha"; break;
                case 1: sHumGnd2 = "Gleba wilgotna"; break;
                case 2: sHumGnd2 = "Gleba mokra"; break;
                default: sHumGnd2 = "Niepoprawny pomiar";
                }
                hJson << "\"Wilgotnosc gleby (30cm)\": \"" << sHumGnd2 << "\",\n";

                std::string sHumGnd3;
                switch (xPkt.iHumGnd3)
                {
                case 0: sHumGnd3 = "Gleba sucha"; break;
                case 1: sHumGnd3 = "Gleba wilgotna"; break;
                case 2: sHumGnd3 = "Gleba mokra"; break;
                default: sHumGnd3 = "Niepoprawny pomiar";
                }
                hJson << "\"Wilgotnosc gleby (60cm)\": \"" << sHumGnd3 << "\",\n";

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
