#ifndef __DEVICELIST_H_
#define __DEVICELIST_H_
#include "base/linklist.h"
#include "devicebase.h"
#include "device.h"
#include "alias.h"
#include <QString>

class TDeviceList:public TLinkList<TDevice>
{
	
private:
	TAlias *aliasses;
	QMap<QString,TDeviceBase *> nameIndex;		//name=>Device or partition
	QMap<QString,TDeviceBase *> deviceByDevPath;
	QMap<QString,TDeviceBase *> labelIndex;
	QMap<QString,TDeviceBase *> uuidIndex;
	QMap<QString,TDeviceBase *> pathIndex;
	QMap<QString,TDeviceBase *> idIndex;
	QMap<QString,TDeviceBase *> lvmIndex;
	void readPartitions(TDevice *p_device);         //read information about partitions of device  p_device
	void readDevices();                             //read device information from /sys/block
	void readLabels();            			//read information about all labels
	bool readMounts();
	void readUuid();
	void readPath();
	void readAliases();
	void readSwap();
	void readAliasFromPath(const QString &p_alias,const QString &p_path,QMap<QString,TDeviceBase *> &p_index);	
	void readLVM();
public:
	inline TDeviceBase * getDeviceByName(const QString &p_name)
	{
		return nameIndex.value(p_name);
	}
	
	inline const QMap<QString,TDeviceBase *> *getPathIndex()
	{
		return &pathIndex;
	}
	
	inline const QMap<QString,TDeviceBase *> *getUuidIndex()
	{
		return &uuidIndex;	
	}
	
	inline const QMap<QString,TDeviceBase *> *getNameIndex()
	{
		return &nameIndex;
	}
	inline const QMap<QString,TDeviceBase *> *getLabelIndex()
	{
		return &labelIndex;
	}
	
	inline const QMap<QString,TDeviceBase *> *getIdIndex()
	{
		return &idIndex;
	}
	
	inline const QMap<QString,TDeviceBase *> *getLvmIndex()
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