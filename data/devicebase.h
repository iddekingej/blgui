#ifndef __DEVICEBASE_H_
#define __DEVICEBASE_H_

#include <QString>
#include <QMap>
#include "base/linklist.h"
#include "base/utils.h"
#include "mtabdevice.h"
#include "devicealias.h"
class TDeviceBase
{
private:
	QString name;
	QString devPath;
	QString type;
	QString label;
	TDiskSize size;
	TLinkList<TMount > mounts;
	TLinkList<TDeviceAlias> deviceAlias;

public:
	inline TLinkListItem<TDeviceAlias> *getDeviceAliasStart(){
		return deviceAlias.getStart();
	}
	
	inline QString getLabel()
	{
		return label;
	}
		
	TLinkListItem<TMount> *getMountStart()
	{
		return mounts.getStart();
	}
		
	inline TDiskSize getSize()
	{
		return size;
	}
	
	QString getReadableSize();
	
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
	
	virtual const QString getModel()=0;
	
	inline QString  getDevPath()
	{
		return devPath;
	}
	
	virtual bool hasPartitions()=0;
	
	QString getMounts();
	virtual void fillDataRow(QStringList &p_list)=0;
	TDeviceBase(const QString &p_name,TDiskSize p_size);
	virtual ~TDeviceBase();
	void addMount(const QString &p_type,const QString &p_mountPoint);
	void addAlias(const QString &p_type,const QString p_alias);
};

#endif