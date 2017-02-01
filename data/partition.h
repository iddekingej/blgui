#ifndef __PARTITION_H_
#define __PARTITION_H_
#include <QString>
#include "devicebase.h"
#include "mount.h"

/**
 * Partition contains information about a partition
 */
class TPartition:public TDeviceBase
{
private:
	/*
	 * Partition belong to this device
	 */
	TDeviceBase *device;
	/*
	 * Start in bytes of the partition
	 */
	TDiskSize start;
public:
	inline TDeviceBase *getDevice(){ return device;}
	inline TDiskSize getStart(){ return start;}
	TPartition(TDeviceBase *p_device,const QString &p_name,TDiskSize p_size,TDiskSize p_start);
	virtual void fillDataRow(QStringList &p_list);
	virtual bool hasPartitions();
};
#endif
