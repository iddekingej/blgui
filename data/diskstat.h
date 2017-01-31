/**
 * This class read statics information of devices
 */
#ifndef __DISKSTAT_H_
#define __DISKSTAT_H_
#include <QString>
#include <QMap>
#include "base/linklist.h"

/**
 *  This class contains static information of one device
 *  It is read from /sys/block/#device/stat file
 */
class TDiskStat
{
private:
	/**
	 * Device name (e.g. sda)
	 */
	QString device;
	/*
	 */
	long readIO;
	long readMerges;
	long readSectors;
	long readTicks;
	long writeIO;
	long writeMerges;
	long writeSectors;
	long writeTicks;
	long inFlight;
	long ioTicks;
	long timeInQueue;
	
public:
	int getReadIO(){ return readIO;}
	int getWriteIO(){return writeIO;}
	int getReadSectors(){ return readSectors;}
	int getWriteSectors(){ return writeSectors;}
	const QString &getDevice(){ return device;}
	TDiskStat(QString p_device,QString p_line);
};

class TDiskStatList{
private:
	TLinkList<TDiskStat> list;
	QMap<QString,TDiskStat *> nameIndex;
public:
	TLinkList<TDiskStat> *getList(){ return &list;}
	TDiskStat *getByName(const QString &p_name){ return nameIndex.value(p_name);}
	void readInfo();
};

#endif
