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
private:
	/**
	 * Information is read from /sys/block/btrfs folder but can be changed by base basepath 
	 * for testing purpose.
	 * basePath is by default /
	 */
	QString basePath;
protected:
	static void getRaidLevel(const QString &p_path,QString &p_raidLevel);
public:	
	inline QString &getBasePath(){ return basePath;}
	inline void setBasePath(const QString &p_basePath){ basePath=p_basePath;}
	 void processInfo(TDeviceList *p_list,TRaidInfo *p_raid);
	TBtrfsInfo();
};

#endif
