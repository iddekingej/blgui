#ifndef __MOUNTDIFF_H_
#define __MOUNTDIFF_H_
#include <QString>
/**
 * The /proc/mount is read periodical for for monitoring mount/unmount actions.
 * The data is compared to the previous data and the difference is calculated.
 * The difference is stored in this object.
 * 
 * This object contain device/path pairs that is in one data set but not in the other 
 * 
 * @see TMTab::notInOther(TMTab *, TLinkList &)
 */
class TMountDiff
{
private:
/**
 * The diffence is about this device
 */
	QString device;
	
/**
 *  That is mounted on this path
 */
	QString path;
public:
	inline QString &getDevice(){return device;}
	inline QString &getPath(){return path;}
	TMountDiff(const QString &p_device,const QString &p_path){ 
		path=p_path;
		device=p_device;
	}
};

#endif
