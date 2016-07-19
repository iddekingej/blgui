#ifndef __MAINWINDOW_H_
#define __MAINWINDOW_H_
#include <QMainWindow>
#include <QStandardItemModel>
#include <QWidget>
#include <QApplication>
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
private:
	TDeviceInfo        *info;
	QStandardItemModel *devModel;
	QVariantList enableDeviceFields;
	void displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list);
	void readConfiguation();
	void fillHeader(int p_begin,QStandardItemModel *p_model);
	void fillDevice(TDeviceInfo *p_info);
	void fillRaid(TDeviceInfo *p_info);
	
public:

	TMainWindow(QWidget *p_parent=NULL);
public slots:
	void refresh();

private:
	Ui::MainWindow ui;
};
#endif