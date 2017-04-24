#include "devicebase.h"
#include "mount.h"
#include <QListIterator>
#include "base/compat.h"
/** 
 * Get disk size in easy to read size 
 * 
 * \return get size in easy readable form (10k ,100M etc..)
 */

QString TDeviceBase::getReadableSize()
{
    return ::getReadableSize(getSize());
}

/**
 *Get free size in easy readable form
 * 
 * \return Free size in easy readable form (10k ,100M etc...) or empty string when
 *         empty size couldn't be determined
 */
QString TDeviceBase::getReadableFreeSize()
{
    if(getHasFree()){
	return ::getReadableSize(getFree());
    }
    return QStringLiteral("");
}


TDeviceBase::TDeviceBase(const QString &p_name, TDiskSize p_size)
{
	name=p_name;
	size=p_size;	
	devPath=QStringLiteral("/dev/")+p_name;
}

/**
 *  Add mount information to devices.
 *  The mount information is a list of mountpoints on which the device is mounted and the fs type.
 *  
 *  \param p_mountPoint  Mount point directory  on which the device is mounted
 *   \param p_type      Type of file system (btrfs,ext2 etc..)
 */

void TDeviceBase::addMount(const QString &p_mountPoint,const QString &p_type)
{
	mounts.append(new TMount(p_mountPoint,p_type));
}


/***
 *  All mount points are concated to one string separated by a newline
 */
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

/**
 *  when a btrfs raid is mounted, only the mount points of one device is stored.
 *  This method copies the mount information to the other devices.
 */
void TDeviceBase::copyMount(TLinkList<TMount> *p_mounts)
{
	TLinkListIterator<TMount> l_iter(p_mounts);
	TMount *l_mount;
	while(l_iter.hasNext()){
		l_mount=l_iter.next();
		addMount(l_mount->getMountPoint(),l_mount->getType());		
	}
}


/**
 * Checks if the device is mounted on some path
 * 
 *  \param p_path path to test.
 */
bool TDeviceBase::isMountedOn(const QString &p_path)
{	
	TLinkListIterator<TMount> l_iter(&mounts);
	while(l_iter.hasNext()){
		TMount *l_item=l_iter.next();		
		if(l_item->getMountPoint()==p_path) return true;		
	}
	return false;
}

/**
 *  The salves concated to one string , separated by a comma
 * 
 */
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




