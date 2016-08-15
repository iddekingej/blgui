#ifndef __FORMPARINFO_H_
#define __FORMPARINFO_H_
#include "gui/formbasedevinfo.h"
#include "data/devicelist.h"
#include "data/partition.h"
#include "ui_parinfo.h"
class TFormParInfo:public TFormBaseDevInfo
{
	Q_OBJECT
private slots:
	void gotoDevice();
private:
	TDeviceList *deviceList;
	TPartition  *partition;
	Ui::parinfo ui;
	void fillMount(TPartition *p_partition);
public:
	TFormParInfo(TDeviceList *p_list, TPartition *p_partition);
	
};
#endif