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
#include "gui/usertabdef.h"
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
#include "gui/formtabdef.h"
#include <QMessageBox>
#include <iostream>
#include <QListIterator>
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
	}  else if(l_list.length()>0 && ui.info->currentIndex()==0){
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
	TMountDialog l_dialog(l_device,info->getDevices()->getNameIndex());
	l_dialog.exec();
	refresh();
	
}

void TMainWindow::sourceChanged(int p_index  PAR_UNUSED)
{
	fillDevice(true);
}

void TMainWindow::refresh()
{		
	if(info != nullptr) delete info;
	info=new TDeviceInfo();
	info->getDisks();
	changeManager.setInfo(info);
	fillDevice(false);
	fillRaid();	
	fillMtab();
	fillIscsi();
	fillStats();
	fillLvm();
	fillUserTabDef();
}

void TMainWindow::fillLvm()
{
	QStandardItemModel *l_model=new QStandardItemModel(0,3,this);
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Device")));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Size")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Volume group")));
	
	TLinkList<TPhysicalVolume> *l_pvs=info->getLVM()->getPvList();
	TPhysicalVolume *l_pvInfo;
	int l_cnt=0;
	if(l_pvs != nullptr){
		TLinkListIterator<TPhysicalVolume> l_pvIter(l_pvs);
		while(l_pvIter.hasNext()){
			l_pvInfo=l_pvIter.next();
			
			
			l_model->setItem(l_cnt,0,new QStandardItem(l_pvInfo->getRealDevice()==nullptr?"":l_pvInfo->getRealDevice()->getName()));
			l_model->setItem(l_cnt,1,new QStandardItem(QString::number(l_pvInfo->getDevSize())));
			l_model->setItem(l_cnt,2,new QStandardItem(l_pvInfo->getVgName()));
			l_cnt++;
		}
	}
	int l_sortHeader=ui.pvInfo->horizontalHeader()->sortIndicatorSection();
	Qt::SortOrder l_sortOrder=ui.pvInfo->horizontalHeader()->sortIndicatorOrder();			
	setViewModel(ui.pvInfo,l_model);
	ui.pvInfo->resizeColumnsToContents();
	ui.pvInfo->resizeRowsToContents();
	ui.pvInfo->sortByColumn(l_sortHeader,l_sortOrder);
	
	TLinkList<TVolumeGroup> *l_vg=info->getLVM()->getVgList();
	   TVolumeGroup *l_vgInfo;
	TLogicalVolume *l_lvInfo;
	QStandardItemModel *l_vgModel=new QStandardItemModel(0,2,this);
	QStandardItemModel *l_lvModel=new QStandardItemModel(0,7,this);
	l_vgModel->setHorizontalHeaderItem(0,new QStandardItem(i18n("Volume group")));
	l_vgModel->setHorizontalHeaderItem(1,new QStandardItem(i18n("Id")));
	l_lvModel->setHorizontalHeaderItem(0,new QStandardItem(i18n("Logical volume")));
	l_lvModel->setHorizontalHeaderItem(1,new QStandardItem(i18n("Volume group")));
	l_lvModel->setHorizontalHeaderItem(2,new QStandardItem(i18n("Device")));	
	l_lvModel->setHorizontalHeaderItem(3,new QStandardItem(i18n("Id")));
	l_lvModel->setHorizontalHeaderItem(4,new QStandardItem(i18n("Read")));
	l_lvModel->setHorizontalHeaderItem(5,new QStandardItem(i18n("Write")));
	l_lvModel->setHorizontalHeaderItem(6,new QStandardItem(i18n("Visible")));
	l_cnt=0;
	int l_lvCnt=0;
	if(l_vg != nullptr){
		TLinkListIterator<TVolumeGroup> l_vgIter(l_vg);
		while(l_vgIter.hasNext()){
			l_vgInfo=l_vgIter.next();
			l_vgModel->setItem(l_cnt,0,new QStandardItem(l_vgInfo->getName()));
			l_vgModel->setItem(l_cnt,1,new QStandardItem(l_vgInfo->getKey()));
			l_cnt++;
			TLinkListIterator<TLogicalVolume> l_iterLv(l_vgInfo->getLogicalVolumns());
			while(l_iterLv.hasNext()){
				l_lvInfo=l_iterLv.next();
				l_lvModel->setItem(l_lvCnt,0,new QStandardItem(l_lvInfo->getName()));
				l_lvModel->setItem(l_lvCnt,1,new QStandardItem(l_vgInfo->getName()));
				l_lvModel->setItem(l_lvCnt,2,new QStandardItem(l_lvInfo->getRealDevice()!=nullptr?l_lvInfo->getRealDevice()->getName():""));
				l_lvModel->setItem(l_lvCnt,3,new QStandardItem(l_lvInfo->getId()));
				if(l_lvInfo->getReadFlag())l_lvModel->setItem(l_lvCnt,4,new QStandardItem("X"));
				if(l_lvInfo->getWriteFlag())l_lvModel->setItem(l_lvCnt,5,new QStandardItem("X"));
				if(l_lvInfo->getVisibleFlag())l_lvModel->setItem(l_lvCnt,6,new QStandardItem("X"));
				l_lvCnt++;
			}
		}
	}
	
	l_lvModel->setRowCount(l_lvCnt);
	l_vgModel->setRowCount(l_cnt);
	l_sortHeader=ui.vgList->horizontalHeader()->sortIndicatorSection();
	l_sortOrder=ui.vgList->horizontalHeader()->sortIndicatorOrder();			
	setViewModel(ui.vgList,l_vgModel);
	ui.vgList->resizeColumnsToContents();
	ui.vgList->sortByColumn(l_sortHeader,l_sortOrder);
	l_sortHeader=ui.lvList->horizontalHeader()->sortIndicatorSection();
	l_sortOrder=ui.lvList->horizontalHeader()->sortIndicatorOrder();		
	setViewModel(ui.lvList,l_lvModel);	
	ui.lvList->resizeColumnsToContents();
	ui.lvList->sortByColumn(l_sortHeader,l_sortOrder);

}

void TMainWindow::fillIscsi()
{
	int l_sortHeader=ui.iscsiTable->horizontalHeader()->sortIndicatorSection();
	Qt::SortOrder l_sortOrder=ui.iscsiTable->horizontalHeader()->sortIndicatorOrder();		
	QStandardItemModel *l_model=new QStandardItemModel(0,5,this);
	TDevice            *l_device;
	int                l_cnt=0;
	l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Session")));
	l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Address")));
	l_model->setHorizontalHeaderItem(2,new QStandardItem(i18n("Device")));
	l_model->setHorizontalHeaderItem(3,new QStandardItem(i18n("Iscsi bus")));
	l_model->setHorizontalHeaderItem(4,new QStandardItem(i18n("Target")));
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
			l_model->setItem(l_cnt,4,new QStandardItem(l_session->getTargetName()));
			l_cnt++;
		}	
	}

	setViewModel(ui.iscsiTable,l_model);
	ui.iscsiTable->resizeColumnsToContents();
	ui.iscsiTable->resizeRowsToContents();
	ui.iscsiTable->sortByColumn(l_sortHeader,l_sortOrder);
}
void TMainWindow::fillMtab()
{
	int l_sortHeader=ui.mtabList->horizontalHeader()->sortIndicatorSection();
	Qt::SortOrder l_sortOrder=ui.mtabList->horizontalHeader()->sortIndicatorOrder();	
	QStandardItemModel *l_model=new QStandardItemModel(0,6,this);
	TMTabEntry *l_info;
	QString l_note;
	int l_cnt=0;
	TDeviceBase *l_realDevice;
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
				l_note.clear();
		}
		l_realDevice=l_info->getRealDevice();
		if(l_realDevice != nullptr){	
			if(l_info->isSameType()==TMTabEntry::NOTSAMETYPE) l_note +=i18n("Wrong type. Type is (%1)",l_realDevice->getType());
			if(l_realDevice->hasPartitions()) l_note+=i18n("Device not mountable (has partitions)");
		}
		l_model->setItem(l_cnt,0,new QStandardItem(l_note));		
		l_cnt++;
	}	
	setViewModel(ui.mtabList,l_model);
	ui.mtabList->resizeColumnsToContents();
	ui.mtabList->resizeRowsToContents();
	ui.mtabList->sortByColumn(l_sortHeader,l_sortOrder);

}

//Fill Raid TAb

void TMainWindow::fillRaid()
{
	int l_cnt=0;
	int l_sortHeader=ui.raidList->horizontalHeader()->sortIndicatorSection();
	Qt::SortOrder l_sortOrder=ui.raidList->horizontalHeader()->sortIndicatorOrder();
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
	ui.raidList->resizeColumnsToContents();
	ui.raidList->resizeRowsToContents();
	ui.raidList->sortByColumn(l_sortHeader,l_sortOrder);

}

void TMainWindow::fillStats()
{
	int l_cnt=0;
	int l_sortHeader=ui.stats->horizontalHeader()->sortIndicatorSection();
	Qt::SortOrder l_sortOrder=ui.stats->horizontalHeader()->sortIndicatorOrder();
	QStandardItemModel *l_model=statsModel;
	l_model->blockSignals(true);
	statsModel->clear();
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
	l_model->blockSignals(false);
	ui.stats->resizeRowsToContents();
	ui.stats->resizeColumnsToContents();
	ui.stats->sortByColumn(l_sortHeader,l_sortOrder);
	if(prvStats!=nullptr) delete prvStats;
	prvStats=l_info;
	
}



/**
* Fill row with data
* \param p_begin - Column 0..p_begin-1 is fixed columns from p_begin are configured
* \param p_model - model for filled data
* \param p_row   - row number
* \param p_list  - List with data
* \param p_parent - parent row (for hierarchical display)
*/
void TMainWindow::displayRow(int p_begin,QStandardItemModel *p_model,int p_row,const QStringList  &p_list,QStandardItem *p_parent)
{
	int l_fieldId;
	QStandardItem *l_item;
	int l_itemSize=p_list.count();	
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
	for(int l_cnt=0;l_cnt<enableDeviceFields->count();l_cnt++){
		l_fieldId=(*enableDeviceFields)[l_cnt];		
		if(l_fieldId+p_begin<l_itemSize){
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
	for(int l_cnt=0;l_cnt<enableDeviceFields->count();l_cnt++){
		l_fieldId=(*enableDeviceFields)[l_cnt];
		if(l_fieldId<g_numDeviceFields){
			p_model->setHorizontalHeaderItem(l_cnt+p_begin,new QStandardItem(QString(i18n(g_deviceFields[l_fieldId].title))));
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
	devProxyModel->setFlexStart(2);
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
	
	devProxyModel->setSourceModel(l_model);
	setExpandedDevRows(l_expanded);
	deviceAsTree=true;
}

//Fill Device tab in main main window 

void TMainWindow::fillDeviceGrid()
{
	const QHash<QString,TDeviceBase *> *l_map;
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
	devProxyModel->setFlexStart(l_fixed);
	QHashIterator<QString,TDeviceBase *> l_mi(*l_map);
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

	devProxyModel->setSourceModel(l_model);
	deviceAsTree=false;
	
}
/** Fill device list with data
 * 
 */
void TMainWindow::fillDevice(bool p_sourceChanged)
{
	if((ui.itemSource->currentIndex()==0) && g_config.getDeviceAsTree()){
		fillDeviceTree();	  
		if(p_sourceChanged)setExpandedDevRows(expandedDevices);

	}  else {
		if(p_sourceChanged && deviceAsTree)getExpandedDevRows(expandedDevices);		
		fillDeviceGrid();
	}
}

void TMainWindow::showUserDefinedTabs(){
	TFormTabDef l_form(&userTabs);
	l_form.exec();
	setupUserTabs();
	fillUserTabDef();
}

void TMainWindow::showFieldChooser(){
	TFieldsConfig l_field;	
	bool l_expand=g_config.getExpandByDefault();
	bool l_asTree=g_config.getDeviceAsTree();
	l_field.exec();
	refresh();
/* When device list is displayed as a tree and epand by default it changed from false to true, expand tree after dialog is closed
 * or when devicelist was previous a list and now a tree and expand by default is set , then expand
 */		
	if(g_config.getDeviceAsTree()){
		if(g_config.getExpandByDefault()){
			if(!l_expand|| !l_asTree) expandDeviceAll();
		}
	}	
}


/** Displays device or partition information dialog
 *  Event handle when double clicked on device grid.  First, the name of the device/partition is retrieved (stored at column 0 of the row)
 *  next the device object is retrieved by name. If it is a partition, than partition details dialog is displayed.If it is a device object
 *  the device dialog is displayed
 * 
 *  \param p_index   Index to the cell where the user double clicks
 */

void TMainWindow::doubleClickedDevGrid(const QModelIndex &p_index)
{
	if(devModel != nullptr){
		QString l_name;
		TDeviceBase *l_deviceBase;		
		l_name=p_index.sibling(p_index.row() ,0).data(Qt::UserRole+1).toString();//get device or partition name
		l_deviceBase=info->getDevices()->getDeviceByName(l_name);
		if(l_deviceBase){
			checkChange.stop();
			if(TPartition *l_partition=dynamic_cast<TPartition *>(l_deviceBase)){
				TFormParInfo l_parInfo(info->getDevices(),l_partition);
				l_parInfo.exec();
			} else 	if(TDevice *l_device=dynamic_cast<TDevice *>(l_deviceBase)){
				TFormDevInfo l_info(info->getDevices(),l_device);
				l_info.exec();			
			}
			checkChange.start();
		}
	}
	
}

void TMainWindow::expandDeviceAll()
{
	ui.diskList->expandAll();
}

void TMainWindow::fillUserTabDef()
{	
	TDoubleLinkedListIterator<TTabDef> l_iterDef(userTabs);
	QListIterator<TUserTabDef *> l_widgetIter(userTabWidgets);
	TTabDef *l_def;
	while(l_iterDef.hasNext() && l_widgetIter.hasNext()){
		l_def=l_iterDef.next();		
		if(l_def->getIsActive()){
			l_widgetIter.next()->fillGrid(l_def,info);
		}
	}	
}


void TMainWindow::setupUserTabs()
{
	long l_no=-1;
	QWidget *l_widget=ui.info->currentWidget();
	TUserTabDef *l_defWidget;
	if(l_widget != nullptr){
		l_defWidget=dynamic_cast<TUserTabDef *>(l_widget);
		if(l_defWidget!=nullptr){
			l_no=l_defWidget->getNo();
		}
	}
	TDoubleLinkedListIterator<TTabDef> l_iter(userTabs);
	TTabDef *l_def;	
	QListIterator<TUserTabDef *> l_widgetIter(userTabWidgets);	
	while(l_widgetIter.hasNext()){
		l_defWidget=l_widgetIter.next();
		l_defWidget->close();
		delete l_defWidget;
	}
	
	userTabWidgets.clear();
	
	
	while(l_iter.hasNext()){
		l_def=l_iter.next();
		if(l_def->getIsActive()){
			l_defWidget=new TUserTabDef(nullptr);
			ui.info->addTab(l_defWidget,l_def->getName());
			userTabWidgets.append(l_defWidget);

			if(l_def->getNo()==l_no)ui.info->setCurrentWidget(l_defWidget);
		}
	}
	
}

void TMainWindow::fillMessages()
{
}


TMainWindow::TMainWindow(QWidget *p_parent):QMainWindow(p_parent)
{
	ui.setupUi(this);
	enableDeviceFields=g_config.getDeviceFields();

	info=nullptr;
	devModel=nullptr;
	userTabs.read();
	statsModel=new QStandardItemModel(0,4,this);	
	setViewModel(ui.stats,statsModel);
	notificationsModel=new QStandardItemModel(0,3,this);
	setViewModel(ui.notificationsList,notificationsModel);	
	devProxyModel=new TSortProxy(enableDeviceFields,this);
	ui.diskList->setModel(devProxyModel);
	
	ui.notifications->setVisible(false);	
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
	
	connect(ui.actionQuit,SIGNAL(triggered()),g_app,SLOT(quit()));
	connect(ui.actionFields,SIGNAL(triggered()), this,SLOT(showFieldChooser()));
	connect(ui.refreshButton,SIGNAL(pressed()),this,SLOT(refresh())); 
	connect(ui.itemSource,SIGNAL(currentIndexChanged(int)),this,SLOT(sourceChanged(int)));	
	connect(ui.diskList,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(doubleClickedDevGrid(const QModelIndex &)));	
	connect(ui.actionAbout,SIGNAL(triggered()),this,SLOT(showAbout()));	
	connect(ui.actionUserDefinedTabs,SIGNAL(triggered()),this,SLOT(showUserDefinedTabs()));
	connect(ui.visibleTabs,SIGNAL(triggered()),this,SLOT(visibleTabs()));
	connect(ui.mountButton,SIGNAL(pressed()),this,SLOT(handleMount()));
	connect(ui.shownotifications,SIGNAL(clicked()),this,SLOT(checkSetNotifications()));
	checkChange.start(1000);
	connect(&checkChange,SIGNAL(timeout()),this,SLOT(timeOutCheckChange()));
	connect(ui.deleteChangeMessage,SIGNAL(pressed()),this,SLOT(clearChangeMessage()));
	tabs[0]=ui.tabDisks;
	tabs[1]=ui.tabRaid;
	tabs[2]=ui.tabFstab;
	tabs[3]=ui.tabIscsi;
	tabs[4]=ui.tabStats;
	tabs[5]=ui.lvmInfo;
	tabsVisible[0]=nullptr;
	tabsVisible[1]=nullptr;
	tabsVisible[2]=nullptr;
	tabsVisible[3]=nullptr;
	tabsVisible[4]=nullptr;
	tabsVisible[5]=nullptr;	
	ui.pvInfo->sortByColumn(0,Qt::AscendingOrder);
	ui.vgList->sortByColumn(0,Qt::AscendingOrder);
	ui.lvList->sortByColumn(0,Qt::AscendingOrder);
	ui.stats->sortByColumn(0,Qt::AscendingOrder);
	ui.mtabList->sortByColumn(1,Qt::AscendingOrder);
	ui.iscsiTable->sortByColumn(0,Qt::AscendingOrder);
	ui.raidList->sortByColumn(0,Qt::AscendingOrder);
	setVisibleTabs();
	setupUserTabs();
	refresh();
	if(g_config.getExpandByDefault()){
		expandDeviceAll();
	}
	if(g_config.getShowNotifications()){
		ui.shownotifications->setCheckState(Qt::Checked);
	}
	 ui.lvmRootWarning->setVisible((getuid()!=0));
	 if(getuid()==0){
		ui.lvmetadNotRunning->setVisible(!TLVM::deamonRunning());
	 } else {
		 ui.lvmetadNotRunning->setVisible(false);
	 }
	
}

//Set which tab is visible from config 

void TMainWindow::setTabVisible(int p_indx,bool p_flag,const QString &p_label)
{
	if(p_flag){
		QWidget *l_tab=tabsVisible[p_indx];
		if(tabsVisible[p_indx] != nullptr){
			int l_cnt;
			int l_pos=0;
			for(l_cnt=0;l_cnt<5 && tabs[l_cnt]!= l_tab;l_cnt++){
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
	setTabVisible(5,g_config.getLVMTab(),i18n("LVM"));
}

/** Display dialog for selecting which tab is visible
 * 
 */

void TMainWindow::visibleTabs()
{
	TVisibleTabs l_dialog;
	l_dialog.exec();
	setVisibleTabs();
}


/**
  * Clear "change message" (Mounts/Unmounts/new device/remove etc..)
 */

void TMainWindow::clearChangeMessage()
{	
	notificationsModel->clear();
	ui.notifications->setVisible(false);
	changeManager.clear();
}

/**
 *  There is a "show notification" checkbox on the main window.
 *  When this is checked or unchecked, the changes is save to the configuration
 *  If the Notification is hidden, the list of changes is cleared.
 */
void TMainWindow::checkSetNotifications()
{	
	if(ui.shownotifications->checkState()==Qt::Checked){
		g_config.setShowNotification(true);
	} else {
		g_config.setShowNotification(false);
		clearChangeMessage();
	}
	g_config.sync();
}


/**
 * Check periodically  if there is any device change
 */

void TMainWindow::timeOutCheckChange()
{
	TLinkList<TChangeItem> *l_what;

	fillStats();
	if(refreshNext){
		if(ui.autoRefresh->isChecked()){
			refresh();
			refreshNext=false;
		}
	}

	if(g_config.getShowNotifications()){
		changeManager.getChanged(refreshNext);
		l_what=changeManager.getChanges();
		if(refreshNext){	
			TChangeItem *l_change;
			TLinkListIterator<TChangeItem> l_ci(l_what);
			int l_row=notificationsModel->rowCount();
			if(l_row==0){
				notificationsModel->setHorizontalHeaderItem(0,new QStandardItem(i18n("Date")));
				notificationsModel->setHorizontalHeaderItem(1,new QStandardItem(i18n("Device")));
				notificationsModel->setHorizontalHeaderItem(2,new QStandardItem(i18n("Change")));
			}
			while(l_ci.hasNext()){
				l_change=l_ci.next();		
				QList<QStandardItem *> l_list;
				l_list	<< new QStandardItem(l_change->getDate().toString(Qt::SystemLocaleLongDate))
					<< new QStandardItem(l_change->getDevice())
					<< new QStandardItem(l_change->getMessage());
				notificationsModel->insertRow(0,l_list);
				l_row++;
			}
			ui.notifications->setVisible(true);
			ui.notificationsList->resizeColumnsToContents();
			ui.notificationsList->resizeRowsToContents();		
		}
	}
}

TMainWindow::~TMainWindow()
{
	if(info)delete info;
	if(devModel) delete devModel;
	if(prvStats != nullptr) delete prvStats;
}

/**
 * When the about menu item is selected in the menu the about dialog is showen.
 */
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
