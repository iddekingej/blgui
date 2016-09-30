#include "filesystems.h"
#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include "base/utils.h"
#include <sys/mount.h>


bool  getFileSystems(QStringList &p_list)
{
	p_list.clear();
	QFile l_file("/proc/filesystems");
	if(!l_file.open(QIODevice::ReadOnly|QIODevice::Text)){
		return false;
	}
	QTextStream l_stream(&l_file);
	QString l_line;
	while(true){
		l_line=l_stream.readLine();
		if(l_line.isNull()) break;
		if(!l_line.startsWith("nodev")){
			p_list << l_line.trimmed();
		}
	}
	l_file.close();
	return true;
}

bool qmount(const QString p_device,const QString p_path,const QString p_filetype,int p_flags,QString p_extra)
{
	const char *l_extra=nullptr;
	if(p_extra.length()>0) l_extra=qstr(p_extra);
	int l_ret=mount(qstr(p_device),qstr(p_path),qstr(p_filetype),p_flags,l_extra);
	return l_ret>=0;
}
bool qumount(const QString p_unmount,bool p_lazy)
{
	int l_ret=umount2(qstr(p_unmount),p_lazy?MNT_DETACH:0);
	return l_ret >=0;
}
