#ifndef __CHANGEMANAGER_H_
#define __CHANGEMANAGER_H_
#include <QString>
#include "mtab.h"
#include "deviceinfo.h"
#include "udevmonitor.h"
class TChangeManager
{
private:
	QSet<QString>  mounted;
	QSet<QString>  unmounted;
	TMTab         *prvMounted=nullptr;
	TDeviceInfo   *info=nullptr;
	TUDevMonitor   changeMonitor;
public:
	QString getChanged();
	void clear();
	inline void setInfo(TDeviceInfo *p_info){ info=p_info;}
	~TChangeManager();
};

#endif