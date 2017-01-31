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

/**
 * Get the model of the device
 */
const QString &TDevice::getModel()
{
	return model;
}


/**
 *  The device object contains a list of partition.
 *  This method creates a new partition object and adds it to the partition list.
 * 
 *  \param p_name  partition name (sda1 etc..)
 *  \param p_size  size of partition
 *  \param p_start start position of partition on device
 */
TPartition *TDevice::addParition(const QString &p_name,TDiskSize p_size,TDiskSize p_start)
{
	TPartition *l_partition=new TPartition(this,p_name,p_size,p_start);
	partitions.append(l_partition);
	return l_partition;
}

/**
 *  The columns in the device tree and it's order can be configured by a user.
 *  For flexible  displaying the columns, the information is stored in a list
 */

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

/**
 *  Checks if the device has partition
 *  
 *  \return  true device has partitions
 *           false device has no partitions
 */
bool TDevice::hasPartitions()
{
	return !partitions.isEmpty();
}

