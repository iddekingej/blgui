#ifndef __USB_H_
#define __USB_H_

#include <QString>
#include "base/linklist.h"
#include <QHash>
/**
 *  For retrieving usb connected to a storage device
 */

class TUsbInfo
{
private:
	QHash<QString,QString> scsiBusIndex;
	void handleHost(QString p_path,QString &l_usbBus);
	void handleTarget(QString p_path,QString &l_usbBus);
	void handleBus(QString p_path,QString &l_usbBus);
public:
	bool getUsbBus(QString &p_scsiBus,QString &p_usb);
	
	void readInfo();
	
	
};

#endif
