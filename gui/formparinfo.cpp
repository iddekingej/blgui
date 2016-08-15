#include "formparinfo.h"
#include "ui_parinfo.h"
#include "base/linklist.h"
#include "gui/formdevinfo.h"
#include <QString>
#include <QStandardItemModel>

void TFormParInfo::gotoDevice()
{
	TFormDevInfo l_info(deviceList, (TDevice*)partition->getDevice());
	l_info.exec();
	close();
}


TFormParInfo::TFormParInfo(TDeviceList *p_list,TPartition *p_partition){
	ui.setupUi(this);
	ui.gotoDevice->setText(p_partition->getDevice()->getName());
	ui.parName->setText(p_partition->getName());
	ui.labelLabel->setText(p_partition->getLabel());
	ui.sizeLabel->setText(QString::number(p_partition->getSize()));
	ui.typeLabel->setText(p_partition->getType());
	connect(ui.btnClose,SIGNAL(clicked()),this,SLOT(close()));
	connect(ui.gotoDevice,SIGNAL(clicked()),this,SLOT(gotoDevice()));
	fillAliases(ui.deviceAliases,ui.noAliasesLabel, p_partition);
	fillMount(p_partition);
	partition=p_partition;
	deviceList=p_list;
}

void TFormParInfo::fillMount(TPartition *p_partition)
{
	QStandardItemModel *l_model=new QStandardItemModel(1,1,this);
	TLinkListItem<TMount> *l_current=p_partition->getMountStart();
	if(l_current==nullptr){
		ui.mountPoints->setVisible(false);
	} else {
		l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Mountpoint")));
		int l_cnt=0;
		while(l_current){
			l_model->setItem(l_cnt,0,new QStandardItem(l_current->getItem()->getMountPoint()));
			l_cnt++;
			l_current=l_current->getNext();
		}
		ui.mountPoints->setModel(l_model);
		ui.mountPoints->resizeRowsToContents();
		ui.mountPoints->resizeColumnsToContents();	
		ui.noMountPointsLabel->setVisible(false);
	}

}