
#include <QString>
#include <QDirIterator>
#include "devicelist.h"
#include "base/utils.h"
#include "partition.h"
#include "device.h"
#include "alias.h"
#include "mtab.h"
#include <QIODevice>
#include <klocalizedstring.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <QTextStream>
#include <errno.h>

const char* MOUNTS_PATH="/proc/mounts";
//List of devices and retrives information about the device
//Information about the devices are read from the /sys/block /dev/disk /proc/mounts/ proc/swap 


//Read all block devices (not the partitions) by scanning /sys/block
//This routine determines:
//-Size
//-Removable
//-Read only
//-loopback file

void TDeviceList::readDevices()
{
	QString      l_deviceName;
	QDir         l_dir(QStringLiteral("/sys/block"));
	QDirIterator l_iter(l_dir,QDirIterator::NoIteratorFlags);
	TDevice      *l_device;
	QString      l_model;
	QString      l_loopFile;
	QString      l_vendor;
	QString      l_scsiBus="";
	TDiskSize    l_size;
	unsigned long  l_removable;
	unsigned long  l_readonly;
	
	while(l_iter.hasNext()){
		l_iter.next();
		l_deviceName=l_iter.fileName();
		if( l_deviceName != "." && l_deviceName != ".."){		
			QDir l_dir(l_iter.filePath());
			readLong(l_iter.filePath(),"size",l_size);
			l_size=l_size*512;
			readLong(l_iter.filePath(),"removable",l_removable);
			readLong(l_iter.filePath(),"ro",l_readonly);
			if(l_dir.exists("device")==1){
				readString(l_iter.filePath(),"device/model",l_model);					
				readString(l_iter.filePath(),"device/vendor",l_vendor);
			} else if(l_dir.exists("loop")==1){
//if /sys/block/<dev>/loop exists =>it is a loop back device read loopback file from loop/backing_file
				l_model="Loopback";
				readString(l_iter.filePath(),"loop/backing_file",l_loopFile);				
			} else{
				l_model="";
				l_loopFile="";
			}

			l_device=new TDevice(l_deviceName,l_model,l_size);
			l_device->setReadonly(l_readonly==1);
			l_device->setRemovable(l_removable==1);
			l_device->setLoopbackFile(l_loopFile);
			l_device->setScsiBus(l_scsiBus);
			l_device->setVendor(l_vendor.trimmed());

//finds scsi bus in /sys/bock/<dev>/device/scsi_device/	
//set device scsibus and add device to scsibus index
			QDir l_scsi("/sys/block/"+l_deviceName+"/device/scsi_device/");	
			if(l_scsi.exists()){
				QDirIterator l_scsiIter(l_scsi);
				while(l_scsiIter.hasNext()){
					
					l_scsiIter.next();
					if(l_scsiIter.fileName() != "." && l_scsiIter.fileName() != ".."){
						l_scsiBus=l_scsiIter.fileName();
						scsiIndex.insert(l_scsiBus,l_device);
						l_device->setScsiBus(l_scsiBus);
						break;
					}
					
				}
			}						
			append(l_device);
			nameIndex.insert(l_deviceName,l_device);
			deviceByDevPath.insert(l_device->getDevPath(),l_device);
			readPartitions(l_device);
		}
	}
}

//read information about mounded swap devices.
//Information is read from file /proc/swap.
//This routine set device type to "swap"

void TDeviceList::readSwap()
{
	QFile l_file(QStringLiteral("/proc/swaps"));
	if(!l_file.open(QIODevice::ReadOnly|QIODevice::Text)) return;
	QTextStream l_stream(&l_file);
	QString l_line;
	QString l_dev;
	TDeviceBase *l_device;
	l_line=l_stream.readLine();
	while(true){		
		if(l_stream.atEnd()) break;
		l_line=l_stream.readLine();
		l_dev=l_line.left(l_line.indexOf(' '));
		l_device=findDeviceByDevPath(l_dev);
		if(l_device){
			l_device->setType("swap");
		}		
		if(l_stream.atEnd()) break;
	}
}


//Read data from partitions belonging to block device p_device
void TDeviceList::readPartitions(TDevice* p_device)
{
	QDir         l_dir("/sys/block/"+p_device->getName());
	QDirIterator l_iter(l_dir,QDirIterator::NoIteratorFlags);
	TDiskSize    l_size;
	QString      l_deviceName;
	QString      l_sizeStr("size");
	TPartition   *l_partition;
	
	while(l_iter.hasNext()){
		l_iter.next();
		if(l_iter.fileInfo().isDir() && l_iter.fileName().startsWith(p_device->getName())){
			readLong(l_iter.filePath(),l_sizeStr,l_size);		
			l_size=l_size*512;
			l_deviceName=l_iter.fileName();		
			l_partition=p_device->addParition(l_deviceName,l_size);	
			nameIndex.insert(l_deviceName,l_partition);
			deviceByDevPath.insert(l_partition->getDevPath(),l_partition);
		}
	}	
}


//Read from all mounted devices the free size through statvfs
void TDeviceList::readFreeSpace()
{
	QMapIterator<QString,TDeviceBase *> l_iter(nameIndex);
	TDeviceBase *l_device;
	QString l_somePath;
	while(l_iter.hasNext()){
		l_device=l_iter.next().value();
		if(l_device->getMountStart() !=nullptr){
			struct statvfs l_info;
			//statvfs need some file at device. Using top directory (/.) of first mount point
			l_somePath=l_device->getMountStart()->getItem()->getMountPoint()+"/.";
			if((statvfs(l_somePath.toUtf8().data(),&l_info))==0){
				l_device->setFree(l_info.f_bsize*l_info.f_bfree);				
			} 
		}
		
	}
}


//under /dev/disk symlinks to the device are stored. The name of the symlink are 'aliases' of the device (e.g. device uuid,label,bus path etc..
///dev/mapper are LVM devices


void TDeviceList::readAliases()
{
	readAliasFromPath(QStringLiteral("label"),QStringLiteral("/dev/disk/by-label/"),labelIndex);
	readAliasFromPath(QStringLiteral("Part.label"),QStringLiteral("/dev/disk/by-partlabel/"),labelIndex);
	readAliasFromPath(QStringLiteral("uuid"),QStringLiteral("/dev/disk/by-uuid/"),uuidIndex);
	readAliasFromPath(QStringLiteral("path"),QStringLiteral("/dev/disk/by-path/"),pathIndex);
	readAliasFromPath(QStringLiteral("id"),QStringLiteral("/dev/disk/by-id/"),idIndex);
	readAliasFromPath(QStringLiteral("LVM"),QStringLiteral("/dev/mapper/"),lvmIndex);
	
}

void TDeviceList::readAliasFromPath(const QString &p_type,const QString &p_path,QMap<QString,TDeviceBase *> &p_index)
{
	QDir l_dir(p_path);
	QDirIterator l_iter(l_dir,QDirIterator::NoIteratorFlags);
	TDeviceBase *l_device;
	QString l_other;
	while(l_iter.hasNext()){		
		l_iter.next();
		if(l_iter.fileInfo().isSymLink()){
			l_other=aliasses->getDeviceNameFromAliasPath(l_iter.filePath());			
			l_device=nameIndex.value(l_other);
			if(l_device !=nullptr){
				p_index.insert(l_iter.fileName() ,l_device);			
				l_device->addAlias(p_type,l_iter.fileName());
			}
		}
	}
}

void TDeviceList::readLabels()
{
	QMapIterator<QString,TDeviceBase*> l_iter(labelIndex);
	while(l_iter.hasNext()){
		l_iter.next();
		l_iter.value()->setLabel(l_iter.key());
	}
}

/**
 * Read LVM device data
 * -setModel to LVM Device 
 * -read LVM members from slaves folder and set fs type to LVM Member
 */
void TDeviceList::readLVM()
{
	QDir l_dir("/sys/block/");
	QDirIterator l_iter(l_dir,QDirIterator::NoIteratorFlags);
	TDeviceBase *l_deviceBase;
	TDeviceBase *l_slaveDevice;	
	while(l_iter.hasNext()){
		l_iter.next();
		l_deviceBase=nameIndex.value(l_iter.fileName());
		
		if(l_deviceBase != nullptr){
			QDir l_slaves(l_iter.filePath());
			if(l_slaves.exists("dm")){
				if(TDevice *l_device=dynamic_cast<TDevice *>(l_deviceBase)){
					l_device->setModel(i18n("LVM Device"));
				}
				l_slaves.cd("slaves");
				if(l_slaves.exists()){
					QDirIterator l_slaveIter(l_slaves,QDirIterator::NoIteratorFlags);
					while(l_slaveIter.hasNext()){
						l_slaveIter.next();
						l_slaveDevice=nameIndex.value(l_slaveIter.fileName());
						if(l_slaveDevice != nullptr){
							l_slaveDevice->setType(i18n("LVM Member"));		
							l_deviceBase->addSlave(l_slaveDevice);
						}
					}
				}
			}
		}
	}
		
}

//Finds TDeviceBase by the path of device inode(or its symbolic link) 

TDeviceBase* TDeviceList::findDeviceByDevPath(const QString& p_devPath)
{
	QString l_name=aliasses->getDeviceNameFromAliasPath(p_devPath);
	if(l_name.length()==0){
		return  deviceByDevPath.value(p_devPath);

	} else {
		return getDeviceByName(l_name);
	}
}

TDeviceList::TDeviceList(TAlias *p_aliasses)
{
	aliasses=p_aliasses;
}

// For BTRFS raid the mount point from only one raid member is retrieved
// This routine copies the mount information to the other raid members.
void TDeviceList::sameMountPoint(const QList<TDeviceBase* >& p_list)
{
	TDeviceBase *l_copyFrom=nullptr;
	TDeviceBase *l_item;
	QListIterator<TDeviceBase *> l_iter(p_list);
	while(l_iter.hasNext()){
		l_item=l_iter.next();
		if(l_item->isMounted()){
			l_copyFrom=l_item;
			break;
		}
	}
	if(l_copyFrom != nullptr){
		l_iter.toFront();
		while(l_iter.hasNext()){
			l_item=l_iter.next();
			if(l_item != l_copyFrom){
				l_item->copyMount(l_copyFrom->getMountStart());
			}
		}
	}
}

//Read all information
void TDeviceList::readInfo()
{
	readDevices();
	readAliases();
	readLabels();
	readLVM();
	readSwap();
}


