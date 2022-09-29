#include <QString>
#include "devicebase.h"
#include "partition.h"
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
		case TField::DEVICE_NAME:
			p_data=getDevice()->getName();
			break;
		case TField::PARTITION_NAME:
			p_data=getName();
			break;
		case TField::SIZE:
			p_data=QString::number(getSize());
			break;
		case TField::MODEL:
			p_data=QString();
			break;
		case TField::TYPE:
			p_data=getType();
			break;
		case TField::MOUNTED:
			p_data=getMountText();
			break;
		case TField::LABEL:
			p_data=getLabel();
			break;
		case TField::SIZE_KMG:
			p_data=getReadableSize();
			break;
		case TField::READONLY:
		case TField::REMOVABLE:
		case TField::LOOPBACKFILE:
		case TField::SCSI_BUS:
		case TField::ISCSI_HOST:
		case TField::ROTATIONAL:
		case TField::USB_BUS:
		case TField::PCI_BUS:
		case TField::LVM_NAME:
			p_data=QEMPTY_STRING;
			break;
		case TField::FREE_SPACE:
			p_data=getHasFree()?QString::number(getFree()):QEMPTY_STRING;
			break;
		case TField::START:
			p_data=QString::number(start);
			break;
		case TField::FREE_SPACE_KMG:
			p_data=getReadableFreeSize();
			break;
		case TField::VG_NAME:
			p_data=getVGName();
			break;
		case TField::SLAVES:
			p_data=getSlavesString();
			break;
		default:
			p_data=QStringLiteral("Invalid field no:")+QString::number((int)p_no);
	}
}

bool TPartition::getFieldValue(TField p_no, QVariant& p_data)
{
		switch(p_no){
		case TField::DEVICE_NAME:
			p_data=getDevice()->getName();
			break;
		case TField::PARTITION_NAME:
			p_data=getName();
			break;
		case TField::SIZE:
			p_data=(qlonglong)getSize();
			break;
		case TField::MODEL:
			p_data=QEMPTY_STRING;
			break;
		case TField::TYPE:
			p_data=getType();
			break;
		case TField::MOUNTED:
			p_data=getMountText();
			break;
		case TField::LABEL:
			p_data=getLabel();
			break;
		case TField::SIZE_KMG:
			p_data=getReadableSize();
			break;
		case TField::READONLY:
		case TField::REMOVABLE:
		case TField::LOOPBACKFILE:
		case TField::SCSI_BUS:
		case TField::ISCSI_HOST:
		case TField::ROTATIONAL:
		case TField::USB_BUS:
		case TField::PCI_BUS:
		case TField::LVM_NAME:
			p_data=QString();
			break;
		case TField::FREE_SPACE:
			p_data=getHasFree()?(qlonglong)getFree():-1;
			break;
		case TField::START:
			p_data=(qlonglong)start;
			break;
		case TField::FREE_SPACE_KMG:
			p_data=getReadableFreeSize();
			break;
		case TField::VG_NAME:
			p_data=getVGName();
			break;
		case TField::SLAVES:
			p_data=getSlavesString();
			break;
		default:
			p_data=QStringLiteral("Invalid field no:")+QString::number((int)p_no);
			return true;
	}
	return false;
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
