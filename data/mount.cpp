
#include "devicebase.h"
#include "base/linklist.h"
#include "mount.h"
#include "base/compat.h"
TMount::TMount(const QString &p_mountPoint,const QString &p_type)
{
	type=p_type;
	mountPoint=p_mountPoint;
};


