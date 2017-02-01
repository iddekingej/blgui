#ifndef  __ISCSI_H_
#define __ISCSI_H_
#include <QString>
#include "data/device.h"
#include "data/devicelist.h"
#include "base/linklist.h"

/**
 * Information about a iscsi Session
 */
class TIScsiSession
{
private:
	/**
	 * Session name
	 */
	QString name;
	/**
	 * network host:port of iscsi device
	 */
	QString connection;
	/**
	 * Target name
	 */
	QString targetName;
	/**
	 * List of iscsi  devices using this session
	 */
	QList<TDevice *> devices;
public:
	/**
	 * Get session  see @see TIScsiSession:name
	 */
	inline QString getSession(){ return name;}
	/**
	 * Get connection see @see TIScsiSession::connection
	 */
	inline QString getConnection(){return connection;}
	
	/**
	 * Get target see @see TScsiSession::target
	 */
	inline QString getTargetName(){ return targetName;}
	
	TIScsiSession(QString p_name,QString p_connection,QString p_targetName);
	void addDevice(TDevice *p_device);
	const QList<TDevice *> &getDevices(){ return devices;}
};

/**
 *  List containing all the active iscsi containers.
 *  This object reads information about iscsi data and creates the 
 *  ISCSI objects
 */
class TIScsiSessionList
{
private:
	/**
	 * List of sessions 
	 */
	TLinkList<TIScsiSession> sessions;
	
	QString findConnection(const QString &p_path);
	QString findTargetPath(const QString &p_path);

public:
	inline TLinkList<TIScsiSession> *getSessions()
	{
		return &sessions;
	}
	
	
	void processInfo(TDeviceList *p_list);
	
}; 
#endif
