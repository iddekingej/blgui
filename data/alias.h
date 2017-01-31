#ifndef __ALIAS_H_
#define __ALIAS_H_
#include <QHash>
#include <QString>

/**
 *  A device can have a alias. That is a symlink to the original device.
 *  This class collect all symlinks and determine the original device.
 */

class TAlias
{
private:
	
	/**
	 * List of found aliases.
	 * The symlink is the index and the value is the original device
	 */
	
	QHash<QString,QString> aliasses;
	void processAlias(const QString &p_file);
	void procesAliasses(const QString &p_path);
public:

	//Get device object by alias name
	inline const QString getDeviceFromAlias(const QString &p_name){
		return aliasses.value(p_name);
	}
	
	//Device name
	const QString getDeviceNameFromAliasPath(const QString &p_name);		

	//Does alias exists?
	inline bool contains(const QString &p_name){
		return aliasses.contains(p_name);
	}
	

	void readInfo();
};
#endif
