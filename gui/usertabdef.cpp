#include "usertabdef.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHash>
#include <QHashIterator>
#include <QList>
#include "data/devicebase.h"
#include "base/globals.h"
#include <klocalizedstring.h>
TUserTabDef::TUserTabDef(QWidget* p_parent):QWidget(p_parent)
{
	ui.setupUi(this);
	model=new QStandardItemModel(0,g_numDeviceFields+2,this);

	ui.dataView->setModel(model);	
}

/**
 *  The first column of the grid the allways the device name.
 *  The second field can be the partition name if the data set contain partition
 *  The rest of the column are user configured
 *  This method fills the user defined column names
 * 
 *  \param p_begin Start of user configured columns (can be 1 or 2)
 *  \param p_fields List of fields displayed int he grid. This Vevtor contains
 *                  field ids (@See g_deviceFields)
 */
void TUserTabDef::fillHeader(int p_begin,QVector<int> *p_fields){
	int l_fieldId;
	for(int l_cnt=0;l_cnt<p_fields->size();l_cnt++){
		l_fieldId=(*p_fields)[l_cnt];
		if(l_fieldId<g_numDeviceFields){
			model->setHorizontalHeaderItem(l_cnt+p_begin,new QStandardItem(QString(i18n(g_deviceFields[l_fieldId]))));
		}
	}
}

/**
 *  The first column of the grid the allways the device name.
 *  The second field can be the partition name if the data set contain partition 
 *  First the fixed set of data is added to the row
 *  Next the user selected columns are added to the displayRow
 * 
 *  \param p_fixedEnd  End  of the fixed column (and start of the user defined columns)
 *  \param p_begin     Start of the user defined data in p_list
 *  \param p_row       Row number
 *  \param p_enableFields Which fields must be displayed (contain field id's)
 *  \param p_list         A QStringList with device data (index is the fieldid)
 *  
 * 
 */
void TUserTabDef::displayRow(int p_fixedEnd,int p_begin,int p_row,QVector<int> *p_enabledFields ,const QStringList  &p_list)
{
	int l_fieldId;
	QStandardItem *l_item;
	int l_itemSize=p_list.count();	
//fill fixed columns 
	for(int l_cnt=0;l_cnt<p_fixedEnd;l_cnt++){
		l_item=new QStandardItem(p_list[l_cnt]);	
		model->setItem(p_row,l_cnt,l_item);
		
	}
	
//fill flexible columns
	for(int l_cnt=0;l_cnt<p_enabledFields->count();l_cnt++){
		l_fieldId=(*p_enabledFields)[l_cnt];		
		if(l_fieldId+p_begin<l_itemSize){
		    model->setItem(p_row,l_cnt+p_fixedEnd,new QStandardItem(p_list[l_fieldId+p_begin]));		
		}
	}
}

/**
 *  Fills the grid with information
 *  This routine scans through all the device data, filters the data and only displays
 *  the data that passes the filter
 * 
 *  \param p_def  Definition of the data
 *  \param p_info Information about all devices and partitions.
 */

void TUserTabDef::fillGrid(TTabDef* p_def, TDeviceInfo* p_info)
{
	no=p_def->getNo();
	model->clear();
	model->setHorizontalHeaderItem(0,new QStandardItem("Device"));
	if(p_def->getConditionObject()!=TT_Device){
		model->setHorizontalHeaderItem(1,new QStandardItem("Partition"));
	}
	int l_fixedEnd=2;
	if(p_def->getConditionObject()==TT_Device){
		l_fixedEnd=1;
	}	
	fillHeader(l_fixedEnd,p_def->getSelectedList());
	const QHash<QString,TDeviceBase*> *l_map=p_info->getDevices()->getNameIndex();
	QHashIterator<QString,TDeviceBase *> l_iter(*l_map);
	TDeviceBase *l_device;
	QStringList l_info;
	int l_conditionField=p_def->getConditionField();
	TConditionType l_conditionType=p_def->getConditionType();
	bool l_ok;
	QString l_value;
	int l_row=0;

	while(l_iter.hasNext()){
		l_iter.next();
		l_device=l_iter.value();
		
		if(p_def->getConditionObject()==TT_Device){
			if(dynamic_cast<TDevice *>(l_device)==nullptr) continue;
		}
		if(p_def->getConditionObject()==TT_Partition){
			if(dynamic_cast<TPartition *>(l_device)==nullptr) continue;
		}
		l_info.clear();
		l_device->fillDataRow(l_info);
		l_ok=true;
		if(l_conditionField>=0 && l_conditionField+2<l_info.length()){
			l_value=l_info[l_conditionField+2];	
			switch(l_conditionType){
				case CT_IsEmpty:l_ok=l_value.isEmpty();break;
				case CT_IsNotEmpty:l_ok=!l_value.isEmpty();break;
				case CT_IsValue:l_ok=(l_value==p_def->getConditionValue());break;
				case CT_NoCondition:l_ok=true;break;
			}
			
		}
		if(l_ok){
			displayRow(l_fixedEnd,2,l_row,p_def->getSelectedList(),l_info);
			l_row++;
		}
	}
	ui.dataView->resizeColumnsToContents();
	ui.dataView->resizeRowsToContents();
	ui.dataView->sortByColumn(0,Qt::AscendingOrder);

}

