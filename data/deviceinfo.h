#ifndef __DEVICE_INFO_H_
#define __DEVICE_INFO_H_
#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMap>
#include <QDateTime>
#include <blkid/blkid.h>
#include "base/utils.h"
#include "devicebase.h"
#include "btrfs.h"
#include "alias.h"
#include "raid.h"
#include "device.h"
#include "devicelist.h"
#include "mtab.h"


class TDeviceInfo
{
private:
	TBtrfsInfo  *btrfsInfo;
	TDeviceList *devices;
	TAlias      *aliasses;
	TRaidInfo   *raidList;
	TMTab       *mtab;
	TMTab       *mounted;
	blkid_cache blkidCache;
	QDateTime   sbTime;

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
	
	inline TMTab *getMounted()
	{
		return mounted;
	}
	
	QDateTime *getSbTime()
	{
		return &sbTime;
	}
	
	inline TRaidInfo *getRaidList()
	{
		return raidList;
	}
	
	inline TMTab *getMTab()
	{
		return mtab;
	}
	
	void getDisks();	
	TDeviceInfo();
	~TDeviceInfo();
};

#endif