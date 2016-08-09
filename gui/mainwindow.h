#ifndef __MAINWINDOW_H_
#define __MAINWINDOW_H_
#include <QMainWindow>
#include <QStandardItemModel>
#include <QWidget>
#include <QApplication>
#include <KSharedConfig>
#include <QTimer>
#include "data/deviceinfo.h"
#include "ui_main.h"
#include "data/udevmonitor.h"
#include "data/changemanager.h"
extern QApplication *g_app;

class TMainWindow: public QMainWindow
{
	Q_OBJECT
private slots:
	
	void showFieldChooser();
	void showAbout();
	void sourceChanged(int p_index);
	void doubleClickedDevGrid(const QModelIndex &p_index);
	void refresh();
	void timeOutCheckChange();
	void clearChangeMessage();

private:
	TDeviceInfo        *info;
	QStandardItemModel *devModel;
	QVariantList enableDeviceFields;
	Ui::MainWindow ui;
	KSharedConfig::Ptr config;
	QTimer checkChange;
	
	TChangeManager  changeManager;
	bool refreshNext=false;
	void displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list);
	void readConfiguation();
	void fillHeader(int p_begin,QStandardItemModel *p_model);
	void fillDevice();
	void fillRaid();
	void fillMtab();
protected:
	void resizeEvent(QResizeEvent *p_event);
public:

	TMainWindow(QWidget *p_parent=NULL);
	~TMainWindow();

};
#endif