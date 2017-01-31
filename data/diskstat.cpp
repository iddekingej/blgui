#include "data/diskstat.h"
#include <QString>
#include <QMap>
#include <QDirIterator>
#include "base/utils.h"
/**
 * /sys/blck/#device/stat contains information about device io statistics
 * The file contains one line, with statics data  separated by a spaces
 * 
 * \param p_device devicename 
 * \param p_line   line read from stat file
 */
TDiskStat::TDiskStat(QString p_device,QString p_line)
{
	QStringList l_data=p_line.split(" ",QString::SkipEmptyParts);
	device=p_device;
	if(l_data.length() == 11){
		readIO=l_data[0].toULong() ;
		readMerges=l_data[1].toULong();
		readSectors=l_data[2].toULong();
		readTicks=l_data[3].toULong();
		writeIO=l_data[4].toULong();
		writeMerges=l_data[5].toULong();
		writeSectors=l_data[6].toULong();
		writeTicks=l_data[7].toULong();
		inFlight=l_data[8].toULong();
		ioTicks=l_data[9].toULong();
		timeInQueue=l_data[10].toULong();
	} else {		
		readIO=0;
		readMerges=0;
		readSectors=0;
		readTicks=0;
		writeIO=0;
		writeMerges=0;
		writeSectors=0;
		writeTicks=0;
		inFlight=0;
		ioTicks=0;
		timeInQueue=0;
		
	}
}

/**
 *  Read statics of all files
 *  This method scan /sys/block on all devices and reads on line from the stat file.
 *  This data is used to create the TStatInfo object.s
 */

void TDiskStatList::readInfo()
{
	QDirIterator l_iter("/sys/block/",QDirIterator::NoIteratorFlags);
	QString l_path;
	QString l_stat;
	TDiskStat *l_info;
	while(l_iter.hasNext()){
		l_iter.next();
		l_path=l_iter.filePath();
		readString(l_path,"stat",l_stat);
		if(l_stat.length()>0){
			l_info =new TDiskStat(l_iter.fileName(),l_stat);
			list.append(l_info);
			nameIndex.insert(l_info->getDevice(),l_info);
		}
	}

}
