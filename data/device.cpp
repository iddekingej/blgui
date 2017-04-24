#include "device.h"
#include "base/utils.h"
#include "base/compat.h"
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
		case FIELD_DEVICE_NAME:
			p_data=getName();
			break;
		case FIELD_PARTITION_NAME:
			p_data=QStringLiteral("");
			break;
		case FIELD_SIZE:
			p_data=QString::number(getSize());
			break;
		case FIELD_MODEL:
			p_data=getVendor()+"/"+getModel();
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
			p_data=(readonly?"X":"");
			break;
		case FIELD_REMOVABLE:
			p_data=(removable?"X":"");
			break;			
		case FIELD_LOOPBACKFILE:
			p_data=loopbackFile;
			break;
		case FIELD_SCSI_BUS:
			p_data=getScsiBus();
			break;
		case FIELD_ISCSI_HOST:
			p_data=getIScsiAddress();
			break;
		case FIELD_ROTATIONAL:
			p_data=getRotational()?"X":"";
			break;
		case FIELD_USB_BUS:
			p_data=getUsbBus();
			break;
		case FIELD_PCI_BUS:
			p_data=getPciBus();
			break;
		case FIELD_LVM_NAME:
			p_data=getLVMName();
			break;
		case FIELD_FREE_SPACE:
			p_data=(getHasFree()?QString::number(getFree()):QStringLiteral(""));
			break;
		case FIELD_START:
			p_data=QStringLiteral("");
			break;
		case FIELD_FREE_SPACE_KMG:
			p_data=getReadableFreeSize();
			break;
		case FIELD_VG_NAME:
			p_data=getVGName();
			break;
		case FIELD_SLAVES:
			p_data=getSlavesString();
			break;
		default:
			p_data=QStringLiteral("Invalid field no:")+QString::number(p_no);
	}
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

