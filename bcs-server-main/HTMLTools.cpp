#include "HTMLTools.h"

#include <sstream>

std::string HTMLTools::drawTable(const std::vector<std::pair<int, DefaultPacket> > vPackets)
{
    auto vPkt = vPackets;
    std::ostringstream os;

    // ====================================
    const std::string sId = "ID";
    const std::string sData = "Data";
    const std::string sGodzina = "Godzina";
    const std::string sTemperatura = "Temperatura";
    const std::string sCisnienieAtm = "Ci�nienie atmosferyczne";
    const std::string sNatezenieSw = "Nat�enie �wiat�a";
    const std::string sWilgotnoscG = "Wilgotno�� gleby";
    const std::string sWilgotnoscP = "Wilgotno�� powietrza";
    const std::string sIntensywnosc = "Intensywno�� powietrza";
    const std::string sPredkosc = "Pr�dko�� wiatru";

    const int iSpace = 5;
    // ====================================

    os << std::left << std::setw(6) << sId << std::setw(15) << sData << std::setw(12) << sGodzina 
        << std::setw(sTemperatura.size() + iSpace) << sTemperatura << std::setw(sCisnienieAtm.size() + iSpace) << sCisnienieAtm
        << std::setw(sNatezenieSw.size() + iSpace) << sNatezenieSw << std::setw(sWilgotnoscG.size() + iSpace) << sWilgotnoscG
        << std::setw(sWilgotnoscP.size() + iSpace) << sWilgotnoscP << std::setw(sIntensywnosc.size() + iSpace) 
        << sIntensywnosc << std::setw(sPredkosc.size() + iSpace) << sPredkosc << std::endl;

    for (int i = (int)vPkt.size() - 1; i > -1; --i)
    {
        DefaultPacket Pkt = vPkt[i].second;
        os << std::left << std::setw(6) << vPkt[i].first << std::setw(15) << Pkt.date << std::setw(12) << Pkt.time
            << std::setw(sTemperatura.size() + iSpace) << Pkt.temp << std::setw(sCisnienieAtm.size() + iSpace) << Pkt.ps
            << std::setw(sNatezenieSw.size() + iSpace) << Pkt.lum << std::setw(sWilgotnoscG.size() + iSpace) << Pkt.humGnd
            << std::setw(sWilgotnoscP.size() + iSpace) << Pkt.humAir << std::setw(sIntensywnosc.size() + iSpace)
            << Pkt.lum << std::setw(sPredkosc.size() + iSpace) << Pkt.wspd << std::endl;
    }

    return os.str();
 }
