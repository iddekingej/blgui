#ifndef __FORMPARINFO_H_
#define __FORMPARINFO_H_
#include "gui/formbasedevinfo.h"
#include "data/partition.h"
#include "ui_parinfo.h"
class TFormParInfo:public TFormBaseDevInfo
{
private:
	Ui::parinfo ui;
	void fillMount(TPartition *p_partition);
public:
	TFormParInfo(TPartition *p_partition);
	
};
#endif