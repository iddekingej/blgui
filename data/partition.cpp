#include <QString>
#include "devicebase.h"
#include "partition.h"

TPartition::TPartition(TDeviceBase *p_device,const QString &p_name,TDiskSize p_size)
:TDeviceBase(p_name,p_size)
{
	device=p_device;
}

void TPartition::fillDataRow(QStringList& p_list)
{	
	p_list 	<<device->getName()
		<<getName()
		<<QString::number(getSize())
		<<getModel()
		<<getType()
		<<getMounts()
		<<getLabel()
		<<getReadableSize()
		<<""
		<<""
		<<""
		<<getSlavesString();
}


const QString TPartition::getModel()
{
	return "";
}


bool TPartition::hasPartitions()
{
	return false;
}