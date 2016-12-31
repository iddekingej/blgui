#ifndef __MOUNTDIFF_H_
#define __MOUNTDIFF_H_
#include <QString>
class TMountDiff
{
private:
	QString device;
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
