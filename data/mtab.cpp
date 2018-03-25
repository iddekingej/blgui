#include "mtab.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "base/utils.h"

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

/**
 *  Checks if a device is  mounted on a certain mount point
 * 
 *  \param p_device      Device name (e.g. sda)
 *  \param p_mountPoint  Mount point
 *  \return              True when device p_device is mounted on mountpoint p_mount otherwise false.
 */

bool TMTab::hasMount(const QString &p_device,const QString &p_mountPoint){
	TLinkListIterator<TMTabEntry> l_iter(&entries);
	TMTabEntry *l_entry;
	while(l_iter.hasNext()){
		l_entry=l_iter.next();
		if((l_entry->getDevice()==p_device) && (l_entry->getMountPoint()==p_mountPoint)) return true;		
	}
	return false;
}

/**
 *   Checks which the combinition (device, mountpoint) are not in the other list
 * 
 *   \param p_other  The devices are checked against this list.
 *   \param p_diff   This list contains (Device,mountpoint) that are not in the p_other list.
 */
bool TMTab::notInOther(TMTab *p_other, TLinkList<TMountDiff> &p_diff)
{	
	bool l_found=false;
	TLinkListIterator<TMTabEntry> l_mtabIter(&entries);
	TMTabEntry *l_item;
	while(l_mtabIter.hasNext()){		
		l_item=l_mtabIter.next();
		if(!p_other->hasMount(l_item->getDevice(),l_item->getMountPoint())){			
			p_diff.append(new TMountDiff(l_item->getDevice(),l_item->getMountPoint()));
			l_found=true;
		}		
	}
	return l_found;
}

/**
 * An mtab/fstab information consist of fields (like device name, mount point etcc...) seperated by spaces.
 * The current position (p_cnt) is at the beginnen of a field(=begin). The method scans until a space or a tab is found (end of the field)(=end)
 * This method return the value of the field (everything between begin and end)
 * 
 * \param p_text line to process
 * \param p_out  value of field
 * \param p_cnt  current position. When the routine exists p_cnt is just after the last character of the field or 
 *               at the end of the string if the end of the line is reached.
 */
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

/**Scan until next field (scan until char is no space
 * \param  p_text  Current line to proces
 * \param  p_cnt   Position. This variable is incremented until next field (until character is not a space of tab) 
 * \return true if non space character found(=field found)
 */
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

/**
 * Proces line in mount file (/etc/mtab or /etc/fstab or...)
 *
 * \param p_line line to process.  
 */
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
	entries.append(new TMTabEntry(l_device,l_realDevice,normelizePath(l_items[1]),l_items[2].toLower(),l_items[3]));
	
	return true;
}

/**
 * Process all lines in the file
 * Files beginnen with a # are skipped.
 */
bool TMTab::processInfo()
{
	QFile l_file(sourceFile);
	if(!l_file.open(QIODevice::ReadOnly|QIODevice::Text)){
		return false;
	}
	QTextStream l_stream(&l_file);
	QString l_line;
	while(true){
		l_line=l_stream.readLine();
		if(l_line.isNull()) break;		
		if(l_line.length()>0){
			if(l_line.at(0)=='#')continue;
			processLine(l_line);
		}

	}
	return true;
}

/**
 * The filesystem type can also be determine for mounted devices, by looking at the information from /proc/mount, because 
 * he /proc/mounts file (mounted device) contains also the file system type.
 * 
 * This method copies this information to the device info.
 */
void TMTab::copyFileType()
{
	TMTabEntry *l_entry;
	TLinkListIterator<TMTabEntry> l_iter(&entries);
	while(l_iter.hasNext()){
		l_entry=l_iter.next();	
		if(l_entry->getRealDevice()!=nullptr)l_entry->getRealDevice()->setType(l_entry->getType());
	}
}
/**
 * Add mount to the \See TDeviceBase mount list
 * 
 */
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

/**
* Checks if the real device type is same as stored in this object
* This is used for checking if device in /etc/fstab is the same as the real fs type
* 
* \return Returns mount status
*/
TSameType TMTabEntry::isSameType()
{

	if(nullptr != realDevice){
		if(realDevice->getType()=="??"){
			return TSameType::UNKNOWNSAMETYPE;
		}
		if(realDevice->getType() ==type){
			return TSameType::SAMETYPE;
		} else {
			return TSameType::NOTSAMETYPE;
		}
	} else {
		return TSameType::UNKNOWNSAMETYPE;
	}
}

/**
 *  The fstab contains mount points that could be mounted. This function determines if
 *  the device are really mounted on the mount point, or not.
 * 
 * \return   \See TMountStatus::UNKMOUNTED  It is not possible to determine if the device is mounted or not
 *           \See TMountStatus::MOUNTED     The device is mounted on the given mount point
 *           \See TMountStatus::DIFMOUNTED  The device is mounted on an other mount point
 *           
 */

TMountStatus TMTabEntry::isMounted()
{
	if(type=="swap"){
		return TMountStatus::UNKMOUNTED;
	}	
	if(nullptr != realDevice){		
		if(realDevice->isMountedOn(mountPoint)){			
			return TMountStatus::MOUNTED;
		} else if(realDevice->isMounted()){			
			return TMountStatus::DIFMOUNTED;
		} else {
			return TMountStatus::NOTMOUNTED;
		}
	} else {
		return TMountStatus::UNKMOUNTED;
	}
}


