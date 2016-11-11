#include "iscsi.h"
#include "base/compat.h"
#include <QDir>
#include <QDirIterator>

TIScsiSession::TIScsiSession(QString p_name,QString p_connection)
{
	name=p_name;
	connection=p_connection;
}
	
void TIScsiSession::addDevice(TDevice* p_device)
{
	devices.append(p_device);
}



QString TIScsiSessionList::findConnection(const QString &p_path)
{
	QDir l_dir(p_path+"/device/");
	QDirIterator l_di(l_dir);
	QString l_filePath;
	while(l_di.hasNext()){
		l_di.next();
	
		if(l_di.fileName().startsWith("connection") && l_di.fileInfo().isDir()){
			l_filePath=l_di.filePath();
			QDir l_dir2(l_filePath+"/iscsi_connection/");
			QDirIterator l_di2(l_dir2);
			while(l_di2.hasNext()){
				l_di2.next();
				if(l_di2.fileName().startsWith("connection") && l_di2.fileInfo().isDir()){
					return l_di2.filePath();
				}
			}
			return nullptr;
		}
	}
	return nullptr;
}

QString TIScsiSessionList::findTargetPath(const QString &p_path){
	
	QStringList l_list;
	l_list.append("target*");
	QDirIterator l_dirIterator(p_path,l_list);
	if(l_dirIterator.hasNext()){
		l_dirIterator.next();
		return l_dirIterator.filePath();
	}
	return nullptr;
}

void TIScsiSessionList::processInfo(TDeviceList* p_list)
{
	QString l_sessionName;
	QString l_conPath;	
	QStringList l_list;
	l_list.append("session*");
	QDirIterator l_si(QStringLiteral("/sys/class/iscsi_session"),l_list);
	QString l_address;
	QString l_port;
	QString l_target;
	TDevice *l_device;
	while(l_si.hasNext()){
		l_si.next();
		l_sessionName=l_si.fileName();
		
		l_conPath=findConnection(l_si.filePath());
		l_target=findTargetPath(l_si.filePath()+"/device/");
		if(l_conPath != nullptr && l_target !=nullptr){
			readString(l_conPath,"address",l_address);
			readString(l_conPath,"port",l_port);
			
			TIScsiSession *l_session=new TIScsiSession(l_sessionName,l_address+":"+l_port);
			sessions.append(l_session);
			QDirIterator l_dit(l_target);
			//Look in target for file containing ":"=>this are scsi bus number
			//look device in devicelist and add to scsi list
			while(l_dit.hasNext()){
				l_dit.next();
				if(l_dit.fileName().contains(":") && l_dit.fileInfo().isDir()){
					l_device=p_list->getDeviceByScsiBus(l_dit.fileName());
					if(l_device != nullptr){
						l_device->setIscsiAddress(l_address+":"+l_port);
						l_session->addDevice(l_device);
						
					}
				}
			}
				

		}
		
	}	
}


	
	
