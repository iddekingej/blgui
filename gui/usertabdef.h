#ifndef __USERTABDEF_H__
#define __USERTABDEF_H__
#include <QWidget>
#include <QVector>
#include "ui_usertabdef.h"
#include "data/tabdef.h"
#include "data/deviceinfo.h"

/**
 * This widget is used for display the user defined tabs.
 * It is added to the main window.
 */

class TUserTabDef:public QWidget
{
private:
	/**
	 * Layout of de widget
	 * Generated from usertabdef.ui
	 */
	Ui::userTabDef ui;
	/**
	 * The model used by de QGridView
	 */
	QStandardItemModel *model;
	
	/**
	 * A TTabdef object contains the definition of the data displayed 
	 * in this widget. The object is not stored in this object because 
	 * during the life time of this widgett,  the TTabdef object can be 
	 * deleted and reread from the configuration fil when the user
	 * opens the user tab def dialog box and click cancel button.
	 * Only the unique ID is stored.
	 */
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
