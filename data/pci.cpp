#include "pci.h"
#include <QDirIterator>
#include "base/utils.h"

bool TPCIInfo::getPciBus(QString& p_scsibus, QString& p_pciBus)
{
	if(scsiToPciIndex.contains(p_scsibus)){
		p_pciBus=scsiToPciIndex[p_scsibus];
		return true;
	}
	p_pciBus="";
	return false;
}
void TPCIInfo::readInfo()
{
	QDirIterator l_iter("/sys/bus/pci/drivers/ahci/",QStringList() << "[0-9]*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){		
		l_iter.next();
		processBus(l_iter.filePath(),l_iter.fileName());
	}
}

void TPCIInfo::processBus(QString p_path, QString p_pciBus)
{
	QDirIterator l_iter(p_path,QStringList() << "ata*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){		
		l_iter.next();
		processAta(l_iter.filePath(),p_pciBus);		
	}
}

void TPCIInfo::processAta(QString p_path, QString p_pciBus)
{
	QDirIterator l_iter(p_path,QStringList() << "host*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){		
		l_iter.next();		
		processHost(l_iter.filePath(),p_pciBus);
	}
}

void TPCIInfo::processHost(QString p_path, QString p_pciBus)
{
	QDirIterator l_iter(p_path,QStringList() << "target*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){		
		l_iter.next();
		processTarget(l_iter.filePath(),p_pciBus);		
	}
}


void TPCIInfo::processTarget(QString p_path, QString p_pciBus)
{
	QDirIterator l_iter(p_path,QStringList() << "[0-9]*",QDir::Dirs,QDirIterator::NoIteratorFlags);
	while(l_iter.hasNext()){		
		l_iter.next();
		scsiToPciIndex.insert(l_iter.fileName(),p_pciBus);
	}
}
