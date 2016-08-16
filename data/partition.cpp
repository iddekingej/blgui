#include <QString>
#include "devicebase.h"
#include "partition.h"

TPartition::TPartition(TDeviceBase *p_device,const QString &p_name,TDiskSize p_size)
:TDeviceBase(p_name,p_size)
{
	device=p_device;
}

//Fill list with data from partition
//This list is used when displaying data in a grid

void TPartition::fillDataRow(QStringList& p_list)
{	
	p_list 	<<device->getName()
		<<getName()
		<<QString::number(getSize())
		<<""
		<<getType()
		<<getMountText()
		<<getLabel()
		<<getReadableSize()
		<<""
		<<""
		<<""
		<<getSlavesString()
		<< QString::number(getFree());
;
}

//A partition never can have paritions
bool TPartition::hasPartitions()
{
	return false;
}