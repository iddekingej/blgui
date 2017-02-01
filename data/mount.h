#ifndef __MTABDEVICE_H_
#define __MTABDEVICE_H_

#include <QString>
#include "base/linklist.h"
/**
 * A device/partition has a list of mount points
 * A mount pointer is stored as a TMount object
 */
class TMount
{
private:
	QString mountPoint;
	QString type;
public:
	inline QString getMountPoint(){ return mountPoint;}
	inline QString getType(){ return type;}
	
	TMount(const QString &p_mountPoint,const QString &p_type);
};


#endif
