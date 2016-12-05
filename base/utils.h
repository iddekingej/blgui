#ifndef __UTILS_H_
#define __UTILS_H_
#include <QString>

#define PAR_UNUSED __attribute__((unused))

/** \brief function to easy convert QString to const QString
 *  \param p_string QString to convert
 */
#define qstr(p_string) ((p_string).toUtf8().data())


typedef unsigned long TDiskSize;

//Used for reading files in /sys/block
//Read file containing ulong (like /sys/block/sda/size)
bool readLong(QString p_path,QString p_name,unsigned long &p_size);

//Used for reading files in /sys/block
//Read file containing a string (like sys/block/sda/model)
bool readString(QString p_path,QString p_name,QString &p_return);

//convert size to readable format 1024=>1K
void getReadableSize(TDiskSize p_value,TDiskSize &p_size,char &p_ind);
QString getReadableSize(TDiskSize p_value);

//Compare is paths are same, ignoring end slashes
QString normelizePath(QString p_path);

#define UNUSEDPAR __attribute__((unused))

#endif
