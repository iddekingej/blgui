#include <QDir>
#include <QDirIterator>
#include <QSet>
#include <QString>
#include "btrfs.h"
#include "devicelist.h"
#include "raid.h"


/**Get raid level
 * \param p_path  path to /sys/fs/btrf entry for raid device
 * \param p_raidLevel  raid level is returned (directory name in /sys/fs/bfrfs/xxx/allocation/system sarting with 'raid')
 */
void TBtrfsInfo::getRaidLevel(const QString &p_path,QString &p_raidLevel)
{		
	QDirIterator l_iter(p_path+"/allocation/system/",QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		if(l_iter.fileName().startsWith("raid")){
			p_raidLevel=l_iter.fileName();
			return ;
		}
	}
	p_raidLevel="";	
}

/** parses btrfs info (under /sys/fs/btrfs).
 *  The fs type, mount points are copied to all raid members and raid information is set
 * 
 * \param p_list   Devicelist used to convert device name to device objects
 * \param p_raid   Entries with multiple btrfs devices are added to the raid list.
 */

void TBtrfsInfo::processInfo(TDeviceList *p_list,TRaidInfo *p_raid)
{
	QDirIterator l_iter("/sys/fs/btrfs/",QDir::Dirs|QDir::NoDotAndDotDot,QDirIterator::NoIteratorFlags);
	QString l_fileName;
	while(l_iter.hasNext())
	{
		l_iter.next();
		l_fileName=l_iter.fileName();
		if(l_iter.fileInfo().isDir() && (l_fileName != "features") && (l_fileName != ".") && (l_fileName != "..")){
			QDirIterator l_deviceIter(l_iter.fileInfo().filePath()+"/devices/",QDir::Dirs|QDir::NoDotAndDotDot,QDirIterator::NoIteratorFlags);
			QList<TDeviceBase *> l_btrfsMembers;
			while(l_deviceIter.hasNext()){
				l_deviceIter.next();
				TDeviceBase *l_device=p_list->getDeviceByName(l_deviceIter.fileName());
				if(l_device!=nullptr){
					l_btrfsMembers.append(l_device);
					l_device->setType("btrfs");
				}
			}
			if(l_btrfsMembers.length()>1){
				p_list->sameMountPoint(l_btrfsMembers);
				QString l_raidLevel="";
				getRaidLevel(l_iter.fileInfo().filePath(),l_raidLevel);
				p_raid->addRaid(l_btrfsMembers[0],"btrfs",l_raidLevel,l_btrfsMembers);
			}
		}
	}
}

