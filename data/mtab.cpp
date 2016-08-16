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
	sourceFile="/etc/fstab";
}

bool TMTab::hasMount(const QString &p_device,const QString &p_mountPoint){
	TLinkListIterator<TMTabEntry> l_iter(&entries);
	TMTabEntry *l_entry;
	while(l_iter.hasNext()){
		l_entry=l_iter.next();
		if((l_entry->getDevice()==p_device) && (l_entry->getMountPoint()==p_mountPoint)) return true;		
	}
	return false;
}


bool TMTab::notInOther(TMTab *p_other, QSet<QString>& p_return)
{	
	bool l_found=false;
	TLinkListIterator<TMTabEntry> l_mtabIter(&entries);
	TMTabEntry *l_item;
	while(l_mtabIter.hasNext()){		
		l_item=l_mtabIter.next();
		if(!p_other->hasMount(l_item->getDevice(),l_item->getMountPoint())){
			p_return += l_item->getDevice();
			l_found=true;
		}		
	}
	return l_found;
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

//Scan until next field in fstab or mtab file line (scan until char is no space
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

// Proces line in mount file (/etc/mtab or /etc/fstan)
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

//Read moint file
void TMTab::processInfo()
{
	QFile l_file(sourceFile);
	if(!l_file.open(QIODevice::ReadOnly|QIODevice::Text)){
		return;
	}
	QTextStream l_stream(&l_file);
	QString l_line;
	while(true){
		if(!l_stream.readLineInto(&l_line)) break;	
		if(l_line.length()>0){
			if(l_line.at(0)=='#')continue;
			processLine(l_line);
		}

	}

}

//Add mount to the TDeviceBase mount list
void TMTab::addMountTODevices()
{	
	TMTabEntry *l_entry;
	TLinkListIterator<TMTabEntry> l_iter(&entries);
	while(l_iter.hasNext()){
		l_entry=l_iter.next();		
		if(l_entry->getRealDevice() != nullptr){
			l_entry->getRealDevice()->addMount(l_entry->getMountPoint(),l_entry->getType());
		}		
	}
}

// Checks if the real device type is same as stored in this object
// THis is used for checking if device in /etc/fstab is the same as se the real fs type
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


