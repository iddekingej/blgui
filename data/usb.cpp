#include "usb.h"
#include <QDirIterator>
#include <QStringList>
#include "base/utils.h"

/**
 * This is the start point of gathering USB information
 * 
 * This method scans /sys/bus/usb/devices and looking 
 * for directries in the form 1-1.6:1.2, this is the usb no.
 * 
 */
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

/**
 *  When readinfo find a folder in the form like A-B.C:D:E where a..e are numbers, the method checks
 *  folders that start with host
 * 
 * \param p_path     Path to scan
 * \param p_usbBus   USB bus currently processed
 */
void TUsbInfo::handleHost(QString p_path,QString &p_usbBus)
{
	QDirIterator l_iter(p_path,QStringList() << "host*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		handleTarget(l_iter.filePath(),p_usbBus);
	}
}

/**
 * Inside the host* folder found @see TUsbInfo::handleHost(QString,QString &) this method look at folders 
 * starting with  "target" 
 * 
 * \param p_path  - path of the host* folder found in TUsbInfo::handleHost
 * \param p_usbBus  - The current USB bus number
 */
void TUsbInfo::handleTarget(QString p_path,QString &p_usbBus)
{
	QDirIterator l_iter(p_path,QStringList() << "target*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		handleBus(l_iter.filePath(),p_usbBus);
	}
}

/**
 *  This method scans to folder with the format a:b:c:d inside the folder 
 *  found by @see TUsbInfo::handleTarget(QString,QString &).
 * 
 *  This is the scsi bus number to which the usb is connected
 *  This data is added to the hash list scsiBusIndex The index is the scsibus and the value is the usb bus.
 */
void TUsbInfo::handleBus(QString p_path,QString &p_usbBus)
{
	QDirIterator l_iter(p_path,QStringList() << "[0-9]*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		scsiBusIndex.insert(l_iter.fileName(),p_usbBus);
	}
}

/**
 *  Get USB bus by scsi bus
 * 
 * \param p_scsiBus  scsi bus.
 * \param p_usb     returns usb bus to which the scsi bus is connected
 * \return          True if scsibus is connected to a usb bus.
 *                  False if not connected to usb bus.
 */

bool TUsbInfo::getUsbBus(QString& p_scsiBus, QString& p_usb)
{
	if(scsiBusIndex.contains(p_scsiBus)){
		p_usb=scsiBusIndex[p_scsiBus];
		return true;
	}
	return false;
}

