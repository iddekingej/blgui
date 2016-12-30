#include "changemanager.h"
#include <klocalizedstring.h>


TChangeItem::TChangeItem(QDateTime p_date, QString& p_device, QString& p_message)
{
	date=p_date;
	device=p_device;
	message=p_message;
}

void TChangeManager::clear()
{
	mounted.clear();
	unmounted.clear();
	changeMonitor.clear();
}

TChangeManager::~TChangeManager()
{
	if(prvMounted != nullptr)delete prvMounted;
}

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


void TChangeManager::getChanged(TLinkList<TChangeItem> &p_what,bool &p_changed)
{
	QString l_what;
	
	TMTab *l_tab=new TMTab(info->getDevices());
	l_tab->setSourceFile(QStringLiteral("/proc/mounts"));
	l_tab->processInfo();
	
	p_changed=false;
	if(prvMounted==nullptr){
		prvMounted=l_tab;
		changeMonitor.open();
	} else {
		
			
		if(l_tab->notInOther(prvMounted,mounted)) p_changed=true;
		if(prvMounted->notInOther(l_tab,unmounted)) p_changed=true;
		if(changeMonitor.isSomethingChanged()) p_changed=true;
		getStringOfSet(mounted,i18n("mounted"),p_what);
		getStringOfSet(unmounted,i18n("unmounted"),p_what);
		getStringOfSet(changeMonitor.getAdded(),i18n("added"),p_what);
		getStringOfSet(changeMonitor.getRemoved(),i18n("removed"),p_what);		
		delete prvMounted;
		prvMounted=l_tab;		
	}
}
