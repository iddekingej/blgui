#ifndef  __ISCSI_H_
#define __ISCSI_H_
#include <QString>
#include "data/device.h"
#include "data/devicelist.h"
#include "base/linklist.h"

class TIScsiSession
{
private:
	QString        name;
	QString        connection;
	QList<TDevice *> devices;
public:
	inline QString getSession(){ return name;}
	inline QString getConnection(){return connection;}
	
	TIScsiSession(QString p_name,QString p_connection);
	void addDevice(TDevice *p_device);
	const QList<TDevice *> &getDevices(){ return devices;}
};


class TIScsiSessionList
{
private:
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