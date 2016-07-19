#include "devicebase.h"
#include "mtabdevice.h"
QString TDeviceBase::getReadableSize()
{
	TDiskSize l_size;
	char l_ind;
	::getReadableSize(getSize(),l_size,l_ind);
	return QString::number(l_size)+l_ind;
}

TDeviceBase::TDeviceBase(const QString &p_name, TDiskSize p_size)
{
	name=p_name;
	size=p_size;	
	devPath="/dev/"+p_name;
}


void TDeviceBase::addMount(const QString &p_type, const QString &p_mountPoint)
{
	mounts.append(new TMount(p_type,p_mountPoint));
}

QString TDeviceBase::getMounts()
{
	
	TLinkListItem<TMount> *l_current=mounts.getStart();
	QString l_return;
	while(l_current){
		if(l_return.length()>0) l_return +="\n";
		l_return +=l_current->getItem()->getMountPoint();
		l_current=l_current->getNext();
	}
	return l_return;
}

TDeviceBase::~TDeviceBase()
{
}


void TDeviceBase::addAlias(const QString& p_type, const QString p_alias)
{
	deviceAlias.append(new TDeviceAlias(p_type,p_alias));
}



