#ifndef __LINUXRAID_
#define __LINUXRAID_
#include "data/devicelist.h"
#include "data/raid.h"

class TLinuxRaid
{
public:
	static void processInfo(TDeviceList* p_list,TRaidInfo *p_raid);
};

#endif
