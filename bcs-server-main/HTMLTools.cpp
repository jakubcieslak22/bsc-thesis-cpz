#include "HTMLTools.h"

#include <sstream>

std::string HTMLTools::drawMeasurementsTable(const std::vector<std::pair<int, MeasurementsPacket> >& vPackets)
{
    auto vPkt = vPackets;
    std::ostringstream os;

    // ====================================
    const std::string sId = "ID";
    const std::string sData = "Data";
    const std::string sGodzina = "Godzina";
    const std::string sTemperatura = "Temperatura";
    const std::string sWilgotnoscP = "Wilgotnoœæ powietrza";
    const std::string sCisnienieAtm = "Ciœnienie atmosferyczne";
    const std::string sNatezenieSw = "Natê¿enie œwiat³a";
    const std::string sIntensywnosc = "Intensywnoœæ opadów";
    const std::string sPredkosc = "Prêdkoœæ wiatru";
    const std::string sWilgotnoscG1 = "Wilgotnoœæ gleby 1";
    const std::string sWilgotnoscG2 = "Wilgotnoœæ gleby 2";
    const std::string sWilgotnoscG3 = "Wilgotnoœæ gleby 3";
    const std::string sLokalizacja = "Lokalizacja";

    const int iSpace = 5;
    // ====================================

    if (vPkt.size() == 0)
        return std::string("Brak danych w bazie.");
    else
    {
        os << std::left << std::setw(6) << sId << std::setw(15) << sData << std::setw(12) << sGodzina
            << std::setw(sTemperatura.size() + iSpace) << sTemperatura << std::setw(sWilgotnoscP.size() + iSpace) << sWilgotnoscP
            << std::setw(sCisnienieAtm.size() + iSpace) << sCisnienieAtm << std::setw(sNatezenieSw.size() + iSpace) << sNatezenieSw
            << std::setw(sIntensywnosc.size() + iSpace) << sIntensywnosc << std::setw(sPredkosc.size() + iSpace)
            << sPredkosc << std::setw(sWilgotnoscG1.size() + iSpace) << sWilgotnoscG1 << std::setw(sWilgotnoscG2.size() + iSpace) << sWilgotnoscG2
            << std::setw(sWilgotnoscG3.size() + iSpace) << sWilgotnoscG3 << std::setw(sLokalizacja.size() + iSpace) << sLokalizacja << std::endl;

        for (int i = (int)vPkt.size() - 1; i > -1; --i)
        {
            MeasurementsPacket Pkt = vPkt[i].second;
            os << std::left << std::setw(6) << vPkt[i].first << std::setw(15) << Pkt.sDate << std::setw(12) << Pkt.sTime
                << std::setw(sTemperatura.size() + iSpace) << Pkt.fTemp << std::setw(sWilgotnoscP.size() + iSpace) << Pkt.fHumAir
                << std::setw(sCisnienieAtm.size() + iSpace) << Pkt.iPs << std::setw(sNatezenieSw.size() + iSpace) << Pkt.fLum
                << std::setw(sIntensywnosc.size() + iSpace) << Pkt.fPrec << std::setw(sPredkosc.size() + iSpace) << Pkt.iWspd 
                << std::setw(sWilgotnoscG1.size() + iSpace) << Pkt.iHumGnd1 << std::setw(sWilgotnoscG2.size() + iSpace) << Pkt.iHumGnd2 
                << std::setw(sWilgotnoscG3.size() + iSpace) << Pkt.iHumGnd3 << std::setw(sLokalizacja.size() + iSpace) << Pkt.sLocation << std::endl;
        }

        return os.str();
    }
}

