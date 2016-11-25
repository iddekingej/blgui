#include "vginfo.h"
#include "base/linklist.h"
#include <QStandardItemModel>
#include "data/lvm.h"
void TVgInfoWidget::fillLVList()
{
	
	TLinkList<TLogicalVolume> *l_lvList=info->getLogicalVolumns();
	TLogicalVolume *l_lv;
	model->clear();
	model->setRowCount(l_lvList->getLength());
	model->setHorizontalHeaderItem(0,new QStandardItem("Name"));
	model->setHorizontalHeaderItem(1,new QStandardItem("Id"));
	TLinkListIterator<TLogicalVolume> l_iter(l_lvList);
	int l_cnt=0;
	while(l_iter.hasNext()){
		l_lv=l_iter.next();
		model->setItem(l_cnt,0,new QStandardItem(l_lv->getName()));
		model->setItem(l_cnt,1,new QStandardItem(l_lv->getId()));
		l_cnt++;
	}
	ui.lvData->resizeColumnsToContents();
}


TVgInfoWidget::TVgInfoWidget(TVGInfo* p_info)
{
	ui.setupUi(this);
	info=p_info;
	ui.vgNameLabel->setText(p_info->getName());
	ui.vgIdLabel->setText(p_info->getKey());
	model=new QStandardItemModel(0,2);
	ui.lvData->setModel(model);
	fillLVList();
}
