#ifndef __USERTABDEF_H__
#define __USERTABDEF_H__
#include <QWidget>
#include "ui_usertabdef.h"
#include "data/tabdef.h"
#include "data/deviceinfo.h"
class TUserTabDef:public QWidget
{
private:
	Ui::userTabDef ui;
	QStandardItemModel *model;
public:
	TUserTabDef(QWidget *p_parent);
	void fillGrid(TTabDef *p_def,TDeviceInfo *p_info);
};
#endif
