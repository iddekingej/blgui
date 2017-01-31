#ifndef __DEVICELIST_H_
#define __DEVICELIST_H_
#include "base/linklist.h"
#include "devicebase.h"
#include "device.h"
#include "alias.h"
#include <QString>
#include <QHash>
#include "usb.h"
#include "pci.h"

/**
 *  List of all devices in the system.
 *  This class reads all information of /sys/block /sys/fs and /sys/mounts
 */
class TDeviceList:public TLinkList<TDevice>
{
	
private:
/**
 * Path where devices information is located. This is 
 * always /sys/block
 * It can be changed for testing purpose (point to test data).
 */
	QString sysBlockPath;
/**
 *  List of device aliases
 */
	TAlias *aliasses;
/**
 * Information about usb bus and storage devices
 */
	TUsbInfo usbInfo;
/**
 * Information about pci bus and storage devices
 */
	TPCIInfo pciInfo;	
	
/**
 *  List of devices/partition , index by its name (sda,sdb1 etc...)
 */
	QHash<QString,TDeviceBase *> nameIndex;		
	
/**
 *  List of devices/partitions, indexed by device path (/dev/sda etc..)
 */
	QHash<QString,TDeviceBase *> deviceByDevPath;
/**
 *  List of devices index by label
 */
	QHash<QString,TDeviceBase *> labelIndex;
/**
 *  List of devices indexed by uuid of device
 */
	QHash<QString,TDeviceBase *> uuidIndex;
/**
 *  List of device path of device
 *  This is NOT /dev/sda etc... but symlinks in /dev/disk/by-path/
 */
	QHash<QString,TDeviceBase *> pathIndex;
/**
 *  List of devices, indexed by id
 */
	QHash<QString,TDeviceBase *> idIndex;
/**
 *  List of devices, indexed by lvm name
 */
	QHash<QString,TDeviceBase *> lvmIndex;
/**
 * List of device index by scsi bus
 */
	QHash<QString,TDevice *> scsiIndex;
/**
 * List of devices index by device no
 */
	QHash<long,TDeviceBase *> devNoIndex;
	void handleDevNo(const QString &p_path,TDeviceBase *p_device);
	void readPartitions(const QString &p_path,TDevice *p_device);         //read information about partitions of device  p_device
	void readDevices();                             //read device information from /sys/block
	void readLabels();            			//read information about all labels
	void readUuid();
	void readPath();
	void readAliases();
	void readSwap();
	void readAliasFromPath(const QString &p_alias,const QString &p_path,QHash<QString,TDeviceBase *> &p_index);	
	void readLVM();
public:
	inline void setSysBlockPath(const QString p_path){
		sysBlockPath=p_path;		
	}
	
	inline QString &getSysBlockPath()
	{
		return sysBlockPath;
	}
	
	inline TDeviceBase *getDeviceByDeviceNo(long p_no){
		return devNoIndex.value(p_no);
	}
	
	inline TDevice *getDeviceByScsiBus(const QString &p_scsiBus)
	{
		return scsiIndex.value(p_scsiBus);
	}
	
	inline TDeviceBase * getDeviceByName(const QString &p_name)
	{
		return nameIndex.value(p_name);
	}
	
	inline const QHash<QString,TDeviceBase *> *getPathIndex()
	{
		return &pathIndex;
	}
	
	inline const QHash<QString,TDeviceBase *> *getUuidIndex()
	{
		return &uuidIndex;	
	}
	
	inline const QHash<QString,TDeviceBase *> *getNameIndex()
	{
		return &nameIndex;
	}
	inline const QHash<QString,TDeviceBase *> *getLabelIndex()
	{
		return &labelIndex;
	}
	
	inline const QHash<QString,TDeviceBase *> *getIdIndex()
	{
		return &idIndex;
	}
	
	inline const QHash<QString,TDeviceBase *> *getLvmIndex()
	{
		return &lvmIndex;
	}
	
	void readInfo();
	TDeviceBase *findDeviceByDevPath(const QString &p_name);
	void sameMountPoint(const QList<TDeviceBase *> &p_list);
	void readFreeSpace();
	TDeviceList(TAlias *p_aliasses);
};
#endif
