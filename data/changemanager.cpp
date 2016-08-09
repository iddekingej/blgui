#include "changemanager.h"
#include <klocalizedstring.h>


void TChangeManager::clear()
{
	mounted.clear();
	unmounted.clear();;
}

TChangeManager::~TChangeManager()
{
	if(prvMounted != nullptr)delete prvMounted;
}


QString TChangeManager::getChanged()
{
	QString l_what;
	
	TMTab *l_tab=new TMTab(info->getDevices());
	l_tab->setSourceFile(QStringLiteral("/proc/mounts"));
	l_tab->processInfo();
	
	if(prvMounted==nullptr){
		prvMounted=l_tab;
		changeMonitor.open();

		return "";
	} else {
		
		
		l_what="";
		bool l_changed=false;
		
		if(l_tab->notInOther(prvMounted,mounted)) l_changed=true;
		QSetIterator<QString> l_iter(mounted);
		while(l_iter.hasNext()){
			if(l_what.length()>0) l_what +=",";
			
			l_what += l_iter.next()+i18n(" mounted");
		}

		if(prvMounted->notInOther(l_tab,unmounted)) l_changed=true;
		QSetIterator<QString> l_iterUnmounted(unmounted);
		while(l_iterUnmounted.hasNext()){
			if(l_what.length()>0) l_what +=",";
			l_what += l_iterUnmounted.next()+i18n(" unmounted");
		}
		
		//Check udev for any device new or remove block devices 
		if(changeMonitor.isSomethingChanged(l_what)) l_changed=true;
		delete prvMounted;
		prvMounted=l_tab;
		return l_what;
	}
}
