#ifndef __MTAB_H_
#define __MTAB_H_

#include <QString>
#include <QSet>
#include "base/linklist.h"
#include "data/devicebase.h"
#include "data/devicelist.h"
class TMTabEntry
{
private:
	QString      device;
	QString      mountPoint;
	QString      type;
	QString      options;
	TDeviceBase *realDevice;
	
public:
	enum TMountStatus{ MOUNTED,NOTMOUNTED,UNKMOUNTED,DIFMOUNTED};
	enum TSameType{ SAMETYPE,NOTSAMETYPE,UNKNOWNSAMETYPE};
	inline const QString &getDevice(){ return device;}
	inline const QString &getMountPoint(){ return mountPoint;}
	inline const QString &getType(){ return type;}
	inline const QString &getOptions(){ return options;}
	inline TDeviceBase *getRealDevice(){ return realDevice;}
	
	TMountStatus isMounted();
	TSameType isSameType();
	
	TMTabEntry(const QString &p_device,TDeviceBase *p_realDevice,const QString &p_mountPoint,const QString &p_type,const QString &p_options);
	
	
};

class TMTab{
private:
	TLinkList<TMTabEntry> entries;
	TDeviceList           *devList;
	QString               sourceFile;
public:
	inline TLinkListItem<TMTabEntry> *getEntriesStart(){ return entries.getStart();}
	inline QString getSourceFile(){ return sourceFile;}
	inline void setSourceFile(const QString &p_sourceFile){ sourceFile=p_sourceFile;}
	TMTab(TDeviceList *p_devList);
	bool processLine(const QString &p_line);
	bool untilNext(const QString& p_text, int& p_cnt);
	void nextItem(const QString &p_text,QString &p_out,int &p_cnt);
	bool hasMount(const QString &p_device,const QString &p_mountPoint);
	bool notInOther(TMTab *p_other,QSet<QString>&p_return);
	void processInfo();
};
#endif