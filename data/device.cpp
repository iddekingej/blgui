#include "device.h"
#include "base/utils.h"
#include "base/compat.h"

#include <QString>

/**
 * TDevice constructor
 * 
 * \param p_name  device name (/dev/sda => name=sda)
 * \param p_size  disk size
 */

TDevice::TDevice(const QString &p_name,TDiskSize p_size)
:TDeviceBase(p_name,p_size)
{			
}

const QString &TDevice::getModel()
{
	return model;
}

TPartition *TDevice::addParition(const QString &p_name,TDiskSize p_size,TDiskSize p_start)
{
	TPartition *l_partition=new TPartition(this,p_name,p_size,p_start);
	partitions.append(l_partition);
	return l_partition;
}

void TDevice::fillDataRow(QStringList& p_list)
{
	p_list 	<< getName()
		<< QStringLiteral("")
		<< QString::number(getSize())
		<< getVendor()+"/"+getModel()
		<< getType()
		<< getMountText()
		<< getLabel()
		<< getReadableSize()
		<< (readonly?"X":"")
		<< (removable?"X":"")
		<< loopbackFile
		<<  getSlavesString()
		<<  (getHasFree()?QString::number(getFree()):QStringLiteral(""))
		<< getScsiBus()
		<< getIScsiAddress()
		<< QStringLiteral("")
		<< getReadableFreeSize()
		<< (getRotational()?"X":"")
		<< getUsbBus()
		<< getPciBus()
		<< getVGName()
		<< getLVMName() ;

}

bool TDevice::hasPartitions()
{
	return partitions.getStart() != nullptr;
}

