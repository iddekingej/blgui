#ifndef __USB_H_
#define __USB_H_

#include <QString>
#include "base/linklist.h"
#include <QHash>

/**
 *  For retrieving infromation USB bus
 */

class TUsbInfo
{
private:
	/**
	 * USB bus indexed by scsibus
	 * When reading information about block devices from /sys/block, the scsi bus is known.
	 * The information in scsiBusIndex is uded to translate this to the USB bus
	 */
	QHash<QString,QString> scsiBusIndex;
	void handleHost(QString p_path,QString &l_usbBus);
	void handleTarget(QString p_path,QString &l_usbBus);
	void handleBus(QString p_path,QString &l_usbBus);
public:
	bool getUsbBus(QString &p_scsiBus,QString &p_usb);
	
	void readInfo();
	
	
};

#endif
