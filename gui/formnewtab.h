#ifndef __NEWTAB_H_
#define __NEWTAB_H_
#include <QDialog>
#include "ui_newtab.h"
class TFormNewTab:public QDialog
{
private:
	Ui::NewTab ui;
public:
	QString getTabName(){ return ui.tabName->text(); }
	TFormNewTab(QString p_name);
	void save();
};
#endif
