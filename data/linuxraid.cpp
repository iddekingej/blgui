#include "linuxraid.h"
#include "raid.h"
#include <QDirIterator>
/**
 *  Read informationa about linux software raid devices and adds it to the raid list (p_raid)
 *  When a storage device is a  linux soft wate, the /sys/block/#block device# folder contains a 
 *  "md" folders
 *  This folder contains the raid info
 *  The slaves folder contains the raid members
 *  
 *  \param p_list Information about all devices on the system
 *  \param p_raid Raid information list. The linux soft raids are added to this 
 */
void TLinuxRaid::processInfo(TDeviceList* p_list,TRaidInfo *p_raid)
{
	QString      l_level;		
	QDirIterator l_devIter("/sys/block/",QDirIterator::NoIteratorFlags);
	TDeviceBase  *l_deviceBase;
	TRaidDevice  *l_raid;
	TDeviceBase  *l_slave;
	while(l_devIter.hasNext()){
		l_devIter.next();
		QDir l_dir(l_devIter.filePath() );
		
		if(l_dir.exists("md")){
			l_dir.cd("md");
			readString(l_dir.path(),"level",l_level);
			l_deviceBase=p_list->getDeviceByName(l_devIter.fileName());
			
			if(l_deviceBase){
				if(TDevice *l_device =dynamic_cast<TDevice *>(l_deviceBase)){
					l_raid=p_raid->AddRaidDevice(l_device,"linux raid",l_level);
					l_device->setModel("Linux raid");
					l_dir.cd("../slaves");
					QDirIterator l_iter(l_dir);
					while(l_iter.hasNext()){
						l_iter.next();
						l_slave=p_list->getDeviceByName(l_iter.fileName());
						if(l_slave)l_raid->addRaidDevice(l_slave);
					}
				}
			}
		}
	}
}
