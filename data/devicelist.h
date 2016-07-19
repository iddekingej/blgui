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
	QMap<QString,TDeviceBase *> nameIndex;
	QMap<QString,TDeviceBase *> deviceByDevPath;
	QMap<QString,TDeviceBase *> labelIndex;
	QMap<QString,TDeviceBase *> uuidIndex;
	QMap<QString,TDeviceBase *> pathIndex;
	QMap<QString,TDeviceBase *> idIndex;
	void readPartitions(TDevice *p_device);
	void readLabels(TAlias *p_aliasses);
	void readDevices();
	bool readMounts(TAlias *p_aliasses);
	void readUuid(TAlias *p_aliasses);
	void readPath(TAlias *p_aliasses);
	void readAliases(TAlias *p_aliasses);
	void readAliasFromPath(const QString &p_alias,const QString &p_path,QMap<QString,TDeviceBase *> &p_index,TAlias *p_aliasses);
	void readLabels();
	
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
	void readInfo(TAlias *p_aliasses);
};
#endif