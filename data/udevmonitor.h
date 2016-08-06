#ifndef __UDEVMONITOR_H_
#define __UDEVMONITOR_H_
#include <libudev.h>
#include <QString>


class TUDevMonitor
{
private:
		struct udev         *udev=nullptr;
		struct udev_monitor *monitor=nullptr;
		int waitFd;
public:
		bool open();
		bool isSomethingChanged(QString &p_comment);
}
;
#endif
