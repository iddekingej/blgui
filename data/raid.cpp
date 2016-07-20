
#include <QString>
#include <QDir>
#include <QDirIterator>
#include "base/utils.h"
#include "raid.h"
#include  "device.h"
     

TRaidDevice::TRaidDevice(TDeviceBase *p_device,const QString &p_type,const QString &p_level)
{
	device=p_device;
	type=p_type;
	raidLevel=p_level;	
}

TRaidDevice *TRaidInfo::AddRaidDevice(TDeviceBase *p_device,const QString &p_type,const QString &p_raidLevel)
{
	TRaidDevice *l_info=new TRaidDevice(p_device,p_type,p_raidLevel);
	devices.append(l_info);
	return l_info;
}

void TRaidInfo::processMD(TDeviceList *p_list)
{
	QString      l_level;		
	QString      l_fileName;
	QDir         l_devDir("/sys/block/");
	QDirIterator l_devIter(l_devDir,QDirIterator::NoIteratorFlags);
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
					l_raid=AddRaidDevice(l_device,"linux raid",l_level);
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


void TRaidInfo::processBtrfs(TBtrfsInfo* p_info,TDeviceList *p_list)
{
	TDeviceBase *l_device;
	TDeviceBase *l_slave;
	TRaidDevice *l_raid;
	TLinkListItem<TBtrfsItem> *l_current=p_info->getStart();
	while(l_current != nullptr){
		if(l_current->getItem()->isMultiDev()){
			l_device=p_list->getDeviceByName(l_current->getItem()->getFs());
			l_raid=AddRaidDevice(l_device,"btrfs",l_current->getItem()->getRaidLevel());
			QStringListIterator l_iter(l_current->getItem()->getDevices());
			while(l_iter.hasNext()){
				l_slave=p_list->getDeviceByName(l_iter.next());
				if(l_slave){
					l_raid->addRaidDevice(l_slave);		
				}
			}
		}
		l_current=l_current->getNext();
	}
}
