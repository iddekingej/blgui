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
	void getChanged(QString &p_what,bool &p_changed);
	void clear();
	inline void setInfo(TDeviceInfo *p_info){ info=p_info;}
	~TChangeManager();
	void getStringOfSet(const QSet< QString >& p_set, QString p_text,QString &p_return);
};

#endif