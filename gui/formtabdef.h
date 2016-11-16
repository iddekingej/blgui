#ifndef __FORMTABLEDEF_H__
#define __FORMTABLEDEF_H__
#include <QDialog>
#include <QStandardItemModel>
#include "ui_tabconfig.h"
#include "data/tabdef.h"
class TFormTabDef:public QDialog{
	Q_OBJECT
private slots:
	void changeConditionType(int p_index);
	void newTab();
	void selectTabDev(QModelIndex p_index);
	void saveTabDef();
private:
	Ui::tabdef ui;
	QStandardItemModel *tabDefModel;
	TTabDefList *tabDefs;
	TTabDef *current;
	void fillConditionField();
	void fillConditionType();
	void fillFormByTabDef(TTabDef *p_def);
	void formToCurrentTabDef();
	void fillTabDef();
public:
	TFormTabDef(TTabDefList *p_tabDefs);
	~TFormTabDef();
};


#endif
