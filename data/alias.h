#ifndef __ALIAS_H_
#define __ALIAS_H_
#include <QMap>
#include <QString>

class TAlias
{
private:
	QMap<QString,QString> aliasses;
	void processAlias(const QString &p_file);
	void procesAliasses(const QString &p_path);
public:
	inline QString getDeviceFromAlias(const QString &p_name){
		return aliasses.value(p_name);
	}
	
	QString getDeviceNameFromAliasPath(const QString &p_name);		

	
	inline bool contains(const QString &p_name){
		return aliasses.contains(p_name);
	}
	

	void readInfo();
};
#endif