#include "formdevinfo.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QTableView>
#include <KSharedConfig>
#include <KConfigGroup>
#include "base/globals.h"
#include "data/partition.h"
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
	if(p_device->getLoopbackFile().length()>0){
		ui.valLoopbackFile->setText(p_device->getLoopbackFile());
	} else {
		ui.valLoopbackFile->setVisible(false);
		ui.labLoopbackFile->setVisible(false);
	}
	fillParitions(p_device);
	fillMountPoints(p_device);
	connect(ui.btnClose,SIGNAL(clicked()),this,SLOT(close()));
	fillAliases(ui.deviceAliases,ui.noAliasesLabel, p_device);
	fillSlaves(p_device);
}

bool TFormDevInfo::fillMountPointItems(QStandardItemModel *p_model,TDeviceBase *p_device)
{
	TLinkListItem<TMount> *l_current=p_device->getMountStart();
	int  l_cnt=p_model->rowCount();
	bool l_found=false;
	while(l_current != nullptr){
		p_model->setItem(l_cnt,0,new QStandardItem(p_device->getName()));
		p_model->setItem(l_cnt,1,new QStandardItem(l_current->getItem()->getMountPoint()));
		l_found=true;
		l_cnt++;
		l_current=l_current->getNext();
	}	
	return  l_found;
}

void TFormDevInfo::fillMountPoints(TDevice *p_device)
{
	QStandardItemModel        *l_model=new QStandardItemModel(0,2,this);
	TLinkListItem<TPartition> *l_partition=p_device->getPartitionStart();
	QString l_value;
	l_model->setHorizontalHeaderItem(0,new QStandardItem(QString(i18n("Device"))));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(QString(i18n("Mount point"))));

	bool l_found=fillMountPointItems(l_model,p_device);
	while(l_partition != nullptr){
		if(fillMountPointItems(l_model,l_partition->getItem())) l_found=true;
		l_partition=l_partition->getNext();
	}

	ui.mountPoints->setModel(l_model);
	ui.mountPoints->setVisible(l_found);
	ui.noMountPointsLabel->setVisible(!l_found);
	if(l_found){
		ui.mountPoints->resizeRowsToContents();
		ui.mountPoints->resizeColumnsToContents();	
	}
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
	ui.partInfo->setModel(l_model);	
}

//Fill slaves tab
void TFormDevInfo::fillSlaves(TDevice* p_device)
{
	
	
	if(p_device->getSlaves()->length()==0){
		ui.slaveList->setVisible(false);
	} else {
		ui.noSlaveLabel->setVisible(false);
		QStandardItemModel          *l_model=new QStandardItemModel(p_device->getSlaves()->count(),1,this);
		QListIterator<TDeviceBase *> l_item(*p_device->getSlaves());
		TDeviceBase                 *l_device;
		int l_cnt=0;
		l_model->setHorizontalHeaderItem(0,new  QStandardItem(i18n("Slave name")));
		while(l_item.hasNext()){
			l_device=l_item.next();
			l_model->setItem(l_cnt,new QStandardItem(l_device->getName()));
			l_cnt++;
		}
		ui.slaveList->setModel(l_model);
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
