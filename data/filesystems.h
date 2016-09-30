#ifndef __FILESYSTEMS_H_
#define __FILESYSTEMS_H_

#include <QString>

bool  getFileSystems(QStringList &p_list);
bool qmount(const QString p_device,const QString p_path,const QString p_filetype,int p_flags,QString p_extra);
bool qumount(const QString p_unmount,bool p_lazy);

#endif
