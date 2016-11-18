#ifndef __FORMTABLEDEF_H__
#define __FORMTABLEDEF_H__
#include <QDialog>
#include <QStandardItemModel>
#include <QItemSelection>
#include "ui_tabconfig.h"
#include "data/tabdef.h"
class TFormTabDef:public QDialog{
	Q_OBJECT
private slots:
	void changeConditionType(int p_index);
	void newTab();
	void selectTabDev(const QItemSelection & p_selected, const QItemSelection & p_deselected);
	void saveTabDef();
	void cancelDef();
	void refreshList(int p_move=0);
	void delDef();
	void upDef();
	void downDef();	
	void addField();
	
private:
	Ui::tabdef ui;
	QStandardItemModel *tabDefModel;
	QStandardItemModel *fieldListModel;
	TTabDefList *tabDefs;
	TTabDef     *current;
	
	int currentRow;
	void fillConditionField();
	void fillConditionType();
	void fillFormByTabDef(TTabDef *p_def);
	void formToCurrentTabDef();
	void fillTabDef();
	void fillFields();
	void fillSelectedFields();
	void addFieldToFieldListModel(int p_int);
	TDoubleLinkedListItem<TTabDef> *getCurrentItem();
public:
	TFormTabDef(TTabDefList *p_tabDefs);
	~TFormTabDef();
};


#endif
