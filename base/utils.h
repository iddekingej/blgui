/* 
 * Utility functions
*/

#ifndef __UTILS_H_
#define __UTILS_H_
#include <QString>
#include <QAbstractItemView>
#include <QStandardItemModel>
#include <QAbstractItemModel>
#include <QItemSelectionModel>

#define PAR_UNUSED __attribute__((unused))

/** 
 *  function to easy convert QString to const QString
 *  \param p_string QString to convert
 */
#define qstr(p_string) ((p_string).toUtf8().data())


typedef unsigned long TDiskSize;

// Reading a single line from a file containing a unsigned long
bool readLong ( const QString p_path, const QString p_name, long unsigned int& p_value )
;


//Reading a single line from a file
bool readString ( const QString p_path, const QString p_name, QString& p_value );

//convert size to readable format 1024=>1K
void getReadableSize(TDiskSize p_value,TDiskSize &p_size,char &p_ind);

//convert size to readable format 1024=>1K
QString getReadableSize(TDiskSize p_value);

//Set view model, delete old one and delete selection model
void setViewModel(QAbstractItemView *p_view,QStandardItemModel *p_model);



//Compare is paths are same, ignoring end slashes
QString normelizePath(QString p_path);

#define UNUSEDPAR __attribute__((unused))
#define QEMPTY_STRING QString()


#endif
