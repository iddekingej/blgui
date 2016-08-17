#ifndef __VISIBLETABS_H_
#define __VISIBLETABS_H_
#include "ui_visibletabs.h"
class TVisibleTabs:public QDialog
{
	Q_OBJECT
private slots:
	void okPressed();
private:
	Ui::visibleTabs ui;
public:
	TVisibleTabs();
};
#endif