#pragma once
#ifndef HTMLTOOLS_H
#define HTMLTOOLS_H

#include "crow.h"

#include "packets.h"

namespace HTMLTools
{
	std::string drawMeasurementsTable(const std::vector<std::pair<int, MeasurementsPacket> >& vPackets);
};

#endif //HTMLTOOLS_H
