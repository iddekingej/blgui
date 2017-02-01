#ifndef __MAINWINDOW_H_
#define __MAINWINDOW_H_
#include <QMainWindow>
#include <QStandardItemModel>
#include <QWidget>
#include <QApplication>
#include <QTimer>
#include "data/deviceinfo.h"
#include "ui_main.h"
#include "data/udevmonitor.h"
#include "data/changemanager.h"
#include "base/config.h"
#include "data/diskstat.h"
#include "data/tabdef.h"
#include "gui/usertabdef.h"
extern QApplication *g_app;

class TMainWindow: public QMainWindow
{
	Q_OBJECT
private slots:
	
	void showFieldChooser();
	void showAbout();
	void showUserDefinedTabs();
	void sourceChanged(int p_index);
	void doubleClickedDevGrid(const QModelIndex &p_index);
	void refresh();
	void timeOutCheckChange();
	void clearChangeMessage();
	void visibleTabs();
	void handleMount();
	void setupUserTabs();
	void checkSetNotifications();
private:
	
/**
 *  Information about all block devices ont he system.
 */
	TDeviceInfo        *info;
/**
 *  Data model for the stats grid
 */
	QStandardItemModel *statsModel;
/**
 *  Data model for the device grid
 */
	QStandardItemModel *devModel;
/**
 *  Data model for the notification model
 */
	QStandardItemModel *notificationsModel;
/**
 * List of fields displayed inside the device grid
 * The Vector contains field id's
 */
	QVector<int> *enableDeviceFields;
/**
 * Layout of the main window.
 * This is generated from main.ui
 */
	Ui::MainWindow ui;
/**
 * Timer for periodicly checking changes of device states (mount,added removed, unmounted)
 */
	QTimer checkChange;
/**
 * Monitors device changes (mount,added, removed, unmounted)
 */
	TChangeManager  changeManager;
/**
 * List of pre defined tabs.
 * This is used for hiding and displaying thos tabs
 */
	QWidget *tabs[6];
/**
 * Array of visible pre defined tabs 
 */
	QWidget *tabsVisible[6];
/**
 * Previous io stats , this is used to calculate the difference
 */
	TDiskStatList *prvStats=nullptr;
/**
 * List of user defined tabs
 */
	TTabDefList userTabs;
/**
 * List of widget used for displaying
 * the user defined tabs
 */
	QList<TUserTabDef *> userTabWidgets;
/**
 * List of devices that are manual expanded.
 * This is used to restore expand state after a refresh
 */
	QSet< QString > expandedDevices;
	
/**
 *  Display the device list as a tree or as a linear list.
 *  This value is read from the configuration file
 */
	bool deviceAsTree=false;
	bool refreshNext=false;
	void setTabVisible(int p_indx,bool p_flag,const QString &p_label);
	void displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list,QStandardItem *p_parent);
	void readConfiguation();
	void getExpandedDevRows(QSet<QString> &p_list);
	void setExpandedDevRows(QSet<QString> &p_list);
	void fillHeader(int p_begin,QStandardItemModel *p_model);
	void fillDeviceTree();
	void fillDeviceGrid();
	void fillDevice(bool p_sourceChanged);
	void fillRaid();
	void fillMtab();
	void fillIscsi();
	void fillStats();
	void fillUserTabDef();
	void fillLvm();
	void fillMessages();
	void expandDeviceAll();
	virtual void setVisibleTabs();
	
protected:
	void resizeEvent(QResizeEvent *p_event);
public:

	TMainWindow(QWidget *p_parent=nullptr);
	virtual ~TMainWindow();

};
#endif
