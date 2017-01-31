#ifndef __BTRFS_H_
#define __BTRFS_H_

#include <QString>
#include "devicelist.h"
#include "raid.h"

/**
 *   /sys/block/btrfs contains information about btrfs filesystems like device (=raid member if it is a raid) and raid level.
 *   This information is read by this class
 */
class TBtrfsInfo
{
protected:
	static void getRaidLevel(const QString &p_path,QString &p_raidLevel);
public:	
	static void processInfo(TDeviceList *p_list,TRaidInfo *p_raid);
};

#endif
