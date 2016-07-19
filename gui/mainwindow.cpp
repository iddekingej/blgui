#include "mainwindow.h"
#include <QWidget>
#include <QString>
#include <QStandardItem>
#include <QStandardItemModel> 
#include <QVariantList>
#include <QApplication>
#include "data/deviceinfo.h"
#include "data/btrfs.h"
#include "ui_main.h"
#include "base/globals.h"
#include "fieldconfig.h"
#include "gui/formdevinfo.h"
#include "gui/formparinfo.h"
#include "mainwindow.h"
#include "about.h"

QApplication *g_app;

void TMainWindow::sourceChanged(int p_index)
{
	refresh();
}

void TMainWindow::refresh()
{	
	readConfiguation();
	if(info != nullptr) delete info;
	info=new TDeviceInfo();
	info->getDisks();
	fillTable(info);
	fillRaid(info);	
}

void TMainWindow::fillRaid(TDeviceInfo *p_info)
{
	TRaidDevice *l_info;	
	TLinkListItem<TRaidDevice> *l_item;
	
	int l_cnt=0;
	
	
	QStandardItemModel *l_model=new QStandardItemModel(p_info->getRaidList()->getLength(),4,this);
	
	l_model->setHorizontalHeaderItem(0,new QStandardItem(QString(i18n("Device"))));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(QString(i18n("Raid members"))));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(QString(i18n("Raid level"))));
	l_model->setHorizontalHeaderItem(3,new QStandardItem(QString(i18n("Raid type"))));
	l_model->setHorizontalHeaderItem(4,new QStandardItem(QString(i18n("Mounted point"))));
	
	l_item=p_info->getRaidList()->getTop();
	
	while(l_item){
		l_info=l_item->getItem();
		l_model->setItem(l_cnt,0,new QStandardItem(l_info->getDevice()->getName() ));
		l_model->setItem(l_cnt,1,new QStandardItem(l_info->getRaidDeviceString()));
		l_model->setItem(l_cnt,2,new QStandardItem(l_info->getRaidLevel()));
		l_model->setItem(l_cnt,3,new QStandardItem(l_info->getType()));
		l_model->setItem(l_cnt,4,new QStandardItem(l_info->getDevice()->getMounts()));
		l_cnt++;		
		l_item=l_item->getNext();
	}
		
	ui.raidList->setModel(l_model);
	ui.raidList->resizeRowsToContents();
	ui.raidList->resizeColumnsToContents();
}

void TMainWindow::displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list)
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

void TMainWindow::fillHeader(int p_begin,QStandardItemModel *p_model){
	int l_fieldId;
	for(int l_cnt=0;l_cnt<enableDeviceFields.count();l_cnt++){
		l_fieldId=enableDeviceFields[l_cnt].toInt();
		if(l_fieldId<g_numDeviceFields){
			p_model->setHorizontalHeaderItem(l_cnt+p_begin,new QStandardItem(QString(i18n(g_deviceFields[l_fieldId]))));
		}
	}
}

void TMainWindow::fillTable(TDeviceInfo *p_info)
{
	const QMap<QString,TDeviceBase *> *l_map;
	TDeviceList *l_devices=p_info->getDevices();
	
	switch(ui.itemSource->currentIndex()){
		case 0:l_map=l_devices->getNameIndex();break;
		case 1:l_map=l_devices->getIdIndex();break;
		case 2:l_map=l_devices->getLabelIndex();break;
		case 3:l_map=l_devices->getUuidIndex();break;
		case 4:l_map=l_devices->getPathIndex();break;
		default:
			l_map=l_devices->getNameIndex();
	}
	
	QStandardItemModel *l_model=new QStandardItemModel(l_map->count(),1,this);
	devModel=l_model;
	
	QStringList l_deviceRow;
	
	int l_cnt=0;
	int l_fixed=0;
	QString l_extraLabel;
	
	switch(ui.itemSource->currentIndex()){		
		case 1:l_extraLabel=i18n("Label");break;
		case 2:l_extraLabel=i18n("Id");break;
		case 3:l_extraLabel=i18n("Uuid");break;
		case 4:l_extraLabel=i18n("Path");break;
		default:
			break;
	}
	if(l_extraLabel.length()>0){
		l_model->setHorizontalHeaderItem(l_fixed,new QStandardItem(l_extraLabel));
		l_fixed++;
	}
	l_model->setHorizontalHeaderItem(l_fixed,new QStandardItem(QString(i18n("Name"))));
	l_fixed++;
	l_model->setHorizontalHeaderItem(l_fixed,new QStandardItem(QString(i18n("Partition"))));
	l_fixed++;

	fillHeader(l_fixed,l_model);
	
	QMapIterator<QString,TDeviceBase *> l_mi(*l_map);
	while(l_mi.hasNext()){
		l_mi.next();		
		l_deviceRow.clear();
		if(ui.itemSource->currentIndex()>0){
			l_deviceRow << l_mi.key();
		
		}
		l_mi.value()->fillDataRow(l_deviceRow);		
		displayRow(l_fixed,l_model,l_cnt,l_deviceRow);
		l_model->item(l_cnt)->setData(l_mi.value()->getName());
		l_cnt++;
	}

	ui.diskList->setWordWrap(false);
	ui.diskList->setModel(l_model);
	
	ui.diskList->resizeRowsToContents();
	ui.diskList->resizeColumnsToContents();	
}

void TMainWindow::showFieldChooser(){
	TFieldsConfig l_field;	
	l_field.exec();
	refresh();
}

void TMainWindow::readConfiguation()
{
	enableDeviceFields.clear();
	KSharedConfig::Ptr config=KSharedConfig::openConfig();
	KConfigGroup  configGroup=config->group("enabledfields");
	enableDeviceFields=configGroup.readEntry("devicefields",QVariantList());
}

void TMainWindow::doubleClickedDevGrid(const QModelIndex &p_index)
{

	if(devModel != nullptr){
		QString l_name;
		TDeviceBase *l_deviceBase;
	
		l_name=devModel->item(p_index.row(),0)->data().toString();
		l_deviceBase=info->getDevices()->getDeviceByName(l_name);
		if(l_deviceBase){
			if(TPartition *l_partition=dynamic_cast<TPartition *>(l_deviceBase)){
				TFormParInfo l_parInfo(l_partition);
				l_parInfo.exec();
			} else 	if(TDevice *l_device=dynamic_cast<TDevice *>(l_deviceBase)){
				TFormDevInfo l_info(l_device);
				l_info.exec();			
			}
		}
	}
	
}

TMainWindow::TMainWindow(QWidget *p_parent):QMainWindow(p_parent)
{
	ui.setupUi(this);
	info=nullptr;
	devModel=nullptr;
	connect(ui.actionQuit,&QAction::triggered,g_app,QApplication::quit);
	connect(ui.actionFields,&QAction::triggered, this,&TMainWindow::showFieldChooser);
	connect(ui.refreshButton,SIGNAL(pressed()),this,SLOT(refresh())); 
	connect(ui.itemSource,SIGNAL(currentIndexChanged(int)),this,SLOT(sourceChanged(int)));	
	connect(ui.diskList,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(doubleClickedDevGrid(const QModelIndex &)));	
	connect(ui.actionAbout,&QAction::triggered,this,&TMainWindow::showAbout);
	ui.itemSource->addItem(i18n("Devices"));
	ui.itemSource->addItem(i18n("Id"));
	ui.itemSource->addItem(i18n("Labels"));
	ui.itemSource->addItem(i18n("Uuid"));
	ui.itemSource->addItem(i18n("Path"));
	ui.diskList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	refresh();
}

void TMainWindow::showAbout()
{
	TAbout l_about;
	l_about.exec();
}