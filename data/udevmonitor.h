#ifndef __UDEVMONITOR_H_
#define __UDEVMONITOR_H_
#include <libudev.h>
#include <QString>
#include <QSet>

/**
 * Monitors udev on state changes of devices
 * This system can detect add new device and remove device.
 */

class TUDevMonitor
{
private:
	struct udev         *udev=nullptr;
	struct udev_monitor *monitor=nullptr;
public:
	bool open();
	bool isSomethingChanged(QSet<QString> &p_added,QSet<QString> &p_removed);		
	~TUDevMonitor();
}
;
#endif
