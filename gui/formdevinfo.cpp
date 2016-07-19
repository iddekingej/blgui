#include "formdevinfo.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QTableView>
#include <KSharedConfig>
#include <KConfigGroup>
#include "base/globals.h"
#include "partition.h"
#include "base/linklist.h"
#include "data/mtabdevice.h"
#include "data/devicealias.h"

TFormDevInfo::TFormDevInfo(TDevice *p_device):TFormBaseDevInfo()
{
	ui.setupUi(this);
	ui.nameDevice->setText(p_device->getName());
	ui.sizeLabel->setText(QString(QString::number(p_device->getSize())));
	ui.modelLabel->setText(p_device->getModel());
	ui.removeableLabel->setText(p_device->getRemovable()?i18n("Yes"):i18n("No"));
	ui.readonlyLabel->setText(p_device->getReadonly()?i18n("Yes"):i18n("No"));
	ui.labelLabel->setText(p_device->getLabel());
	ui.typeLabel->setText(p_device->getType());
	fillParitions(p_device);
	fillMountPoints(p_device);
	connect(ui.btnClose,SIGNAL(clicked()),this,SLOT(close()));
	fillAliases(ui.deviceAliases,ui.noAliasesLabel, p_device);
}

void TFormDevInfo::fillMountPoints(TDevice *p_device)
{
	QStandardItemModel *l_model=new QStandardItemModel(1,2,this);
	TLinkListItem<TMount> *l_current=p_device->getMountStart();
	TLinkListItem<TPartition> * l_partition=p_device->getPartitionStart();
	QString l_value;
	bool l_found=false;
	int l_cnt=0;
	l_model->setHorizontalHeaderItem(0,new QStandardItem(QString(i18n("Device"))));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(QString(i18n("Mountpoint"))));
	while(l_current != nullptr){
		l_model->setItem(l_cnt,0,new QStandardItem(p_device->getName()));
		l_model->setItem(l_cnt,1,new QStandardItem(l_current->getItem()->getMountPoint()));
		l_found=true;
		l_cnt++;
		l_current=l_current->getNext();
	}
	while(l_partition != nullptr){

		l_current=l_partition->getItem()->getMountStart();
		while(l_current != nullptr){
			l_model->setItem(l_cnt,0,new QStandardItem(l_partition->getItem()->getName()));
			l_model->setItem(l_cnt,1,new QStandardItem(l_current->getItem()->getMountPoint()));
			l_found=true;
			l_cnt++;
			l_current=l_current->getNext();

		}
		l_partition=l_partition->getNext();
	}

	ui.mountPoints->setModel(l_model);
	ui.mountPoints->setVisible(l_found);
	ui.noMountPointsLabel->setVisible(!l_found);
	ui.mountPoints->resizeRowsToContents();
	ui.mountPoints->resizeColumnsToContents();	
}

void TFormDevInfo::fillParitions(TDevice* p_device)
{
	TLinkListItem<TPartition> *l_current;
	int l_cnt=0;
	QStringList l_deviceRow;
	QStandardItemModel *l_model=new QStandardItemModel(p_device->getNumPartitions(),1,this);
	l_model->setHorizontalHeaderItem(0,new QStandardItem(QString(i18n("Name"))));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(QString(i18n("Partition"))));
	ui.partInfo->setWordWrap(false);
	ui.partInfo->setModel(l_model);	
	ui.partInfo->resizeRowsToContents();
	ui.partInfo->resizeColumnsToContents();	
	l_current=p_device->getPartitionStart();
	fillHeader(2,l_model);
	while(l_current != nullptr){
			
		l_deviceRow.clear();
		l_current->getItem()->fillDataRow(l_deviceRow);
		displayRow(2,l_model,l_cnt,l_deviceRow);		
		l_cnt++;
		l_current=l_current->getNext();		
	}	
}

void TFormDevInfo::displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list)
{
	int l_fieldId;
	QStandardItem *l_item;

	for(int l_cnt=0;l_cnt<p_begin;l_cnt++){
		l_item=new QStandardItem(p_list[l_cnt]);		
		p_model->setItem(p_row,l_cnt,l_item);
	}
	for(int l_cnt=0;l_cnt<enableDeviceFields.count();l_cnt++){
		l_fieldId=enableDeviceFields[l_cnt].toInt();
		if(l_fieldId+p_begin<p_list.count()){
			p_model->setItem(p_row,l_cnt+p_begin,new QStandardItem(p_list[l_fieldId+p_begin]));
		}
	}
}

void TFormDevInfo::fillHeader(int p_begin,QStandardItemModel *p_model){
	int l_fieldId;
	for(int l_cnt=0;l_cnt<enableDeviceFields.count();l_cnt++){
		l_fieldId=enableDeviceFields[l_cnt].toInt();
		if(l_fieldId<g_numDeviceFields){
			p_model->setHorizontalHeaderItem(l_cnt+p_begin,new QStandardItem(QString(i18n(g_deviceFields[l_fieldId]))));
		}
	}
}
