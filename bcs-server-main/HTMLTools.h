#pragma once
#ifndef HTMLTOOLS_H
#define HTMLTOOLS_H

#include "packets.h"

namespace HTMLTools
{
	std::string drawTable(const std::vector<std::pair<int, DefaultPacket> >& vPackets);
	std::string drawTestTable(const std::vector<std::pair<int, TestPacket> >& vPackets);
};

#endif //HTMLTOOLS_H
