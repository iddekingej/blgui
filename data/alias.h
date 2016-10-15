#ifndef __ALIAS_H_
#define __ALIAS_H_
#include <QHash>
#include <QString>

class TAlias
{
private:
	QHash<QString,QString> aliasses;
	void processAlias(const QString &p_file);
	void procesAliasses(const QString &p_path);
public:

	//Get device object by alias name
	inline const QString getDeviceFromAlias(const QString &p_name){
		return aliasses.value(p_name);
	}
	
	const QString getDeviceNameFromAliasPath(const QString &p_name);		

	//Does alias exists?
	inline bool contains(const QString &p_name){
		return aliasses.contains(p_name);
	}
	

	void readInfo();
};
#endif
