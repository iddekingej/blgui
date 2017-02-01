#include <QString>
#include "devicebase.h"
#include "partition.h"
#include "base/compat.h"

/**
 *  Creates partition information object
 *  
 *  \param p_device  block to device to which this partition belongs
 *  \param p_name    name of partition
 *  \param p_size    size of partition
 *  \param p_start   start point of partition
 */
TPartition::TPartition(TDeviceBase *p_device,const QString &p_name,TDiskSize p_size,TDiskSize p_start)
:TDeviceBase(p_name,p_size)
{
	device=p_device;
	start=p_start;
}

/**
 * The fields in the device grid is set by configuration,so it is dynamically 
 * For easy filling the grid based on the configuration, all the partition information
 * is copied to a QStringList.
 */

void TPartition::fillDataRow(QStringList& p_list)
{	
	p_list 	<<getDevice()->getName()
		<<getName()
		<<QString::number(getSize())
		<<QStringLiteral("")
		<<getType()
		<<getMountText()
		<<getLabel()
		<<getReadableSize()
		<<QStringLiteral("")
		<<QStringLiteral("")
		<<QStringLiteral("")
		<<getSlavesString()
		<< (getHasFree()?QString::number(getFree()):QStringLiteral(""))
		<<QStringLiteral("")
		<<QStringLiteral("")
		<<QString::number(start)
		<<getReadableFreeSize()
		<<QStringLiteral("")
		<<QStringLiteral("")
		<<QStringLiteral("")
		<< getVGName()
		<<QStringLiteral("");
;
}

/**
 *    Returns if device has  a partition. Because partition can't have a partition, it always returns false
 *    See also @see  TDevice::hasPartitions
 * 
 *    \return Has partition=>always false because a partition can't have a partition
 */
bool TPartition::hasPartitions()
{
	return false;
}
