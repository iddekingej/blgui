#ifndef __FIELDCONFIG_H_
#define __FIELDCONFIG_H_
#include <QObject>
#include <QDialog>
#include <QStandardItemModel>
#include <KSharedConfig>
#include <KConfigGroup>
#include <KConfig>
#include "ui_fields.h"
#include "base/globals.h"


class TFieldsConfig:public QDialog
{
	Q_OBJECT
private slots:
	void save();
	void addLabel();
	void removeLabel();
	void moveUp();
	void moveDown();
	void displayAsTreeClicked();
	void displayAsGridClicked();
private:
	QStandardItemModel *modelAvailable;
	QStandardItemModel *modelSelected;
	Ui::FieldsConfig ui;

	void hideByFieldId(QListView *p_view,int p_fieldId,bool p_flag);
	void moveItem(int p_dif);
	void enableRemoveButton();
	void fillAvailableList();
	void fillSelectedList();
	int getFAVisibleRow(int p_index);
	void scrollToSelected();

public:
	TFieldsConfig();
	~TFieldsConfig();
}
;

#endif
