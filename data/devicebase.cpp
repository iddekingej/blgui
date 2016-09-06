#include "devicebase.h"
#include "mount.h"
#include <QListIterator>
#include "base/compat.h"
//Get disk size in easy to read size like 10k 10M 100G
QString TDeviceBase::getReadableSize()
{
    return ::getReadableSize(getSize());
}

//Get freedisk size in easy to read size like 10k 10M 100G
QString TDeviceBase::getReadableFreeSize()
{
    if(getHasFree()){
	return ::getReadableSize(getFree());
    }
    return "";
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
QString TDeviceBase::getMountText()
{
	TLinkListIterator<TMount> l_iter(&mounts);	
	TMount *l_mount;
	QString l_return;
	while(l_iter.hasNext()){
		l_mount=l_iter.next();
		if(l_return.length()>0) l_return +=QStringLiteral("\n");
		l_return +=l_mount->getMountPoint();		
	}
	return l_return;
}

//Copy mounts from other device
void TDeviceBase::copyMount(TLinkList<TMount> *p_mounts)
{
	TLinkListIterator<TMount> l_iter(p_mounts);
	TMount *l_mount;
	while(l_iter.hasNext()){
		l_mount=l_iter.next();
		addMount(l_mount->getMountPoint(),l_mount->getType());		
	}
}


//True is device is mounted on path
//p_path=>path to test
bool TDeviceBase::isMountedOn(const QString &p_path)
{	
	TLinkListIterator<TMount> l_iter(&mounts);
	while(l_iter.hasNext()){
		TMount *l_item=l_iter.next();		
		if(l_item->getMountPoint()==p_path) return true;		
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




