#include "formdevinfo.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QTableView>
#include <KSharedConfig>
#include <KConfigGroup>
#include "base/globals.h"
#include "data/device.h"
#include "data/devicelist.h"
#include "data/partition.h"
#include "base/linklist.h"
#include "data/mount.h"
#include "data/devicealias.h"
#include "gui/formparinfo.h"
#include <klocalizedstring.h>
//if device selection changes
void TFormDevInfo::deviceSelected(int p_index)
{	
	TDeviceBase *l_deviceBase=deviceList->getDeviceByName(ui.deviceName->currentText());
	if(TDevice *l_device=dynamic_cast<TDevice *>(l_deviceBase)){
		setInfo(l_device);
	}
}

void TFormDevInfo::clickPartition(const QModelIndex &p_index)
{
	QString l_partition=p_index.data().toString();
	TDeviceBase *l_device=deviceList->getDeviceByName(l_partition);
	if(l_device !=nullptr){
		TPartition *l_partition=dynamic_cast<TPartition*>(l_device);
		if(l_partition != nullptr){
			TFormParInfo l_form(deviceList,l_partition);
			l_form.exec();
			close();
		}
	}
}


//Initilize device selectionlist
//p_list =>List of devices
//p_device=>Current selected device

void TFormDevInfo::initDevSelect(TDeviceList *p_list,TDevice *p_device)
{
	TDevice *l_device;
	TLinkListIterator<TDevice> l_iter(p_list);
	int l_index=0;
	while(l_iter.hasNext()){
		l_device=l_iter.next();
		ui.deviceName->addItem(l_device->getName());
		if(p_device->getName()==l_device->getName()){
			ui.deviceName->setCurrentIndex(l_index);
		}
		l_index++;
	}
}

//Fill all field of form with information from p_device

void TFormDevInfo::setInfo(TDevice* p_device)
{
	ui.sizeLabel->setText(QString(QString::number(p_device->getSize())));
	ui.modelLabel->setText(p_device->getModel());
	ui.removeableLabel->setText(p_device->getRemovable()?i18n("Yes"):i18n("No"));
	ui.readonlyLabel->setText(p_device->getReadonly()?i18n("Yes"):i18n("No"));
	ui.labelLabel->setText(p_device->getLabel());
	ui.typeLabel->setText(p_device->getType());
	ui.vendorLabel->setText(p_device->getVendor());
	ui.scsibusLabel->setText(p_device->getScsiBus());
	ui.usbBusLabel->setText(p_device->getUsbBus());
	ui.iscsiHost->setText(p_device->getIScsiAddress());
	ui.ssdLabel->setText(p_device->getRotational()?i18n("Rotational"):i18n("SSD"));
	if(p_device->getLoopbackFile().length()>0){
		ui.valLoopbackFile->setText(p_device->getLoopbackFile());
	} else {
		ui.valLoopbackFile->setVisible(false);
		ui.labLoopbackFile->setVisible(false);
	}
	fillParitions(p_device);
	fillMountPoints(p_device);
	fillAliases(ui.deviceAliases,ui.noAliasesLabel, p_device);
	fillSlaves(p_device);
}


TFormDevInfo::TFormDevInfo(TDeviceList *p_list,TDevice *p_device):TFormBaseDevInfo()
{
	
	ui.setupUi(this);
	deviceList=p_list;
	initDevSelect(p_list,p_device);
	setInfo(p_device);
	connect(ui.btnClose,SIGNAL(clicked()),this,SLOT(close()));
	connect(ui.deviceName,SIGNAL(currentIndexChanged(int)),this,SLOT(deviceSelected(int)));
	connect(ui.partInfo,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(clickPartition(const QModelIndex &)));

}

bool TFormDevInfo::fillMountPointItems(QStandardItemModel *p_model,TDeviceBase *p_device)
{	
	int  l_cnt=p_model->rowCount();
	bool l_found=false;
	
	TMount *l_mount;
	TLinkListIterator<TMount> l_iter(p_device->getMounts());
	while(l_iter.hasNext()){
		l_mount=l_iter.next();	
		p_model->setItem(l_cnt,0,new QStandardItem(p_device->getName()));
		p_model->setItem(l_cnt,1,new QStandardItem(l_mount->getMountPoint()));
		p_model->setItem(l_cnt,2,new QStandardItem(l_mount->getType()));
		l_found=true;
		l_cnt++;
	}
	return  l_found;
}

void TFormDevInfo::fillMountPoints(TDevice *p_device)
{
	QStandardItemModel        *l_model=new QStandardItemModel(0,3,this);
	QString l_value;
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Device")));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Mount point")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Fs. type")));

	bool l_found=fillMountPointItems(l_model,p_device);
	TLinkListIterator<TPartition> l_iter(p_device->getPartitions());
	while(l_iter.hasNext()){
		if(fillMountPointItems(l_model,l_iter.next())) l_found=true;
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
	TPartition *l_partition;
	QStringList l_deviceRow;
	QStandardItemModel *l_model=new QStandardItemModel(p_device->getNumPartitions(),1,this);
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Name")));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Type")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Size")));
	l_model->setHorizontalHeaderItem(3,new QStandardItem(i18n("Start(Bytes)")));
	l_model->setHorizontalHeaderItem(4,new QStandardItem(i18n("Available")));
	l_model->setHorizontalHeaderItem(5,new QStandardItem(i18n("Mount point")));
	
	
	TLinkListIterator<TPartition> l_iter(p_device->getPartitions());
	int l_cnt=0;
	QStandardItem *l_item;
	while(l_iter.hasNext()){
		l_partition=l_iter.next();
		l_deviceRow.clear();
		l_item=new QStandardItem(l_partition->getName());
		l_item->setData(l_partition->getName());
		l_model->setItem(l_cnt,0,l_item);
		l_model->setItem(l_cnt,1,new QStandardItem(l_partition->getType()));
		l_model->setItem(l_cnt,2,new QStandardItem(l_partition->getReadableSize()));
		l_model->setItem(l_cnt,3,new QStandardItem(QString::number(l_partition->getStart())));
		l_model->setItem(l_cnt,4,new QStandardItem(QString::number(l_partition->getFree())));
		l_model->setItem(l_cnt,5,new QStandardItem(l_partition->getMountText()));
		
		l_cnt++;
	}
	ui.partInfo->setModel(l_model);	
	ui.partInfo->setWordWrap(false);
	ui.partInfo->resizeRowsToContents();
	ui.partInfo->resizeColumnsToContents();	
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
