#ifndef __FORMTABLEDEF_H__
#define __FORMTABLEDEF_H__
#include <QDialog>
#include <QStandardItemModel>
#include <QItemSelection>
#include "ui_tabconfig.h"
#include "data/tabdef.h"
#include <QCloseEvent>

class TFormTabDef:public QDialog{
	Q_OBJECT
private slots:
	void changeConditionType(int p_index);
	void newTab();
	void selectTabDev(const QItemSelection & p_selected, const QItemSelection & p_deselected);
	void selectField(const QItemSelection & p_selected, const QItemSelection & p_deselected);
	void saveTabDef();
	void cancelDef();
	void refreshList(int p_move=0);
	void delDef();
	void upDef();
	void downDef();	
	void addField();
	void delField();
	void upField();
	void downField();
	void checkUseExtended();
	void extendedConditionChanged();
	void extendedFieldChanged(int p_index);
	void tabTypeChanged(int p_index);
private:
	Ui::tabdef ui;
	QStandardItemModel *tabDefModel;
	QStandardItemModel *fieldListModel;
	TTabDefList *tabDefs;
	TTabDef     *current;
	
	int currentRow=0;
	void toggleUseExtended(bool p_flag);
	void fillExtendedFields();
	void fillConditionField();
	void fillConditionType();
	void fillFormByTabDef(TTabDef *p_def);
	void formToCurrentTabDef();
	void fillTabDef();
	void fillFields();
	void fillSelectedFields();
	void addFieldToFieldListModel(int p_int);
	void moveField(int p_dir);
	void setExtendedConditionError(QString p_error);
	void checkExtendedCondition();
	TDoubleLinkedListItem<TTabDef> *getCurrentItem();
protected:
	virtual void closeEvent(QCloseEvent *p_event) override;
public:
	TFormTabDef(TTabDefList *p_tabDefs);
	~TFormTabDef();
};


#endif
