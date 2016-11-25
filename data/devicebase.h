#ifndef __DEVICEBASE_H_
#define __DEVICEBASE_H_

#include <QString>
#include <QMap>
#include "base/linklist.h"
#include "base/utils.h"
#include "mount.h"
#include "devicealias.h"
class TDeviceBase
{
private:
	QString name;
	QString devPath;
	QString type;
	QString label;
	QString vgName;
	TDiskSize size=0;
	TDiskSize free=0;
	bool hasFree=false;
	TLinkList<TMount > mounts;
	TLinkList<TDeviceAlias> deviceAlias;
	QList<TDeviceBase *>    slaves;
	int minor;
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
	virtual ~TDeviceBase();
	void addMount(const QString &p_type,const QString &p_mountPoint);
	void addAlias(const QString &p_type,const QString &p_alias);
	void copyMount(TLinkList<TMount> *p_mounts);
};

#endif
