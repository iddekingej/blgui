/**
 *   This class monitors changes on file system 
 *   -udev is used for adding and removing devices
 *   -rereading /proc/mounts(=mtab) is used for detecting mounting/unmounting
 * 
 *   Informationc ollected by the TChangeManager is displayed in the notification message
 */

#ifndef __CHANGEMANAGER_H_
#define __CHANGEMANAGER_H_
#include <QString>
#include "mtab.h"
#include "deviceinfo.h"
#include "udevmonitor.h"
#include <QDateTime>
#include "base/linklist.h"

/**
 * A change in a device state is stored in this item
 * */
class TChangeItem
{
private:
	
/**
 *  Data of change. This is displayed at the notification
 */
	QDateTime date;
	
/**
 * Device name which state is changed.
 */
	QString device;
/**
 * Message describing the change
 */	

	QString message;
	
public:
	inline QDateTime &getDate(){ return date;}
	inline const QString &getDevice(){ return device;}
	inline const QString &getMessage(){ return message;}
	TChangeItem(QDateTime p_date,const QString &p_device,const QString &p_message);
};

class TChangeManager
{
private:
/**
 *  Periodically mtab (=/proc/mounts) is read and compared to the previous mount information. Every difference is 
 *  added to the change list.
 *  This property contains the previous /proc/mounts information
 */
	TMTab         *prvMounted=nullptr;
/**
 *  Device information list.
 */
	TDeviceInfo   *info=nullptr;
	
/**
 * changeMonitor is a interface to udev. This object returns 
 * device that are added or removed from the system
 */
	TUDevMonitor   changeMonitor;
/**
 * List of changed items
 */
	TLinkList<TChangeItem> changes;
	void getStringOfSet(const QSet<QString >& p_set, QString p_text);
	void getStringOfDiff(TLinkList<TMountDiff> &p_diff,QString p_text);
public:
	inline TLinkList<TChangeItem> *getChanges(){ return &changes;}
	void getChanged(bool &p_changed);
	void clear();
	inline void setInfo(TDeviceInfo *p_info){ info=p_info;}
	~TChangeManager();
	
};

#endif
