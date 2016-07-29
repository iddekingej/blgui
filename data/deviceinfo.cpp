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


QString TDeviceInfo::getTypeByDevice(TDeviceBase *p_device)
{
	QString l_type;	
	char *l_value;
	QString l_devName= p_device->getDevPath();
	

	if(btrfsInfo->isBtrfs(p_device->getName())){
		l_type="btrfs";
	} else{ 				
		l_value=blkid_get_tag_value(blkidCache,"TYPE",l_devName.toUtf8().data());				
		if(l_value != NULL){
			l_type=l_value;
			free(l_value);
		} else{
			l_type="??";
		}
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

	if (blkid_get_cache(&blkidCache, NULL) < 0){
		printf("Failed to cache\n");
	 }	
	aliasses->readInfo();
	devices->readInfo();
	btrfsInfo->readInfo(aliasses);
	raidList->processMD(devices);
	raidList->processBtrfs(btrfsInfo,devices);
	mtab->processInfo();
	
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
			l_partLabel=QString(blkid_get_tag_value(blkidCache,"PARTLABEL",l_devicePath.toUtf8().data()));
			l_db->setLabel(l_partLabel);
		}
	}
	

}

TDeviceInfo::TDeviceInfo()
{	
	btrfsInfo=new TBtrfsInfo();
	
	aliasses =new TAlias();
	devices  =new TDeviceList(aliasses);
	raidList =new TRaidInfo();
	mtab     =new TMTab(devices);
}
TDeviceInfo::~TDeviceInfo(){
	delete btrfsInfo;
	delete devices;
	delete aliasses;
	delete raidList;
	delete mtab;
	blkid_put_cache(blkidCache);
}