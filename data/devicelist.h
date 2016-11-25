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
class TDeviceList:public TLinkList<TDevice>
{
	
private:
	TAlias *aliasses;
	TUsbInfo usbInfo;
	TPCIInfo pciInfo;	
	QHash<QString,TDeviceBase *> nameIndex;		//name=>Device or partition
	QHash<QString,TDeviceBase *> deviceByDevPath;
	QHash<QString,TDeviceBase *> labelIndex;
	QHash<QString,TDeviceBase *> uuidIndex;
	QHash<QString,TDeviceBase *> pathIndex;
	QHash<QString,TDeviceBase *> idIndex;
	QHash<QString,TDeviceBase *> lvmIndex;
	QHash<QString,TDevice *> scsiIndex;
	QHash<long,TDeviceBase *> devNoIndex;
	void handleDevNo(QString p_path,TDeviceBase *p_device);
	void readPartitions(TDevice *p_device);         //read information about partitions of device  p_device
	void readDevices();                             //read device information from /sys/block
	void readLabels();            			//read information about all labels
	void readUuid();
	void readPath();
	void readAliases();
	void readSwap();
	void readAliasFromPath(const QString &p_alias,const QString &p_path,QHash<QString,TDeviceBase *> &p_index);	
	void readLVM();
public:
	
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
