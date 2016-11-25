#ifndef __VGINFO_H_
#define __VGINFO_H_
#include "data/lvm.h"
#include <QWidget>
#include <QStandardItemModel>
#include "ui_vginfo.h"

class TVgInfoWidget:public QWidget
{
private:
	Ui::vgInfo ui;
	QStandardItemModel *model;
	void fillLVList();
	TVGInfo *info;
public:
	TVgInfoWidget(TVGInfo *p_info);
};
#endif
