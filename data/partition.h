#ifndef __PARTITION_H_
#define __PARTITION_H_
#include <QString>
#include "devicebase.h"
#include "mount.h"

class TPartition:public TDeviceBase
{
private:
	TDeviceBase *device;
public:
	inline TDeviceBase *getDevice(){ return device;}
	
	TPartition(TDeviceBase *p_device,const QString &p_name,TDiskSize p_size);
	virtual void fillDataRow(QStringList &p_list);
	virtual bool hasPartitions();
};
#endif