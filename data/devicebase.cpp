#include "devicebase.h"
#include "mount.h"
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
void TDeviceBase::addMount(const QString &p_mountPoint,const QString &p_type)
{
	mounts.append(new TMount(p_mountPoint,p_type));
}


//Get QString of all mountpoints from device
QString TDeviceBase::getMounts()
{
	
	TLinkListItem<TMount> *l_current=mounts.getStart();
	QString l_return;
	while(l_current != nullptr){
		if(l_return.length()>0) l_return +=QStringLiteral("\n");
		l_return +=l_current->getItem()->getMountPoint();
		l_current=l_current->getNext();
	}
	return l_return;
}

//Copy mounts from other device
void TDeviceBase::copyMount(TLinkListItem<TMount> *p_mountStart)
{
	TLinkListItem<TMount> *l_current=p_mountStart;
	while(l_current){
		addMount(l_current->getItem()->getMountPoint(),l_current->getItem()->getType());
		l_current=l_current->getNext();
	}
}

//true device is mounted
bool TDeviceBase::isMounted()
{
		return mounts.getStart() != nullptr;
}
//True is device is mounted on path
//p_path=>path to test
bool TDeviceBase::isMountedOn(const QString &p_path)
{
	TLinkListItem<TMount> *l_current=mounts.getStart();
	QString l_return;
	while(l_current){
		if(l_current->getItem()->getMountPoint()==p_path) return true;
		l_current=l_current->getNext();
	}
	return false;
}
//Get slaves of device as a string
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



//Add alias of device
void TDeviceBase::addAlias(const QString& p_type, const QString &p_alias)
{
	deviceAlias.append(new TDeviceAlias(p_type,p_alias));
}

TDeviceBase::~TDeviceBase(){}




