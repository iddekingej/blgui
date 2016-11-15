#ifndef __FORMTABLEDEF_H__
#define __FORMTABLEDEF_H__
#include <QDialog>
#include "ui_tabconfig.h"

class TFormTabDef:public QDialog{
	Q_OBJECT
private slots:
	void changeConditionType(int p_index);
private:
	Ui::tabdef ui;
	void fillConditionField();
	void fillConditionType();
public:
	TFormTabDef();
};


#endif
