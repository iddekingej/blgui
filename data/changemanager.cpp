#include "changemanager.h"
#include <klocalizedstring.h>
#include "mountdiff.h"
#include "base/linklist.h"


/**
 * A change items contains information about changes in device states
 * 
 * \param p_date  date of change
 * \param p_device name of device
 * \param p_message message describing  the change.
 */

TChangeItem::TChangeItem(QDateTime p_date, const QString& p_device, const QString& p_message)
{
	date=p_date;
	device=p_device;
	message=p_message;
}


/**
 * Clears the udev change monitor.
 */

void TChangeManager::clear()
{
	changeMonitor.clear();
}

TChangeManager::~TChangeManager()
{
	if(prvMounted != nullptr)delete prvMounted;
}

/**
 * The UDev change manager returns a QSet of added or removed devices 
 * 
 * This routine adds the devices to the change list.
 * 
 * \param p_set  list of devices
 * \param p_message message  describing the change
 * \param p_what    All changed devices are added to this list.
 */
void TChangeManager::getStringOfSet(const QSet< QString >& p_set, QString p_message,TLinkList<TChangeItem> &p_what)
{
	
	QSetIterator<QString> l_iter(p_set);
	TChangeItem *l_change;
	QString     l_device;
	while(l_iter.hasNext()){
		l_device=l_iter.next();
		l_change=new TChangeItem(QDateTime::currentDateTime(),l_device,p_message );
		p_what.append(l_change);
	}
}

/**
 *  Unmount /mounts are detected by periodically reading mtab and compare it with the previous version
 *  The difference is stored in a list of TMountDiff's. 
 * 
 *  This information is added to the change list.
 * 
 *  \param p_diff   List of changed mtab items
 *  \param p_text   Message describing the state change (mounted or unmounted)
 */

void TChangeManager::getStringOfDiff(TLinkList<TMountDiff>& p_diff, QString p_text, TLinkList<TChangeItem>& p_what)
{	
	TLinkListIterator<TMountDiff> l_iter(p_diff);
	TChangeItem *l_change;
	TMountDiff *l_diff;
	
	while(l_iter.hasNext()){
		l_diff=l_iter.next();
		l_change=new TChangeItem(QDateTime::currentDateTime(),l_diff->getDevice(),p_text+" '"+l_diff->getPath()+"'");
		p_what.append(l_change);
	}
}

/**
 *  Get the devices changes:
 *  -read /proc/mount(=mtab) and compare it with the previous read.
 *  -get change information from udev 
 * Next tranform the information to change item
 * 
 *  \param p_what  List of changed items
 *  \param p_changed true when there are changes, flase if there are no changes
 */

void TChangeManager::getChanged(TLinkList<TChangeItem> &p_what,bool &p_changed)
{
	QString l_what;
	
	TMTab *l_tab=new TMTab(info->getDevices());
	TLinkList<TMountDiff> l_mounted;
	TLinkList<TMountDiff> l_unmounted;
	l_tab->setSourceFile(QStringLiteral("/proc/mounts"));
	l_tab->processInfo();
	
	p_changed=false;
	if(prvMounted==nullptr){
		prvMounted=l_tab;
		changeMonitor.open();
	} else {
		
			
		if(l_tab->notInOther(prvMounted,l_mounted)) p_changed=true;
		getStringOfDiff(l_mounted,"mounted",p_what);
		if(prvMounted->notInOther(l_tab,l_unmounted)) p_changed=true;
		getStringOfDiff(l_unmounted,"unmounted",p_what);
		if(changeMonitor.isSomethingChanged()) p_changed=true;

		getStringOfSet(changeMonitor.getAdded(),i18n("added"),p_what);
		getStringOfSet(changeMonitor.getRemoved(),i18n("removed"),p_what);		
		delete prvMounted;
		prvMounted=l_tab;		
	}
}
