#pragma once
#include "packets.h"
#ifndef JSONTOOLS_H
#define JSONTOOLS_H
namespace JSONTools
{
	bool packJSON(std::vector<std::pair<int, MeasurementsPacket> >& vCachedPackets);
}
#endif //JSONTOOLS_H
