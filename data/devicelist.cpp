
#include <QString>
#include <QDirIterator>
#include "devicelist.h"
#include "base/utils.h"
#include "partition.h"
#include "device.h"
#include "alias.h"
#include <QIODevice>

const char* MOUNTS_PATH="/proc/mounts";


void TDeviceList::readDevices()
{
	QString      l_deviceName;
	QDir         l_dir("/sys/block");
	QDirIterator l_iter(l_dir,QDirIterator::NoIteratorFlags);
	TDevice      *l_device;
	QString      l_model;
	QString      l_loopFile;
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
			} else if(l_dir.exists("loop")==1){
				l_model="Loopback";
				readString(l_iter.filePath(),"loop/backing_file",l_loopFile);				
			} else{
				l_model="??";
				l_loopFile="";
			}
			l_device=new TDevice(l_deviceName,l_model,l_size);
			l_device->setReadonly(l_readonly==1);
			l_device->setRemovable(l_removable==1);
			l_device->setLoopbackFile(l_loopFile);
			append(l_device);
			nameIndex.insert(l_deviceName,l_device);
			deviceByDevPath.insert(l_device->getDevPath(),l_device);
			readPartitions(l_device);
		}
	}
}

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


bool TDeviceList::readMounts(TAlias *p_aliasses)

{
	char        l_lineBuffer[256];
	int         l_read;
	QFile       l_file(MOUNTS_PATH);
	QString     l_line;
	QStringList l_parts;
	QString     l_deviceName;
	TDeviceBase *l_device;
	bool l_success=l_file.open(QIODevice::ReadOnly);
	if(!l_success) return false;

	while(true){
		l_read=l_file.readLine(l_lineBuffer,sizeof(l_lineBuffer));
		if(l_read==-1) break;
		l_line=l_lineBuffer;
		l_parts=l_line.split(" ");
		if(l_parts.size()>=3){
			if(p_aliasses->contains(l_parts[0])){
				l_deviceName=p_aliasses->getDeviceNameFromAliasPath(l_parts[0]);
			} else {
				QFileInfo l_info(l_parts[0]);
				l_deviceName=l_info.fileName();
				
			}
			l_device=getDeviceByName(l_deviceName);
			if(l_device != nullptr){
				l_device->addMount(l_parts[1],l_parts[2]);
				l_device->setType(l_parts[2]);
			}
		}
	}
	l_file.close();
	return true;
}

void TDeviceList::readAliases(TAlias *p_aliasses)
{
	readAliasFromPath("label","/dev/disk/by-label/",labelIndex,p_aliasses);
	readAliasFromPath("label","/dev/disk/by-partlabel/",labelIndex,p_aliasses);
	readAliasFromPath("uuid","/dev/disk/by-uuid/",uuidIndex,p_aliasses);
	readAliasFromPath("path","/dev/disk/by-path/",pathIndex,p_aliasses);
	readAliasFromPath("id","/dev/disk/by-id/",idIndex,p_aliasses);
	
}

void TDeviceList::readAliasFromPath(const QString &p_type,const QString &p_path,QMap<QString,TDeviceBase *> &p_index,TAlias *p_aliasses)
{
	QDir l_dir(p_path);
	QDirIterator l_iter(l_dir,QDirIterator::NoIteratorFlags);
	TDeviceBase *l_device;
	QString l_other;
	while(l_iter.hasNext()){		
		l_iter.next();
		if(l_iter.fileInfo().isSymLink()){
			l_other=p_aliasses->getDeviceNameFromAliasPath(l_iter.filePath());			
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


void TDeviceList::readInfo(TAlias* p_aliasses)
{
	readDevices();
	readMounts(p_aliasses);
	readAliases(p_aliasses);
	readLabels();
}


