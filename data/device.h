#ifndef __DEVICE_H_
#define __DEVICE_H_
#include "devicebase.h"
#include "base/linklist.h"
#include "partition.h"
#include <QString>
class TDevice:public TDeviceBase
{
private:
	TLinkList<TPartition> partitions;	
	QString model;
	QString vendor;
	bool    readonly;
	bool    removable;
	QString loopbackFile;
public:
	

	inline int getNumPartitions()
	{
		return partitions.getLength();
	}
	
	
	inline const QString &getLoopbackFile()
	{
		return loopbackFile;
	}
	
	inline void setLoopbackFile(const QString &p_file)
	{
		loopbackFile=p_file;
	}

	inline bool getReadonly()
	{
		return readonly;
	}
	
	inline void setReadonly(bool p_readonly)
	{
		readonly=p_readonly;
	}
	
	inline bool getRemovable()
	{
		return removable;
	}
	
	inline void setRemovable(bool p_removable)
	{
		removable=p_removable;
	}
	
	TLinkListItem<TPartition> *getPartitionStart()
	{
		return partitions.getStart();
	}

	inline void setVendor(const QString &p_vendor)
	{
		vendor=p_vendor;
	}
	
	inline QString &getVendor(){
		return vendor;
	}
	
	inline void setModel(const QString &p_model)
	{
		model=p_model;
	}
	
	const QString &getModel();
	virtual void fillDataRow(QStringList &p_list);

	TDevice(const QString &p_name,const QString &p_model,TDiskSize p_size);
	TPartition *addParition(const QString &p_name,TDiskSize p_size);
	bool hasPartitions();
};
#endif