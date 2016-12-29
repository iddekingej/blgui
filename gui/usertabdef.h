#ifndef __USERTABDEF_H__
#define __USERTABDEF_H__
#include <QWidget>
#include <QVector>
#include "ui_usertabdef.h"
#include "data/tabdef.h"
#include "data/deviceinfo.h"
class TUserTabDef:public QWidget
{
private:
	Ui::userTabDef ui;
	QStandardItemModel *model;
	unsigned long no=-1;
private:
	void fillHeader(int p_begin,QVector<int> *p_fields);
	void displayRow(int p_fixedEnd,int p_begin,int p_row,QVector<int> *p_enabledFields ,const QStringList  &p_list);
public:
	inline unsigned long getNo(){ return no;}
	TUserTabDef(QWidget *p_parent);
	void fillGrid(TTabDef *p_def,TDeviceInfo *p_info);
};
#endif
