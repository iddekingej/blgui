#include "device.h"
#include "base/utils.h"
#include "base/globals.h"

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

void TDevice::fillDataRow(TField p_no,QString &p_data)
{	
	switch(p_no){
		case TField::DEVICE_NAME:
			p_data=getName();
			break;
		case TField::PARTITION_NAME:
			p_data=QStringLiteral("");
			break;
		case TField::SIZE:
			p_data=QString::number(getSize());
			break;
		case TField::MODEL:
			p_data=getVendor()+"/"+getModel();
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
			p_data=(readonly?"X":"");
			break;
		case TField::REMOVABLE:
			p_data=(removable?"X":"");
			break;			
		case TField::LOOPBACKFILE:
			p_data=loopbackFile;
			break;
		case TField::SCSI_BUS:
			p_data=getScsiBus();
			break;
		case TField::ISCSI_HOST:
			p_data=getIScsiAddress();
			break;
		case TField::ROTATIONAL:
			p_data=getRotational()?"X":"";
			break;
		case TField::USB_BUS:
			p_data=getUsbBus();
			break;
		case TField::PCI_BUS:
			p_data=getPciBus();
			break;
		case TField::LVM_NAME:
			p_data=getLVMName();
			break;
		case TField::FREE_SPACE:
			p_data=(getHasFree()?QString::number(getFree()):QStringLiteral(""));
			break;
		case TField::START:
			p_data=QStringLiteral("");
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



bool TDevice::getFieldValue(TField p_no,QVariant &p_data)
{	
	switch(p_no){
		case TField::DEVICE_NAME:
			p_data=getName();
			break;
		case TField::PARTITION_NAME:
			p_data=QStringLiteral("");
			break;
		case TField::SIZE:
			p_data=(qlonglong)getSize();
			break;
		case TField::MODEL:
			p_data=getVendor()+"/"+getModel();
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
			p_data=readonly;
			break;
		case TField::REMOVABLE:
			p_data=removable;
			break;			
		case TField::LOOPBACKFILE:
			p_data=loopbackFile;
			break;
		case TField::SCSI_BUS:
			p_data=getScsiBus();
			break;
		case TField::ISCSI_HOST:
			p_data=getIScsiAddress();
			break;
		case TField::ROTATIONAL:
			p_data=getRotational();
			break;
		case TField::USB_BUS:
			p_data=getUsbBus();
			break;
		case TField::PCI_BUS:
			p_data=getPciBus();
			break;
		case TField::LVM_NAME:
			p_data=getLVMName();
			break;
		case TField::FREE_SPACE:
			p_data=(qlonglong)(getHasFree()?getFree():-1);
			break;
		case TField::START:
			p_data=QStringLiteral("");
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
 *  Checks if the device has partition
 *  
 *  \return  true device has partitions
 *           false device has no partitions
 */
bool TDevice::hasPartitions()
{
	return !partitions.isEmpty();
}

