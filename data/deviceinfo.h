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
#include "lvm.h"

/**
 * This class combines all the information
 */

class TDeviceInfo
{
private:
	/**
	 * Base path of information (/proc /sys/block /etc ..) to read.
	 * By default '/', can be changed for testing 
	 */
	QString basePath;

	/**
	 *  Information about all devices
	 */
	TDeviceList       *devices;
	
	/**
	 * list of aliases of a device
	 */
	
	TAlias            *aliasses;
	/*
	 * Information about raid on the system (Lsinux raid and btrfs)
	 */
	TRaidInfo         *raidList;
	/**
	 * Information about mounted devices
	 */
	TMTab             *mtab;
	/**
	 * Information about iscsi deices
	 */
	TIScsiSessionList *iscsi;
	/**
	 * Information about LVM devices 
	 */
	TLVM              *lvm;
	/**
	 * libblkid is used for determine the file system type.
	 * this information is cached
	 */
	blkid_cache blkidCache;
	/**
	 * Time and date the information is read.
	 */
	
	QDateTime   sbTime;
	/**
	 * Btrfs information
	 */
	TBtrfsInfo *btrfsInfo;	

	void procesAliasses(const QString &p_path);
	void processAlias(const QString &p_file);
	void getTypeByDevice(TDeviceBase *p_device,QString &p_type);
public:
	inline QString &getBasePath()
	{
		return basePath;
	}
	
	inline void setBasePath(const QString &p_basePath)
	{
		basePath=p_basePath;
	}
	
	inline TDeviceList *getDevices(){
		return devices;
	}
	
	inline QDateTime *getSbTime()
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
