#include "device.h"
#include "base/utils.h"

#include <QString>

TDevice::TDevice(const QString &p_name,const QString &p_model,TDiskSize p_size)
:TDeviceBase(p_name,p_size)
{		
	model=p_model;
}

const QString &TDevice::getModel()
{
	return model;
}

TPartition *TDevice::addParition(const QString &p_name,TDiskSize p_size)
{
	TPartition *l_partition=new TPartition(this,p_name,p_size);
	partitions.append(l_partition);
	return l_partition;
}

void TDevice::fillDataRow(QStringList& p_list)
{
	p_list 	<< getName()
		<< ""
		<< QString::number(getSize())
		<< getVendor()+"/"+getModel()
		<< getType()
		<< getMounts()
		<< getLabel()
		<< getReadableSize()
		<< (readonly?"X":"")
		<< (removable?"X":"")
		<< loopbackFile
		<<  getSlavesString()
		<<  (!hasPartitions() && getMounts().length()>0?QString::number(getFree()):"");
}

bool TDevice::hasPartitions()
{
	return partitions.getStart() != nullptr;
}

