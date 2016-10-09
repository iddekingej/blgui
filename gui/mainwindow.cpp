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
#include "gui/visibletabs.h"
#include "mainwindow.h"
#include "about.h"
#include "base/utils.h"
#include "data/mtab.h"
#include "data/iscsi.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include "data/diskstat.h"
#include <klocalizedstring.h>
#include <QModelIndexList>
#include "mountdialog.h"
#include <unistd.h>
#include <sys/types.h>
#include <QMessageBox>

QApplication *g_app;


class TGridDelegate : public QStyledItemDelegate
{
public:
    TGridDelegate(QObject* p_parent ) : QStyledItemDelegate(p_parent) { }
 
    void paint(QPainter* p_painter, const QStyleOptionViewItem& p_option, const QModelIndex& p_index ) const
    {
        p_painter->save();
        p_painter->setPen(QColor(Qt::lightGray));
        p_painter->drawRect(p_option.rect);
        p_painter->restore();
 
        QStyledItemDelegate::paint(p_painter, p_option, p_index);
    }
};


void TMainWindow::handleMount()
{	
	QModelIndexList l_list=ui.diskList->selectionModel()->selectedIndexes();
	TDeviceBase *l_device=nullptr;
	QString l_message="";
	if(getuid()!=0){
		l_message=i18n("Only root can mount");
	}  else if(l_list.length()==0){
		l_message=i18n("No device selected");
	} else {
		QModelIndex l_index=l_list[0];		
		QString l_name=l_index.data(Qt::UserRole + 1).toString();
		l_device=info->getDevices()->getDeviceByName(l_name);
		if(l_device==nullptr){
			l_message=i18n("Device not found");
		} else if(l_device->hasPartitions()){
			l_message=i18n("Can't mount device");
		}
	}
	if(l_message.length()>0){
		QMessageBox l_box;
		l_box.setText(l_message);
		l_box.setStandardButtons(QMessageBox::Ok);		
		l_box.exec();
		return;
	}
	if(l_device !=nullptr){
		TMountDialog l_dialog(l_device);
		l_dialog.exec();
		refresh();
	}
}

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
	fillIscsi();
	fillStats();
}

void TMainWindow::fillIscsi()
{
	
	QStandardItemModel *l_model=new QStandardItemModel(0,4,this);
	TDevice            *l_device;
	int                l_cnt=0;
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Session")));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Address")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Device")));
	l_model->setHorizontalHeaderItem(3,new QStandardItem(i18n("Iscsi bus")));
	TLinkListIterator<TIScsiSession> l_sessionIter(info->getIscsiSessions()->getSessions());
	TIScsiSession *l_session;
	while(l_sessionIter.hasNext()){
		l_session=l_sessionIter.next();
		QListIterator<TDevice *> l_iter(l_session->getDevices());
		while(l_iter.hasNext()){
			l_device=l_iter.next();
			l_model->setItem(l_cnt,0,new QStandardItem(l_session->getSession()));
			l_model->setItem(l_cnt,1,new QStandardItem(l_session->getConnection()));
			l_model->setItem(l_cnt,2,new QStandardItem(l_device->getName()));
			l_model->setItem(l_cnt,3,new QStandardItem(l_device->getScsiBus()));
			l_cnt++;
		}	
	}
	ui.iscsiTable->setModel(l_model);
	ui.iscsiTable->resizeRowsToContents();
	ui.iscsiTable->resizeColumnsToContents();
}
void TMainWindow::fillMtab()
{
	QStandardItemModel *l_model=new QStandardItemModel(0,6,this);
	TMTabEntry *l_info;
	QString l_note;
	int l_cnt=0;
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Comments")));

	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Device")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Real device")));
	l_model->setHorizontalHeaderItem(3,new QStandardItem(i18n("Mount point")));
	l_model->setHorizontalHeaderItem(4,new QStandardItem(i18n("Type")));
	l_model->setHorizontalHeaderItem(5,new QStandardItem(i18n("Options")));
	TLinkListIterator<TMTabEntry> l_mtabIter(info->getMTab()->getEntries());;
	while(l_mtabIter.hasNext()){
		l_info=l_mtabIter.next();
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
		l_cnt++;
	}
	ui.mtabList->setModel(l_model);
	ui.mtabList->resizeRowsToContents();
	ui.mtabList->resizeColumnsToContents();
}

//Fill Raid TAb

void TMainWindow::fillRaid()
{
	int l_cnt=0;
	QStandardItemModel *l_model=new QStandardItemModel(info->getRaidList()->getLength(),4,this);

	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Device")));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Raid members")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Raid level")));
	l_model->setHorizontalHeaderItem(3,new QStandardItem(i18n("Raid type")));
	l_model->setHorizontalHeaderItem(4,new QStandardItem(i18n("Mounted point")));
	
	TLinkListIterator<TRaidDevice> l_raidIter(info->getRaidList()->getDevices());
	TRaidDevice *l_raid;
	while(l_raidIter.hasNext()){
		l_raid=l_raidIter.next();
		l_model->setItem(l_cnt,0,new QStandardItem(l_raid->getDevice()->getName() ));
		l_model->setItem(l_cnt,1,new QStandardItem(l_raid->getRaidDeviceString()));
		l_model->setItem(l_cnt,2,new QStandardItem(l_raid->getRaidLevel()));
		l_model->setItem(l_cnt,3,new QStandardItem(l_raid->getType()));
		l_model->setItem(l_cnt,4,new QStandardItem(l_raid->getDevice()->getMountText()));
		l_cnt++;				
	}
		
	ui.raidList->setModel(l_model);
	ui.raidList->resizeRowsToContents();
	ui.raidList->resizeColumnsToContents();
}

void TMainWindow::fillStats()
{
	int l_cnt=0;
	QStandardItemModel *l_model=new QStandardItemModel(info->getRaidList()->getLength(),4,this);
	TDiskStatList *l_info=new TDiskStatList();
	l_info->readInfo();
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Device")));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Read(sectors)")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Read(div)")));
	l_model->setHorizontalHeaderItem(3,new QStandardItem(i18n("Write(sectors)")));
	l_model->setHorizontalHeaderItem(4,new QStandardItem(i18n("Write(div)")));
	TLinkListIterator<TDiskStat> l_iter(l_info->getList());
	TDiskStat *l_item;
	TDiskStat *l_prv;
	while(l_iter.hasNext()){
		l_item=l_iter.next();
		l_prv=nullptr;
		if(prvStats != nullptr){
			l_prv=prvStats->getByName(l_item->getDevice());
		}
		l_model->setItem(l_cnt,0,new QStandardItem(l_item->getDevice()));
		l_model->setItem(l_cnt,1,new QStandardItem(QString::number(l_item->getReadSectors())));
		l_model->setItem(l_cnt,2,new QStandardItem(QString::number(l_prv!=nullptr?l_item->getReadSectors()-l_prv->getReadSectors():0)));		
		l_model->setItem(l_cnt,3,new QStandardItem(QString::number(l_item->getWriteSectors())));
		l_model->setItem(l_cnt,4,new QStandardItem(QString::number(l_prv != nullptr?l_item->getWriteSectors()-l_prv->getWriteSectors():0)));
		l_cnt++;
	}
	ui.stats->setModel(l_model);
	ui.stats->resizeRowsToContents();
	ui.stats->resizeColumnsToContents();
	if(prvStats!=nullptr) delete prvStats;
	prvStats=l_info;
	
}



//Fill row with data
// p_begin - Column 0..p_begin-1 is fixed columns from p_begin are configured
// p_model - model for fillen data
// p_row   - row number
// p_list  - List with data

void TMainWindow::displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list,QStandardItem *p_parent)
{
	int l_fieldId;
	QStandardItem *l_item;
	
//fill fixed columns 
	for(int l_cnt=0;l_cnt<p_begin;l_cnt++){
		l_item=new QStandardItem(p_list[l_cnt]);	
		if(p_parent != nullptr){
		    p_parent->setChild(p_row,l_cnt,l_item);
		} else {
		    p_model->setItem(p_row,l_cnt,l_item);
		}
	}
	
//fill flexible columns
	for(int l_cnt=0;l_cnt<enableDeviceFields.count();l_cnt++){
		l_fieldId=enableDeviceFields[l_cnt].toInt();
		if(l_fieldId+p_begin<p_list.count()){
			if(p_parent !=nullptr){
			    p_parent->setChild(p_row,l_cnt+p_begin,new QStandardItem(p_list[l_fieldId+p_begin]));			    
			} else {
			    p_model->setItem(p_row,l_cnt+p_begin,new QStandardItem(p_list[l_fieldId+p_begin]));
			}
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

//Collect all expanded tree items. This callled before a refresh
//After refresh all tree items are restored with setExpandedDevRows
//p_list ->  device names which are expanded
void TMainWindow::getExpandedDevRows(QSet<QString> &p_list)
{
	p_list.clear();
	if(devModel != nullptr){
		QModelIndex l_index;		
		for(int l_row=0;l_row<devModel->rowCount();l_row++){
			l_index=devModel->index(l_row,0);
			if(ui.diskList->isExpanded(l_index)){
				p_list += l_index.data().toString();
			}
		}
	}
}

//expand all nodes for devices in set p_lists
void TMainWindow::setExpandedDevRows(QSet< QString >& p_list)
{
	QModelIndex l_index;
	
	for(int l_row=0;l_row<devModel->rowCount();l_row++){
		l_index=devModel->index(l_row,0);
		if(p_list.contains(l_index.data().toString())){
			ui.diskList->setExpanded(l_index,true);
		}
	}
}

//Fill devices tab as a tree
void TMainWindow::fillDeviceTree()
{
    	QStringList l_deviceRow;
	QStandardItem *l_parent;
    	QStandardItemModel *l_model=new QStandardItemModel(0,1,this);	
    	QSet<QString> l_expanded;
	
	getExpandedDevRows(l_expanded);
	devModel=l_model;
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Name")));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Partition")));
	fillHeader(2,l_model);
	TLinkListIterator<TDevice> l_iter(info->getDevices());
	TDevice *l_device;
	TPartition *l_partition;
	int l_cnt=0;
	int l_partRow;
	while(l_iter.hasNext()){
	    l_device=l_iter.next();
	    l_deviceRow.clear();
	    l_device->fillDataRow(l_deviceRow);
	    displayRow(2,l_model,l_cnt,l_deviceRow,nullptr);
	    l_parent=l_model->item(l_cnt,0);
	    TLinkListIterator<TPartition> l_iterPartition(l_device->getPartitions());
	    l_model->item(l_cnt)->setData(l_device->getName());
	    l_partRow=0;
	    while(l_iterPartition.hasNext()){
		l_partition=l_iterPartition.next();
		l_deviceRow.clear();
		l_partition->fillDataRow(l_deviceRow);
		displayRow(2,l_model,l_partRow,l_deviceRow,l_parent);
		l_parent->child(l_partRow)->setData(l_partition->getName());
		l_partRow++;
	    }
	    l_cnt++;
	}
	ui.diskList->setWordWrap(false);
	ui.diskList->setModel(l_model);
	ui.diskList->setSortingEnabled(true);
	
	setExpandedDevRows(l_expanded);
}

//Fill Device tab in main main window 

void TMainWindow::fillDeviceGrid()
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
		displayRow(l_fixed,l_model,l_cnt,l_deviceRow,nullptr);
		l_model->item(l_cnt)->setData(l_mi.value()->getName());
		l_cnt++;
	}

	ui.diskList->setWordWrap(false);
	ui.diskList->setModel(l_model);
}

void TMainWindow::fillDevice()
{
	if((ui.itemSource->currentIndex()==0) && g_config.getDeviceAsTree()){
		fillDeviceTree();	  
	}  else {
		fillDeviceGrid();
	}
}

void TMainWindow::showFieldChooser(){
	printf("xxx/n");
	TFieldsConfig l_field;	
	l_field.exec();
	refresh();
}

void TMainWindow::readConfiguation()
{
	enableDeviceFields.clear();	
	enableDeviceFields=g_config.getDeviceFields();
}

void TMainWindow::doubleClickedDevGrid(const QModelIndex &p_index)
{
	if(devModel != nullptr){
		QString l_name;
		TDeviceBase *l_deviceBase;
		l_name=p_index.data(Qt::UserRole + 1).toString();
		l_deviceBase=info->getDevices()->getDeviceByName(l_name);
		if(l_deviceBase){
			if(TPartition *l_partition=dynamic_cast<TPartition *>(l_deviceBase)){
				TFormParInfo l_parInfo(info->getDevices(),l_partition);
				l_parInfo.exec();
			} else 	if(TDevice *l_device=dynamic_cast<TDevice *>(l_deviceBase)){
				TFormDevInfo l_info(info->getDevices(),l_device);
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
	
	int l_width= g_config.getMainWindowWidth();
	int l_height=g_config.getMainWindowHeight();
	if((l_width>0) && (l_height>0)){
		resize(l_width,l_height);
	}
	ui.diskList->setItemDelegate(new TGridDelegate(ui.diskList));
	g_app->setWindowIcon(QIcon(QStringLiteral(":/icons/mainicon.png")));
	setWindowIcon(QIcon(QStringLiteral(":/icons/mainicon.png")));
	refresh();
	
	connect(ui.actionQuit,SIGNAL(triggered()),g_app,SLOT(quit()));
	connect(ui.actionFields,SIGNAL(triggered()), this,SLOT(showFieldChooser()));
	connect(ui.refreshButton,SIGNAL(pressed()),this,SLOT(refresh())); 
	connect(ui.itemSource,SIGNAL(currentIndexChanged(int)),this,SLOT(sourceChanged(int)));	
	connect(ui.diskList,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(doubleClickedDevGrid(const QModelIndex &)));	
	connect(ui.actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));	
	connect(ui.visibleTabs,SIGNAL(triggered()),this,SLOT(visibleTabs()));
	connect(ui.mountButton,SIGNAL(pressed()),this,SLOT(handleMount()));
	checkChange.start(1000);
	connect(&checkChange,SIGNAL(timeout()),this,SLOT(timeOutCheckChange()));
	
	ui.deleteChangeMessage->setVisible(false);
	connect(ui.deleteChangeMessage,SIGNAL(pressed()),this,SLOT(clearChangeMessage()));
	tabs[0]=ui.tabDisks;
	tabs[1]=ui.tabRaid;
	tabs[2]=ui.tabFstab;
	tabs[3]=ui.tabIscsi;
	tabs[4]=ui.tabStats;
	tabsVisible[0]=nullptr;
	tabsVisible[1]=nullptr;
	tabsVisible[2]=nullptr;
	tabsVisible[3]=nullptr;
	tabsVisible[4]=nullptr;
	ui.diskList->sortByColumn(0,Qt::AscendingOrder);
	if(g_config.getExpandByDefault()){
		ui.diskList->expandAll();
	}
	setVisibleTabs();

}
//MyItem * myObj 
//       = static_cast<MyItem*>
//         (ui.myTreeView->currentIndex().internalPointer());

//Set which tab is visible from config 

void TMainWindow::setTabVisible(int p_indx,bool p_flag,const QString &p_label)
{
	if(p_flag){
		QWidget *l_tab=tabsVisible[p_indx];
		if(tabsVisible[p_indx] != nullptr){
			int l_cnt;
			int l_pos=0;
			for(l_cnt=0;l_cnt<4 && tabs[l_cnt]!= l_tab;l_cnt++){
				if(ui.info->indexOf(tabs[l_cnt])>=0) l_pos++;
			}	
			ui.info->insertTab(l_pos,l_tab,p_label);
			tabsVisible[p_indx]=nullptr;
		}
	} else {
		if(tabsVisible[p_indx] ==nullptr){
			int l_indx=ui.info->indexOf(tabs[p_indx]);
			if(l_indx>=0){
				ui.info->removeTab(l_indx);
				tabsVisible[p_indx]=tabs[p_indx];
			}
		}
	}
}

void TMainWindow::setVisibleTabs(){
	setTabVisible(0,g_config.getDisksTab(),i18n("Disks"));
	setTabVisible(1,g_config.getRaidTab() ,i18n("Raid"));
	setTabVisible(2,g_config.getFsTabTab(),i18n("Fstab"));
	setTabVisible(3,g_config.getIscsiTab(),i18n("Iscsi"));
	setTabVisible(4,g_config.getStatsTab(),i18n("Stats"));
}

//Display "Visible tab" dialog when menu option is l_selected

void TMainWindow::visibleTabs()
{
	TVisibleTabs l_dialog;
	l_dialog.exec();
	setVisibleTabs();
}


//Clear "change message" (Mounts/Unmounts/new device/remove etc..)
void TMainWindow::clearChangeMessage()
{
	ui.arInfo->setText(QStringLiteral(""));
	ui.deleteChangeMessage->setVisible(false);
	changeManager.clear();
}

//Check periodically  if there is any device change

void TMainWindow::timeOutCheckChange()
{
	QString l_what;

	fillStats();
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
	if(prvStats != nullptr) delete prvStats;
}

void TMainWindow::showAbout()
{
	TAbout l_about;
	l_about.exec();
}

void TMainWindow::resizeEvent(QResizeEvent *p_event)
{
	g_config.setMainWindowSize(p_event->size().width() ,p_event->size().height());
	g_config.sync();
}
