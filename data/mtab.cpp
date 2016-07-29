#include "mtab.h"
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QIODevice>


TMTabEntry::TMTabEntry(QString p_device,TDeviceBase *p_realDevice, QString p_mountPoint,QString p_type, QString p_options)
{
	device     = p_device;
	mountPoint = p_mountPoint;
	type       = p_type;
	options    = p_options;
	realDevice = p_realDevice;

}

TMTabEntry::TMountState TMTabEntry::isMounted()
{
	if(type==QStringLiteral("swap")){
		return MOUNTUNKNOWN;
	}
	if(realDevice){
		if(realDevice->isMountedOn(mountPoint)){
			return MOUNTED;
		} else {
			if(realDevice->isMounted()){
				return DIFMOUNTED;
			} else{
				return NOTMOUNTED;
			}
		}
	} else {
		return MOUNTUNKNOWN;
	}
}

TMTabEntry::TSameType TMTabEntry::isSameType()
{
	if(realDevice){
		if(realDevice->getType()=="??"){
			return UNKNOWNTYPE;
		} else {
			if(QString::compare(realDevice->getType(),type,Qt::CaseInsensitive)==0){
				return SAMETYPE;
			} else {
				return NOTSAMETYPE;
			}
		}
	} else {
		return UNKNOWNTYPE;
	}
}



QString TMTab::scanToSpace(const QString &p_string,int &p_cnt)
{
	int   l_length=p_string.length();
	int   l_begin=p_cnt;
	QChar l_ch;	
	QString l_string;
	while(p_cnt<l_length){
		l_ch=p_string.at(p_cnt);
		if( (' '==l_ch)||('\t'==l_ch)){
			return p_string.mid(l_begin,p_cnt-l_begin);			
		}
		p_cnt++;
	}
	return p_string.mid(l_begin);
}

bool TMTab::scanToNext(const QString &p_string,int &p_cnt)
{
	int   l_length=p_string.length();
	QChar l_ch;	
	while(p_cnt<l_length){
		l_ch=p_string.at(p_cnt);
		if( (' '!=l_ch)&&('\t'!=l_ch)){		
			return true;
		}
		p_cnt++;
	}	
	return false;
}	

bool TMTab::processLine(const QString &p_line)
{
	int  l_current=0;
	QStringList l_info;
	QString l_part;
	QString l_deviceName;
	QString l_ldeviceName;
	TDeviceBase *l_realDevice;
	while(scanToNext(p_line,l_current)){
		l_part=scanToSpace(p_line,l_current);
		l_info << l_part;
	}
	if(l_info.length()<4) return false;
	l_deviceName=l_info[0];
	l_ldeviceName=l_deviceName.toLower();
	if(l_ldeviceName.startsWith("label=")){
		l_realDevice=devList->getLabelIndex()->value(l_deviceName.mid(6));
	}else if(l_ldeviceName.startsWith("uuid=")){		
		l_realDevice=devList->getUuidIndex()->value(l_deviceName.mid(5));
	} else {
		l_realDevice=devList->findDeviceByDevPath(l_info[0]);
		
	}
	entries.append(new TMTabEntry(l_info[0],l_realDevice,l_info[1],l_info[2].toLower(),l_info[3]));
	return true;
	
}
void TMTab::processInfo()
{

	QString l_line;
	QString l_device;
	QFile l_file(QStringLiteral("/etc/fstab"));
	if(!l_file.open(QIODevice::ReadOnly|QIODevice::Text)){
			printf("Error\n");
			return;
	}
	
	QTextStream l_stream(&l_file);	
	while(true){
		l_line=l_stream.readLine();
		
		if(l_stream.atEnd()==1) break;
		if(l_line.at(0)=='#') continue;		
		processLine(l_line);
	}
	l_file.close();
}

TMTab::TMTab(TDeviceList *p_devList){
	devList=p_devList;
}
