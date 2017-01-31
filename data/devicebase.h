#ifndef __DEVICEBASE_H_
#define __DEVICEBASE_H_

#include <QString>
#include <QMap>
#include "base/linklist.h"
#include "base/utils.h"
#include "mount.h"
#include "devicealias.h"
/**
 *  TDeviceBase is the base class of TDevice (information about devices)
 *  and TPartition (information about partition)
 */

class TDeviceBase
{
private:
/**
 *  Name of device (sda,sdb etc..)
 */
	QString name;
/**
 * Path to device node (/dev/sda, /dev/sdb)
 */
	QString devPath;
/**
 *  Filesystem type (btrfs,xfs,ext2 etc..)
 */
	QString type;
	
/**
 *  Label of device
 */
	QString label;
/**
 *  Name of volume group, when device is a lvm device
 */
	QString vgName;
/**
 *  Size of device  in bytes
 */
	TDiskSize size=0;
/**
 *  Free size of device in bytes
 *  This can only be read when device or partition is mounted
 *  When free size can't be read this value =0
 */
	TDiskSize free=0;
/**
 *  If free size could be determined
 *  When tree, free contains a valid valid data
 */
	bool hasFree=false;
/**
 *  List of mounts of this device
 */
	TLinkList<TMount > mounts;
/**
 *  List of aliases of the device
 *  (That are symlinks to the device node)
 */
	TLinkList<TDeviceAlias> deviceAlias;
/**
 *  List of slaves 
 *  That's raid of lvm members
 */
	QList<TDeviceBase *>    slaves;
/**
 * minor device id
 */
	int minor;
/**
 * major device id
 */
	int major;

public:
	inline void setVGName(QString p_name){ vgName=p_name;}
	inline QString &getVGName(){ return vgName;}
	inline void setDeviceNo(int p_major,int p_minor){
		minor=p_minor;
		major=p_major;
	}
	
	inline int getMinor(){ return minor;}
	inline int getMajor(){ return major;}
	
	inline TLinkList<TDeviceAlias> *getDeviceAlias(){
		return &deviceAlias;
	}
	
	inline QString getLabel()
	{
		return label;
	}
		
	TLinkList<TMount> *getMounts()
	{
		return &mounts;
	}
		
	inline TDiskSize getSize()
	{
		return size;
	}
	
	QString getReadableSize();
	QString getReadableFreeSize();
	
	inline QString getName()
	{
		return name;
	}
	
	inline QString getType()
	{
		return type;
	}
	
	
	inline void setLabel(const QString &p_label)
	{
		label=p_label;
	}
	

	inline void setType(const QString &p_type)
	{
		type=p_type;
	}
	
	inline void setFree(TDiskSize p_free,bool p_hasFree){ 
	    free=p_free;
	    hasFree=p_hasFree;
	}
	inline TDiskSize getFree(){ return free;}
	inline bool getHasFree(){ return hasFree;}
	
	inline QString  getDevPath()
	{
		return devPath;
	}
	
	inline QList<TDeviceBase *> *getSlaves()
	{
		return &slaves;
	}
	
	inline void addSlave(TDeviceBase *p_slave)
	{
		slaves.append(p_slave);
	}
		
	inline bool isMounted()
	{
		return mounts.getStart() != nullptr;
	}
	
	virtual bool hasPartitions()=0;
	bool isMountedOn(const QString &p_path);
	QString getMountText();
	const QString getSlavesString();
	virtual void fillDataRow(QStringList &p_list)=0;
	TDeviceBase(const QString &p_name,TDiskSize p_size);
	void addMount(const QString &p_type,const QString &p_mountPoint);
	void addAlias(const QString &p_type,const QString &p_alias);
	void copyMount(TLinkList<TMount> *p_mounts);
	virtual ~TDeviceBase();
};

#endif
