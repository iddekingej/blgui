#include "usertabdef.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHash>
#include <QHashIterator>
#include <QList>
#include "data/devicebase.h"
#include "base/globals.h"
TUserTabDef::TUserTabDef(QWidget* p_parent):QWidget(p_parent)
{
	ui.setupUi(this);
	model=new QStandardItemModel(0,g_numDeviceFields+2);

	ui.dataView->setModel(model);	
}

void TUserTabDef::fillGrid(TTabDef* p_def, TDeviceInfo* p_info)
{
	model->clear();
	model->setHorizontalHeaderItem(0,new QStandardItem("Device"));
	model->setHorizontalHeaderItem(1,new QStandardItem("Partition"));
	for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
		model->setHorizontalHeaderItem(2+l_cnt,new QStandardItem(g_deviceFields[l_cnt]));
	}	
	const QHash<QString,TDeviceBase*> *l_map=p_info->getDevices()->getNameIndex();
	QHashIterator<QString,TDeviceBase *> l_iter(*l_map);
	TDeviceBase *l_device;
	QStringList l_info;
	int l_conditionField=p_def->getConditionField();
	TConditionType l_conditionType=p_def->getConditionType();
	bool l_ok;
	QString l_value;
	
	while(l_iter.hasNext()){
		l_iter.next();
		l_device=l_iter.value();
		l_info.clear();
		l_device->fillDataRow(l_info);
		l_ok=true;
		if(l_conditionField>=0 && l_conditionField+2<l_info.length()){
			l_value=l_info[l_conditionField+2];	
			switch(l_conditionType){
				case CT_IsEmpty:l_ok=l_value.isEmpty();break;
				case CT_IsNotEmpty:l_ok=!l_value.isEmpty();break;
				case CT_IsValue:l_ok=(l_value==p_def->getConditionValue());break;
			}
			
		}
		if(l_ok){
			
			QList<QStandardItem *>l_list;
			l_list << new QStandardItem(l_info[0]);
			l_list << new QStandardItem(l_info[1]);
			for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
				l_list << new QStandardItem(l_info[l_cnt+2]);
			}
			model->appendRow(l_list);
		}
	}
}

