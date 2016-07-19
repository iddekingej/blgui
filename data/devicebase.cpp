#include "devicebase.h"
#include "mtabdevice.h"
#include <QListIterator>
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

//Add device mount
//parameters:
//p_type       : fs type
//p_mountPoint : Mount point path
void TDeviceBase::addMount(const QString &p_type, const QString &p_mountPoint)
{
	mounts.append(new TMount(p_type,p_mountPoint));
}


//Get QString of all mountpoints from device
QString TDeviceBase::getMounts()
{
	
	TLinkListItem<TMount> *l_current=mounts.getStart();
	QString l_return;
	while(l_current){
		if(l_return.length()>0) l_return +=QStringLiteral("\n");
		l_return +=l_current->getItem()->getMountPoint();
		l_current=l_current->getNext();
	}
	return l_return;
}

const QString TDeviceBase::getSlavesString()
{
	QListIterator<TDeviceBase *> l_iter(slaves);
	QString l_return;
	TDeviceBase *l_device;
	while(l_iter.hasNext()){
		l_device=l_iter.next();
		if(l_return.length()>0) l_return += QStringLiteral(",");
		l_return += l_device->getName();
	}
	return l_return;	
}


void TDeviceBase::addAlias(const QString& p_type, const QString p_alias)
{
	deviceAlias.append(new TDeviceAlias(p_type,p_alias));
}

TDeviceBase::~TDeviceBase(){}




