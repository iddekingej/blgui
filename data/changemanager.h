#ifndef __CHANGEMANAGER_H_
#define __CHANGEMANAGER_H_
#include <QString>
#include "mtab.h"
#include "deviceinfo.h"
#include "udevmonitor.h"
#include <QDateTime>
#include "base/linklist.h"
class TChangeItem
{
private:
	QDateTime date;
	QString device;
	QString message;
public:
	inline QDateTime &getDate(){ return date;}
	inline QString &getDevice(){ return device;}
	inline QString &getMessage(){ return message;}
	TChangeItem(QDateTime p_date,QString &p_device,QString &p_message);
};

class TChangeManager
{
private:
	QSet<QString>  mounted;
	QSet<QString>  unmounted;
	TMTab         *prvMounted=nullptr;
	TDeviceInfo   *info=nullptr;
	TUDevMonitor   changeMonitor;
	
	void getStringOfSet(const QSet<QString >& p_set, QString p_text,TLinkList<TChangeItem> &p_what);
public:
	void getChanged(TLinkList<TChangeItem> &p_what,bool &p_changed);
	void clear();
	inline void setInfo(TDeviceInfo *p_info){ info=p_info;}
	~TChangeManager();
	
};

#endif
