#ifndef __DEVICEALIAS_H_
#define __DEVICEALIAS_H_

#include <QString>

class TDeviceAlias
{
private:
	QString type;
	QString alias;
public:
	const QString &getType(){ return type;}
	const QString &getAlias(){ return alias;}
	TDeviceAlias(const QString &p_type,const QString &p_alias);
};

#endif