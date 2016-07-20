#ifndef __FORMDEVINFO_H_
#define __FORMDEVINFO_H_
#include <QDialog>
#include <QStandardItemModel>
#include "ui_devinfo.h"
#include "data/device.h"
#include "gui/formbasedevinfo.h"

class TFormDevInfo:public TFormBaseDevInfo
{
	Q_OBJECT
private:
	Ui::devinfo ui;
	void fillParitions(TDevice *p_device);
	void displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list);	
	void fillHeader(int p_begin,QStandardItemModel *p_model);
	void fillMountPoints(TDevice *p_device);
	//Fill slave tabs
	void fillSlaves(TDevice *p_device); 
public:
	public:
	TFormDevInfo(TDevice *p_device);
};
#endif