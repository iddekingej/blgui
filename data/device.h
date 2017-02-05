#ifndef __DEVICE_H_
#define __DEVICE_H_
#include "devicebase.h"
#include "base/linklist.h"
#include "partition.h"
#include <QString>

/**
 *  Information about devices
 */
class TDevice:public TDeviceBase
{
private:
	/**
	* List of partitions on device
	*/
	TLinkList<TPartition> partitions;	
	
	/**
	* Model of device
	*/
	QString model;
	
	/**
	 * Vendor of device 
	 */
	QString vendor;
	/**
	 * When the device is readonly
	 */
	bool    readonly=false;
	
	/**
	 * flag indicating if it is a removeable type
	 */
	bool    removable=false;
	
	/**
	 * If the device is a loopback device, this field contains the file used for the loopback.
	 */
	QString loopbackFile;
	/**
	 * Scsi bus of the adres
	 */
	QString scsiBus;
	/**
	 * IP adres  of the nas of iscsi device
	 */
	QString iscsiAddress;
	/**
	 * USB Bus of the device
	 */
	QString usbBus;
	/**
	 * PCI Bus of the device
	 */
	QString pciBus;
	
	/**
	 * LVM name when device is a LVM (device mapper) device
	 */
	QString LVMName;
	bool    rotational=false;
public:
	/** Set lvm name
	 *\param p_LVMName  name of lvm 
	 */
	
	inline void setLVMName(QString &p_LVMName)
	{
		LVMName=p_LVMName;
	}
	
	inline QString &getLVMName(){
		return LVMName;
	}
	
	/** \brief  flag is device is rotational (has spinning disk) flags probably means it's a ssd
	 * 
	 */
	inline bool getRotational()
	{
		return rotational;
	}
	
	/** \brief set rotational true=>Disk has a spinning disk false it is probably a ssd. read from \sys\block\??\queue\rotational
	 *  \param p_rotational  boolean, value of the flag
	 */
	
	inline void setRotational(bool p_rotational)
	{
		rotational=p_rotational;
	}
	
	inline const QString &getIScsiAddress(){
		return iscsiAddress;
	}
	
	inline void setIscsiAddress(QString p_address){
		iscsiAddress=p_address;
	}
	
	inline const QString &getUsbBus(){
		return usbBus;
	}
	
	inline void setUsbBus(const QString &p_usbBus)
	{
		usbBus=p_usbBus;
	}
	
	inline const QString &getScsiBus(){
		return scsiBus;
	}
	
	inline void setPciBus(const QString &p_pciBus)
	{
		pciBus=p_pciBus;
	}
	
	inline const QString &getPciBus(){
		return pciBus;
	}
	
	void setScsiBus(const QString &p_scsiBus)
	{
		scsiBus=p_scsiBus;
	}
	
	inline int getNumPartitions()
	{
		return partitions.getLength();
	}
	
	
	inline const QString &getLoopbackFile()
	{
		return loopbackFile;
	}
	
	inline void setLoopbackFile(const QString &p_file)
	{
		loopbackFile=p_file;
	}

	inline bool getReadonly()
	{
		return readonly;
	}
	
	inline void setReadonly(bool p_readonly)
	{
		readonly=p_readonly;
	}
	
	inline bool getRemovable()
	{
		return removable;
	}
	
	inline void setRemovable(bool p_removable)
	{
		removable=p_removable;
	}
	
	TLinkListItem<TPartition> *getPartitionStart()
	{
		return partitions.getStart();
	}

	inline void setVendor(const QString &p_vendor)
	{
		vendor=p_vendor;
	}
	
	inline QString &getVendor(){
		return vendor;
	}
	
	inline void setModel(const QString &p_model)
	{
		model=p_model;
	}
	
	inline TLinkList<TPartition> *getPartitions(){ return &partitions;}
	
	const QString &getModel();
	virtual void fillDataRow(QStringList &p_list);

	TDevice(const QString &p_name,TDiskSize p_size);
	TPartition *addParition(const QString &p_name,TDiskSize p_size,TDiskSize p_start);
	bool hasPartitions();
};
#endif
