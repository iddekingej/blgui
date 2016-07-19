#ifndef __DEVICE_INFO_H_
#define __DEVICE_INFO_H_
#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMap>
#include <blkid/blkid.h>
#include "base/utils.h"
#include "devicebase.h"
#include "btrfs.h"
#include "alias.h"
#include "raid.h"
#include "device.h"
#include "devicelist.h"


class TDeviceInfo
{
private:
	TBtrfsInfo  *btrfsInfo;
	TDeviceList *devices;
	TAlias      *aliasses;
	TRaidInfo   *raidList;
	blkid_cache blkidCache;

	void procesAliasses(const QString &p_path);
	void processAlias(const QString &p_file);
	QString getTypeByDevice(TDeviceBase *p_device);
public:
	inline TDeviceList *getDevices(){
		return devices;
	}
	
	inline TBtrfsInfo *getBtrfsInfo(){
		return btrfsInfo;
	}
	
	inline TRaidInfo *getRaidList()
	{
		return raidList;
	}
	
	
	void getDisks();	
	TDeviceInfo();
	~TDeviceInfo();
};

#endif