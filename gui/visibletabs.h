#ifndef __VISIBLETABS_H_
#define __VISIBLETABS_H_
#include "ui_visibletabs.h"

/**
 *  The main window contains some predefined tabs (device tab, raid ,llvm tab)
 *  
 *  With this dialog is possible to configure which tabs are visible 
 *  User defined tabs kan be displayed or hidden configured the "usertabdef" dialog
 */
class TVisibleTabs:public QDialog
{
	Q_OBJECT
private slots:
	void okPressed();
private:
	/**
	 * Gui layout. 
	 * This is generated from visibletabs.ui
	 */
	Ui::visibleTabs ui;
public:
	TVisibleTabs();
};
#endif