#include <stdio.h>
#include <blkid/blkid.h>
#include <QString>
#include <limits.h>
#include <QFile>
#include <stdlib.h>

#include "deviceinfo.h"
#include "base/utils.h"
#include "base/linklist.h"
#include "btrfs.h"
#include "raid.h"
#include "device.h"
#include "partition.h"
#include "mtab.h"
#include "iscsi.h"
#include "linuxraid.h"
#include "base/utils.h"

QString TDeviceInfo::getTypeByDevice(TDeviceBase *p_device)
{
	QString l_type;	
	char *l_value;
	QString l_devName= p_device->getDevPath();
		
	l_value=blkid_get_tag_value(blkidCache,"TYPE",qstr(l_devName));				
	if(l_value != NULL){
		l_type=l_value;
		free(l_value);
	} else{
		l_type="??";
	}

	return l_type;
}



void TDeviceInfo::getDisks()
{		

	QString l_type;
	QFile   l_file;		
	TDeviceBase *l_db;
	QString l_partLabel;
	QString l_devicePath;
	char *l_label;

	if (blkid_get_cache(&blkidCache, NULL) < 0){
		printf("Failed to cache\n");
	 }	
	aliasses->readInfo();
	devices->readInfo();
	mtab->processInfo();
	TMTab *l_mtab2=new TMTab(devices);
	l_mtab2->setSourceFile("/proc/mounts");
	l_mtab2->processInfo();
	l_mtab2->addMountTODevices();	
	l_mtab2->copyFileType();
	delete l_mtab2;
	TBtrfsInfo::processInfo(devices,raidList);
	TLinuxRaid::processInfo(devices,raidList);
	devices->readFreeSpace();
	iscsi->processInfo(devices);
	
	
	QMapIterator<QString,TDeviceBase *> l_mi(*devices->getNameIndex());
	while(l_mi.hasNext()){
		l_mi.next();
		l_db=l_mi.value();
		if(!l_db->hasPartitions()){
			if(l_db->getType().length()==0){
				l_type=getTypeByDevice(l_db);
				l_db->setType(l_type);
			}
		}
		if(l_db->getLabel().length()==0){
			l_devicePath=l_db->getDevPath();
			l_label=blkid_get_tag_value(blkidCache,"PARTLABEL",qstr(l_devicePath));
			l_partLabel=l_label;
			free(l_label);
			l_db->setLabel(l_partLabel);
		}
	}
	sbTime=QFileInfo("/sys/block").lastModified();
}

TDeviceInfo::TDeviceInfo()
{	

	aliasses = new TAlias();
	devices  = new TDeviceList(aliasses);
	raidList = new TRaidInfo();
	mtab     = new TMTab(devices);	
	iscsi    = new TIScsiSessionList();
}
TDeviceInfo::~TDeviceInfo(){
	delete devices;
	delete aliasses;
	delete raidList;
	delete mtab;
	delete iscsi;
	blkid_put_cache(blkidCache);
}
