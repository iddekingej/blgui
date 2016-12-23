#ifndef __BTRFS_H_
#define __BTRFS_H_

#include <QString>
#include "devicelist.h"
#include "raid.h"

/**Read all btrfs info
 */
class TBtrfsInfo
{
protected:
	static void getRaidLevel(const QString &p_path,QString &p_raidLevel);
public:	
	static void processInfo(TDeviceList *p_list,TRaidInfo *p_raid);
};

#endif
