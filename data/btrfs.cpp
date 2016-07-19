#include <QDir>
#include <QDirIterator>
#include <QSet>
#include <QString>
#include "btrfs.h"


void TBtrfsMountItem::appendDevice(const QString &p_device)
{
	devices.append(p_device);
}


TBtrfsMountItem::TBtrfsMountItem(const QString &p_fs,const QString &p_raidLevel)
{
	fs=p_fs;
	raidLevel=p_raidLevel;
}

int TBtrfsInfo::readDevices(QString p_path,TBtrfsMountItem *p_info)
{
	QDir l_dir(p_path+"/devices/");
	QDirIterator l_iter(l_dir,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		if(l_iter.fileInfo().isSymLink()){
			p_info->appendDevice(l_iter.fileName());
			btrfsDevices << l_iter.fileName();

		}
	}
	return 0;
}

QString TBtrfsInfo::getRaidLevel(const QString &p_path)
{
	QDir l_dir(p_path+"/allocation/system/");
	QDirIterator l_iter(l_dir,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){
		l_iter.next();
		if(l_iter.fileName().startsWith("raid")){
			return l_iter.fileName();
		}
	}
	return QString();
}
int TBtrfsInfo::readInfo(TAlias *p_alias)
{	
	QDir l_dir("/sys/fs/btrfs");
	QDirIterator l_iter(l_dir,QDirIterator::NoIteratorFlags);
	QString l_fileName;
	TBtrfsMountItem *l_info;
	while(l_iter.hasNext()){
		l_iter.next();
		l_fileName=l_iter.fileName();
		if(l_iter.fileInfo().isDir() && (l_fileName != "features") && (l_fileName != ".") && (l_fileName != "..")){
			
			l_info=new TBtrfsMountItem( p_alias->getDeviceNameFromAliasPath("/dev/disk/by-uuid/"+l_fileName),getRaidLevel(l_iter.filePath()));
			readDevices(l_iter.filePath(), l_info);
			mountItems.append(l_info);
		}
		
	}
	return 0;
}

int TBtrfsInfo::getNumberMultiDevices()
{
		TLinkListItem<TBtrfsMountItem> *l_top=mountItems.getStart();
		int l_return=0;
		while(l_top){
			if(l_top->getItem()->isMultiDev()) l_return++;
			l_top=l_top->getNext();
		}
		return l_return;		
}

bool TBtrfsInfo::isBtrfs(const QString &p_name)
{
	return btrfsDevices.contains(p_name);
}

