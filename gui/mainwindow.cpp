#include "mainwindow.h"
#include <QWidget>
#include <QString>
#include <QStandardItem>
#include <QStandardItemModel> 
#include <QVariantList>
#include <QApplication>
#include <QResizeEvent>
#include <KSharedConfig>
#include <KConfigGroup>
#include "data/deviceinfo.h"
#include "data/btrfs.h"
#include "ui_main.h"
#include "base/globals.h"
#include "fieldconfig.h"
#include "gui/formdevinfo.h"
#include "gui/formparinfo.h"
#include "mainwindow.h"
#include "about.h"
#include "base/utils.h"
#include "data/mtab.h"

QApplication *g_app;

void TMainWindow::sourceChanged(int p_index  PAR_UNUSED)
{
	refresh();
}

void TMainWindow::refresh()
{	
	readConfiguation();
	if(info != nullptr) delete info;
	info=new TDeviceInfo();
	info->getDisks();
	changeManager.setInfo(info);
	fillDevice();
	fillRaid();	
	fillMtab();
}

void TMainWindow::fillMtab()
{
	TLinkListItem<TMTabEntry> *l_current=info->getMTab()->getEntriesStart();
	QStandardItemModel *l_model=new QStandardItemModel(0,6,this);
	TMTabEntry *l_info;
	QString l_note;
	int l_cnt=0;
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Options")));

	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Device")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Real device")));
	l_model->setHorizontalHeaderItem(3,new QStandardItem(i18n("Mount point")));
	l_model->setHorizontalHeaderItem(4,new QStandardItem(i18n("Type")));
	l_model->setHorizontalHeaderItem(5,new QStandardItem(i18n("Options")));
	while(l_current){
		l_info=l_current->getItem();
		l_model->setItem(l_cnt,1,new QStandardItem(l_info->getDevice()));
		l_model->setItem(l_cnt,2,new QStandardItem(l_info->getRealDevice()!=nullptr?l_info->getRealDevice()->getName():""));
		l_model->setItem(l_cnt,3,new QStandardItem(l_info->getMountPoint()));
		l_model->setItem(l_cnt,4,new QStandardItem(l_info->getType()));
		l_model->setItem(l_cnt,5,new QStandardItem(l_info->getOptions()));		
		switch(l_info->isMounted()){
			case TMTabEntry::NOTMOUNTED : l_note = i18n("Not mounted\n");break;
			case TMTabEntry::DIFMOUNTED : l_note = i18n("Mounted on different path \n");break;
			default:
				l_note="";
		}
		if(l_info->getRealDevice() != nullptr){	
			if(l_info->isSameType()==TMTabEntry::NOTSAMETYPE) l_note +=i18n("Wrong type. Type is (%1)",l_info->getRealDevice()->getType());
			if(l_info->getRealDevice()->hasPartitions()) l_note+=i18n("Device not mountable (has partitions)");
		}
		l_model->setItem(l_cnt,0,new QStandardItem(l_note));
		l_current=l_current->getNext();
		l_cnt++;
	}
	ui.mtabList->setModel(l_model);
	ui.mtabList->resizeRowsToContents();
	ui.mtabList->resizeColumnsToContents();
}

//Fill Raid TAb

void TMainWindow::fillRaid()
{
	TRaidDevice *l_info;	
	TLinkListItem<TRaidDevice> *l_item;
	
	int l_cnt=0;
	
	
	QStandardItemModel *l_model=new QStandardItemModel(info->getRaidList()->getLength(),4,this);
	
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Device")));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Raid members")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Raid level")));
	l_model->setHorizontalHeaderItem(3,new QStandardItem(i18n("Raid type")));
	l_model->setHorizontalHeaderItem(4,new QStandardItem(i18n("Mounted point")));
	
	l_item=info->getRaidList()->getTop();
	
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

//Fill row with data
// p_begin - Column 0..p_begin-1 is fixed columns from p_begin are configured
// p_model - model for fillen data
// p_row   - row number
// p_list  - List with data

void TMainWindow::displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list)
{
	int l_fieldId;
	QStandardItem *l_item;
	
//fill fixed columns 
	for(int l_cnt=0;l_cnt<p_begin;l_cnt++){
		l_item=new QStandardItem(p_list[l_cnt]);		
		p_model->setItem(p_row,l_cnt,l_item);
	}
	
//fill flexible columns
	for(int l_cnt=0;l_cnt<enableDeviceFields.count();l_cnt++){
		l_fieldId=enableDeviceFields[l_cnt].toInt();
		if(l_fieldId+p_begin<p_list.count()){
			p_model->setItem(p_row,l_cnt+p_begin,new QStandardItem(p_list[l_fieldId+p_begin]));
		}
	}
}

// Fill the header of the configured columns
void TMainWindow::fillHeader(int p_begin,QStandardItemModel *p_model){
	int l_fieldId;
	for(int l_cnt=0;l_cnt<enableDeviceFields.count();l_cnt++){
		l_fieldId=enableDeviceFields[l_cnt].toInt();
		if(l_fieldId<g_numDeviceFields){
			p_model->setHorizontalHeaderItem(l_cnt+p_begin,new QStandardItem(QString(i18n(g_deviceFields[l_fieldId]))));
		}
	}
}

//Fill Device tab in main main window 

void TMainWindow::fillDevice()
{
	const QMap<QString,TDeviceBase *> *l_map;
	TDeviceList *l_devices=info->getDevices();
	int l_selectedType=ui.itemSource->currentIndex();
	QString l_extraLabel;

	switch(l_selectedType){
		case 1:	l_map=l_devices->getIdIndex();
			l_extraLabel=i18n("Id");
			break;
		case 2:	l_map=l_devices->getLabelIndex();
			l_extraLabel=i18n("Label");
			break;
		case 3:	l_map=l_devices->getUuidIndex();
			l_extraLabel=i18n("Uuid");
			break;
		case 4:	l_map=l_devices->getPathIndex();
			l_extraLabel=i18n("Path");
			break;
		case 5:	l_map=l_devices->getLvmIndex();
			l_extraLabel=i18n("LVM");
			break;
		default:
			l_map=l_devices->getNameIndex();
	}
	
	QStandardItemModel *l_model=new QStandardItemModel(l_map->count(),1,this);	
	devModel=l_model;
	
	QStringList l_deviceRow;
	
	int l_cnt=0;
	int l_fixed=0;
	
	if(l_extraLabel.length()>0){
		l_model->setHorizontalHeaderItem(l_fixed,new QStandardItem(l_extraLabel));
		l_fixed++;
	}
	l_model->setHorizontalHeaderItem(l_fixed,new QStandardItem(i18n("Name")));
	l_fixed++;
	l_model->setHorizontalHeaderItem(l_fixed,new QStandardItem(i18n("Partition")));
	l_fixed++;

	fillHeader(l_fixed,l_model);
	
	QMapIterator<QString,TDeviceBase *> l_mi(*l_map);
	while(l_mi.hasNext()){
		l_mi.next();		
		l_deviceRow.clear();
		if(l_selectedType>0){
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

	ui.itemSource->addItem(i18n("Devices"));
	ui.itemSource->addItem(i18n("Id"));
	ui.itemSource->addItem(i18n("Labels"));
	ui.itemSource->addItem(i18n("Uuid"));
	ui.itemSource->addItem(i18n("Path"));
	ui.diskList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	
	config=KSharedConfig::openConfig();
	
	KConfigGroup  l_configGroup=config->group(QStringLiteral("windows"));
	int l_width=l_configGroup.readEntry(QStringLiteral("mainWidth"),-1);
	int l_height=l_configGroup.readEntry(QStringLiteral("mainHeight"),-1);
	if((l_width>0) && (l_height>0)){
		resize(l_width,l_height);
	}
	
	g_app->setWindowIcon(QIcon(QStringLiteral(":/icons/mainicon.png")));
	setWindowIcon(QIcon(QStringLiteral(":/icons/mainicon.png")));
	refresh();
	
	connect(ui.actionQuit,&QAction::triggered,g_app,QApplication::quit);
	connect(ui.actionFields,&QAction::triggered, this,&TMainWindow::showFieldChooser);
	connect(ui.refreshButton,SIGNAL(pressed()),this,SLOT(refresh())); 
	connect(ui.itemSource,SIGNAL(currentIndexChanged(int)),this,SLOT(sourceChanged(int)));	
	connect(ui.diskList,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(doubleClickedDevGrid(const QModelIndex &)));	
	connect(ui.actionAbout,&QAction::triggered,this,&TMainWindow::showAbout);	
	
	checkChange.start(1000);
	connect(&checkChange,SIGNAL(timeout()),this,SLOT(timeOutCheckChange()));

	ui.deleteChangeMessage->setVisible(false);
	connect(ui.deleteChangeMessage,SIGNAL(pressed()),this,SLOT(clearChangeMessage()));
}

//Clear "change message" (Mounts/Unmounts/new device/remove etc..)
void TMainWindow::clearChangeMessage()
{
	ui.arInfo->setText("");
	ui.deleteChangeMessage->setVisible(false);
	changeManager.clear();
}

//Check periodically  if there is any device change

void TMainWindow::timeOutCheckChange()
{
	QString l_what;

	
	if(refreshNext){
		if(ui.autoRefresh->isChecked()){
			refresh();
			refreshNext=false;
		}
	}

//Read all current mountes  and compares is there is any changes
//All changes are collected in mount and umount set until the user presses the "clear message" button


	changeManager.getChanged(l_what,refreshNext);

	if(refreshNext){
		ui.arInfo->setText(l_what);
		ui.deleteChangeMessage->setVisible(true);		
	}
		
}


TMainWindow::~TMainWindow()
{
	if(info)delete info;
	if(devModel) delete devModel;
}

void TMainWindow::showAbout()
{
	TAbout l_about;
	l_about.exec();
}

void TMainWindow::resizeEvent(QResizeEvent *p_event)
{
	KConfigGroup  l_configGroup=config->group(QStringLiteral("windows"));
	l_configGroup.writeEntry(QStringLiteral("mainWidth"),p_event->size().width() );
	l_configGroup.writeEntry(QStringLiteral("mainHeight"),p_event->size().height());
	config->sync();
}
