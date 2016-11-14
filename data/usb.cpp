#include "usb.h"
#include <QDirIterator>
#include <QStringList>
#include "base/utils.h"


void TUsbInfo::readInfo()
{
	QDirIterator l_iter("/sys/bus/usb/devices/");
	QString l_path;
	while(l_iter.hasNext()){
		l_iter.next();
		l_path=l_iter.fileName();
		if(l_path[0]>'0' && l_path[0]<'9' ){
			if(l_path.indexOf(":")!=-1){
				handleHost(l_iter.filePath(),l_path);
			}
		}
	}
}


void TUsbInfo::handleHost(QString p_path,QString &p_usbBus)
{
	QDirIterator l_iter(p_path,QStringList() << "host*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		handleTarget(l_iter.filePath(),p_usbBus);
	}
}

void TUsbInfo::handleTarget(QString p_path,QString &p_usbBus)
{
	QDirIterator l_iter(p_path,QStringList() << "target*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		handleBus(l_iter.filePath(),p_usbBus);
	}
}

void TUsbInfo::handleBus(QString p_path,QString &p_usbBus)
{
	QDirIterator l_iter(p_path,QStringList() << "[0-9]*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		scsiBusIndex.insert(l_iter.fileName(),p_usbBus);
	}
}

bool TUsbInfo::getUsbBus(QString& p_scsiBus, QString& p_usb)
{
	if(scsiBusIndex.contains(p_scsiBus)){
		p_usb=scsiBusIndex[p_scsiBus];
		return true;
	}
	return false;
}

