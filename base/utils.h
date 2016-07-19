#ifndef __UTILS_H_
#define __UTILS_H_
#include <QString>

typedef unsigned long TDiskSize;
bool readLong(QString p_path,QString p_name,unsigned long &p_size);
bool readString(QString p_path,QString p_name,QString &p_return);
void getReadableSize(TDiskSize p_value,TDiskSize &p_size,char &p_ind);

#endif