/**
 * Some file system functions
 */
#ifndef __FILESYSTEMS_H_
#define __FILESYSTEMS_H_

#include <QString>
//Get all fs types (btrfs,xfs etc)
bool  getFileSystems(QStringList &p_list);
//Mount a device
bool qmount(const QString p_device,const QString p_path,const QString p_filetype,int p_flags,QString p_extra);
//umount a device
bool qumount(const QString p_unmount,bool p_lazy);

#endif
