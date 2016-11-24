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
private:
	TDeviceInfo        *info;
	QStandardItemModel *devModel;
	QVector<int> *enableDeviceFields;
	Ui::MainWindow ui;
	QTimer checkChange;
	
	TChangeManager  changeManager;
	QWidget *tabs[5];
	QWidget *tabsVisible[5];
	TDiskStatList *prvStats=nullptr;
	TTabDefList userTabs;
	QList<TUserTabDef *> userTabWidgets;
	bool refreshNext=false;
	void setTabVisible(int p_indx,bool p_flag,const QString &p_label);
	void displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list,QStandardItem *p_parent);
	void readConfiguation();
	void getExpandedDevRows(QSet<QString> &p_list);
	void setExpandedDevRows(QSet<QString> &p_list);
	void fillHeader(int p_begin,QStandardItemModel *p_model);
	void fillDeviceTree();
	void fillDeviceGrid();
	void fillDevice();
	void fillRaid();
	void fillMtab();
	void fillIscsi();
	void fillStats();
	void fillUserTabDef();
	void fillLvm();
	void expandDeviceAll();
	virtual void setVisibleTabs();
	
protected:
	void resizeEvent(QResizeEvent *p_event);
public:

	TMainWindow(QWidget *p_parent=NULL);
	virtual ~TMainWindow();

};
#endif
