#ifndef __MTAB_H_
#define __MTAB_H_
#include <QString>
#include "base/linklist.h"
#include "devicelist.h"
#include "devicebase.h"

class TMTabEntry{
private:
	QString     device;
	QString     mountPoint;
	QString     options;
	QString     type;
	TDeviceBase *realDevice;
public:
	enum TSameType{SAMETYPE,NOTSAMETYPE,UNKNOWNTYPE};
	enum TMountState{ MOUNTED,NOTMOUNTED,DIFMOUNTED,MOUNTUNKNOWN};
	inline QString getDevice(){ return device;}
	inline QString getMountPoint(){ return mountPoint;}
	inline QString getOptions(){ return options;}
	inline QString getType(){ return type;}
	inline TDeviceBase *getRealDevice(){ return realDevice;}
	TMTabEntry(QString p_device,TDeviceBase *p_realDevice,QString p_mountPoint,QString p_type,QString p_options);
	TMountState isMounted();
	TSameType   isSameType();
};

class TMTab{
private:
	TLinkList<TMTabEntry> entries;
	TDeviceList *devList;
	QString scanToSpace(const QString &p_string,int &p_cnt);
	bool scanToNext(const QString &p_string,int &p_cnt);
	bool processLine(const QString &p_line);
public:
	inline TLinkListItem<TMTabEntry> *getEntriesStart()
	{
		return entries.getStart();
	}
	
	void processInfo();
	TMTab(TDeviceList *p_devList);

};
#endif