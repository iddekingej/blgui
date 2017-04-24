#include <QString>
#include "devicebase.h"
#include "partition.h"
#include "base/compat.h"
#include "base/globals.h"
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

void TPartition::fillDataRow(TField p_no,QString &p_data)
{	
	switch(p_no){
		case FIELD_DEVICE_NAME:
			p_data=getDevice()->getName();
			break;
		case FIELD_PARTITION_NAME:
			p_data=getName();
			break;
		case FIELD_SIZE:
			p_data=QString::number(getSize());
			break;
		case FIELD_MODEL:
			p_data=QStringLiteral("");
			break;
		case FIELD_TYPE:
			p_data=getType();
			break;
		case FIELD_MOUNTED:
			p_data=getMountText();
			break;
		case FIELD_LABEL:
			p_data=getLabel();
			break;
		case FIELD_SIZE_KMG:
			p_data=getReadableSize();
			break;
		case FIELD_READONLY:
		case FIELD_REMOVABLE:
		case FIELD_LOOPBACKFILE:
		case FIELD_SCSI_BUS:
		case FIELD_ISCSI_HOST:
		case FIELD_ROTATIONAL:
		case FIELD_USB_BUS:
		case FIELD_PCI_BUS:
		case FIELD_LVM_NAME:
			p_data=QStringLiteral("");
			break;
		case FIELD_FREE_SPACE:
			p_data=(getHasFree()?QString::number(getFree()):QStringLiteral(""));
			break;
		case FIELD_START:
			p_data=QString::number(start);
			break;
		case FIELD_FREE_SPACE_KMG:
			p_data=getReadableFreeSize();
			break;
		case FIELD_VG_NAME:
			p_data=getVGName();
			break;
		default:
			p_data=QStringLiteral("Invalid field no:")+QString::number(p_no);
	}
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
