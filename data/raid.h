#ifndef __RAID_H_
#define __RAID_H_

#include <QStringList>
#include <QString>
#include "base/linklist.h"
#include "btrfs.h"
#include "device.h"
#include "devicelist.h"

class TRaidDevice
{
private:
	QStringList  raidDevices;
	QString      raidLevel;
	TDeviceBase *device;
	QString      type;
public:
	inline const QStringList &getRaidDevices()
	{
		return raidDevices;
	}
	
	inline const QString &getRaidLevel()
	{
		return raidLevel;
	}
	
	inline TDeviceBase *getDevice()
	{
		return device;
	}
	
	inline const QString &getType()
	{
		return type;
	}
	
	inline void addRaidDevice(QString p_device)
	{
		raidDevices << p_device;
	}
	
	inline void addRaidDevices(QStringList p_device)
	{
		raidDevices << p_device;
	}
	
	QString getRaidDeviceString()
	{
		return raidDevices.join(",");
	}
	
	TRaidDevice(TDeviceBase *p_device,const QString &p_type,const QString &p_level);
}
;
class TRaidInfo
{
private:
	TLinkList<TRaidDevice>devices;
public:
	inline TLinkListItem<TRaidDevice> *getTop(){
		return devices.getStart();
	}

	int getLength()
	{
		return devices.getLength();
	}	
	
	TRaidDevice *AddRaidDevice(TDeviceBase *p_device,const QString &p_type,const QString &p_raidLevel);
	void processMD(TDeviceList *p_list);
	void processBtrfs(TBtrfsInfo *p_info,TDeviceList *p_list);
}
;
#endif
