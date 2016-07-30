#ifndef __MAINWINDOW_H_
#define __MAINWINDOW_H_
#include <QMainWindow>
#include <QStandardItemModel>
#include <QWidget>
#include <QApplication>
#include <KSharedConfig>
#include "data/deviceinfo.h"
#include "ui_main.h"

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

private:
	TDeviceInfo        *info;
	QStandardItemModel *devModel;
	QVariantList enableDeviceFields;
	Ui::MainWindow ui;
	KSharedConfig::Ptr config;
	void displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list);
	void readConfiguation();
	void fillHeader(int p_begin,QStandardItemModel *p_model);
	void fillDevice(TDeviceInfo *p_info);
	void fillRaid(TDeviceInfo *p_info);
	void fillMtab(TDeviceInfo *p_info);
protected:
	void resizeEvent(QResizeEvent *p_event);
public:

	TMainWindow(QWidget *p_parent=NULL);
	~TMainWindow();

};
#endif