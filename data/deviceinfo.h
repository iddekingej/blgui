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
#include "iscsi.h"
#include "base/compat.h"
#include "lvm.h"

class TDeviceInfo
{
private:
	TDeviceList       *devices;
	TAlias            *aliasses;
	TRaidInfo         *raidList;
	TMTab             *mtab;
	TIScsiSessionList *iscsi;
	TLVM              *lvm;
	blkid_cache blkidCache;
	QDateTime   sbTime;
	

	void procesAliasses(const QString &p_path);
	void processAlias(const QString &p_file);
	void getTypeByDevice(TDeviceBase *p_device,QString &p_type);
public:
	inline TDeviceList *getDevices(){
		return devices;
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
	
	inline TIScsiSessionList *getIscsiSessions()
	{
		return iscsi;
	}
	
	inline TLVM *getLVM()
	{
		return lvm;
	}
	
	void getDisks();	
	TDeviceInfo();
	~TDeviceInfo();
};

#endif
