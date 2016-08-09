#ifndef __UDEVMONITOR_H_
#define __UDEVMONITOR_H_
#include <libudev.h>
#include <QString>
#include <QSet>

class TUDevMonitor
{
private:
		struct udev         *udev=nullptr;
		struct udev_monitor *monitor=nullptr;
		int waitFd;
		QSet<QString> added;
		QSet<QString> removed;
		
public:
		bool open();
		bool isSomethingChanged();
		void clear();
		inline const QSet<QString> &getAdded(){ return added;}
		inline const QSet<QString> &getRemoved(){ return removed;}
}
;
#endif
