#include "mtab.h"
#include <QString>
#include <QFile>
#include <QTextStream>

TMTabEntry::TMTabEntry(const QString &p_device,TDeviceBase *p_realDevice,const QString &p_mountPoint,const QString &p_type,const QString &p_options)
{
	device=p_device;
	realDevice=p_realDevice;
	mountPoint=p_mountPoint;
	type=p_type;
	options=p_options;
}



TMTab::TMTab(TDeviceList* p_devList)
{
	devList=p_devList;
}

void TMTab::nextItem(const QString& p_text, QString& p_out, int& p_cnt)
{
	int l_length=p_text.length();
	int l_begin=p_cnt;
	QChar l_ch;	
	while(p_cnt<l_length){
		l_ch=p_text.at(p_cnt);
		if((l_ch==' ') || (l_ch=='\t')){
			p_out=p_text.mid(l_begin,p_cnt-l_begin);
			return;
		}
		p_cnt++;
	}
	p_out=p_text.mid(l_begin);
}

bool TMTab::untilNext(const QString& p_text, int& p_cnt)
{
	int l_length=p_text.length();
	QChar l_ch;	
	
	while(p_cnt<l_length){
		l_ch=p_text.at(p_cnt);
		if(l_ch!=' ' && l_ch!='\t') return true;
		p_cnt++;
	}
	
	return false;;	
}

bool TMTab::processLine(const QString& p_line)
{
	QStringList l_items;
	QString l_entry;
	QString l_device;
	QString l_lowerDevice;
	TDeviceBase *l_realDevice;
	int l_cnt=0;
	
	while(untilNext(p_line,l_cnt)){		
		nextItem(p_line,l_entry,l_cnt);
		
		l_items << l_entry;
	}
	if(l_items.length()<4) return false;
	
	l_device=l_items[0];
	l_lowerDevice=l_device.toLower();
	if(l_lowerDevice.startsWith("label=")){
		l_realDevice=devList->getLabelIndex()->value(l_lowerDevice.mid(6));
	} else if(l_lowerDevice.startsWith("uuid=")){
		l_realDevice=devList->getUuidIndex()->value(l_lowerDevice.mid(5));
	} else {
		l_realDevice=devList->findDeviceByDevPath(l_device);
	}
	entries.append(new TMTabEntry(l_device,l_realDevice,l_items[1],l_items[2].toLower(),l_items[3]));
	
	return true;
}


void TMTab::processInfo()
{
	QFile l_file("/etc/fstab");
	if(!l_file.open(QIODevice::ReadOnly|QIODevice::Text)){
		return;
	}
	QTextStream l_stream(&l_file);
	QString l_line;
	while(true){
		l_line=l_stream.readLine();
		if(l_stream.atEnd()) break;
		if(l_line.at(0)=='#')continue;
		processLine(l_line);

	}

}


TMTabEntry::TSameType TMTabEntry::isSameType()
{

	if(nullptr != realDevice){
		if(realDevice->getType()=="??"){
			return UNKNOWNSAMETYPE;
		}
		if(realDevice->getType() ==type){
			return SAMETYPE;
		} else {
			return NOTSAMETYPE;
		}
	} else {
		return UNKNOWNSAMETYPE;
	}
}


TMTabEntry::TMountStatus TMTabEntry::isMounted()
{
	if(type=="swap"){
		return UNKMOUNTED;
	}	
	if(nullptr != realDevice){
		if(realDevice->isMountedOn(mountPoint)){
			return MOUNTED;
		} else if(realDevice->isMounted()){
			return DIFMOUNTED;
		} else {
			return NOTMOUNTED;
		}
	} else {
		return UNKMOUNTED;
	}
}
