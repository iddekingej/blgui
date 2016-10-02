
#include <QString>
#include <QDir>
#include <QDirIterator>
#include "base/utils.h"
#include "raid.h"
#include "devicebase.h"
     

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


void TRaidInfo::addRaid(TDeviceBase *p_device,const QString &p_type,const QString &p_level,QList<TDeviceBase *>p_members)
{
	TRaidDevice *l_raid=AddRaidDevice(p_device,p_type,p_level);
	for(TDeviceBase *l_member:p_members){
		l_raid->addRaidDevice(l_member);
	}
}
