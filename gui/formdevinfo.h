#ifndef __FORMDEVINFO_H_
#define __FORMDEVINFO_H_
#include <QDialog>
#include <QStandardItemModel>
#include <QDateTime>
#include "ui_devinfo.h"
#include "data/device.h"
#include "gui/formbasedevinfo.h"
#include "data/devicelist.h"

class TFormDevInfo:public TFormBaseDevInfo
{
	Q_OBJECT
private slots:
	void deviceSelected(int p_index);
	void clickPartition(const QModelIndex &p_index);
private:
	Ui::devinfo ui;
	TDeviceList *deviceList;
	void initDevSelect(TDeviceList *p_list,TDevice *p_device);
	void setInfo(TDevice *p_device);
	void fillParitions(TDevice *p_device);
	void displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list);	
	void fillHeader(int p_begin,QStandardItemModel *p_model);
	//fill mount fillmount
	//for device
	bool fillMountPointItems(QStandardItemModel *p_model,TDeviceBase *p_device);
	//for device and all mount points
	void fillMountPoints(TDevice *p_device);
	//Fill slave tabs
	void fillSlaves(TDevice *p_device); 
public:
	public:
	TFormDevInfo(TDeviceList *p_list,TDevice *p_device);
};
#endif