#include "changemanager.h"
#include <klocalizedstring.h>


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

void TChangeManager::getStringOfSet(const QSet< QString >& p_set, QString p_text,QString &p_return)
{
	
	QSetIterator<QString> l_iter(p_set);
	while(l_iter.hasNext()){
		if(p_return.length()>0) p_return += ",";
		p_return += l_iter.next()+" "+p_text;
	}
}


void TChangeManager::getChanged(QString &p_what,bool &p_changed)
{
	static const char *empty="";
	QString l_what;
	
	TMTab *l_tab=new TMTab(info->getDevices());
	l_tab->setSourceFile(QStringLiteral("/proc/mounts"));
	l_tab->processInfo();
	
	p_what="";
	p_changed=false;
	if(prvMounted==nullptr){
		prvMounted=l_tab;
		changeMonitor.open();
	} else {
		
			
		if(l_tab->notInOther(prvMounted,mounted)) p_changed=true;
		if(changeMonitor.isSomethingChanged()) p_changed=true;
		getStringOfSet(mounted,i18n("mounted"),p_what);
		getStringOfSet(unmounted,i18n("unmounted"),p_what);
		getStringOfSet(changeMonitor.getAdded(),i18n("added"),p_what);
		getStringOfSet(changeMonitor.getRemoved(),i18n("removed"),p_what);
		

		
		//Check udev for any device new or remove block devices 
		delete prvMounted;
		prvMounted=l_tab;		
	}
}
