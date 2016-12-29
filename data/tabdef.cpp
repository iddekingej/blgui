#include "tabdef.h"
#include "base/config.h"
#include "base/utils.h"
#include "base/doublelinkedlist.h"
#include <QMap>
#include <QVariant>
#include <QList>
#include <QListIterator>
#include <sys/time.h>

TTabDef::TTabDef(const QString &p_name)
{
	name=p_name;
	conditionObject=TT_Device;
	conditionType=CT_Empty;
	conditionField=-1;
	conditionValue="";
	isActive=true;
	struct timeval l_time;
	gettimeofday(&l_time,nullptr);
	no=((unsigned long)l_time.tv_sec)*1000000+l_time.tv_usec;
}


TTabDef::TTabDef(QVariant& p_json)
{
	QMap<QString,QVariant> l_map=p_json.toMap();
	
	name=l_map["name"].toString();
	int l_co=l_map["conditionObject"].toInt();
	conditionObject=(l_co==TT_Device)?TT_Device:TT_Partition;
	conditionType=(TConditionType)(l_map["conditionType"].toInt());
	conditionValue=l_map["conditionValue"].toString();	
	conditionField=l_map["conditionField"].toInt();
	if(l_map.contains("isactive")){
		isActive=l_map["isactive"].toBool();
	} else {		
		isActive=true;		
	}
	if(l_map.contains("no")){
		no=l_map["no"].toInt();
	} else {
		no=-1;
	}
	QList<QVariant> l_fields=l_map["selectedFields"].toList();
	for(int l_cnt=0;l_cnt<l_fields.size();l_cnt++){
		selectedList.append(l_fields[l_cnt].toInt());
	}
}


void TTabDef::addSelectedList(int p_field)
{
	selectedList.push_back(p_field);
}


void TTabDef::toJson(QList<QVariant>& p_document)
{
	QMap<QString,QVariant> l_object;
	l_object["name"]=QVariant(name);
	l_object["conditionObject"]=QVariant(conditionObject);
	l_object["conditionType"]=QVariant(conditionType);
	l_object["conditionValue"]=QVariant(conditionValue);
	l_object["conditionField"]=QVariant(conditionField);
	l_object["isactive"]=QVariant(isActive);
	l_object["no"]=QVariant((unsigned long long)no);
	QList<QVariant> l_arr;
	for(int l_field:selectedList){
		l_arr.push_back(QVariant(l_field));
	}
	l_object["selectedFields"]=QVariant(l_arr);
	p_document.push_back(l_object);
}


//TODO: Exception when already exists
TTabDef * TTabDefList::createTabDef(const QString& p_name)
{
	TTabDef *l_item=new TTabDef(p_name);
	append(l_item);
	return l_item;
}
/**
 * Get tabdef information by name.
 * Note: Name should be unique
 * Parameter:
 * \param p_name   Name of tab to find.
 * \return         Return tab with name  or nullptr when no tab found with this name
 */
TTabDef * TTabDefList::getByName(QString& p_name)
{
	TDoubleLinkedListIterator<TTabDef> l_iter(this);
	TTabDef *l_item;
	while(l_iter.hasNext()){
		l_item=l_iter.next();
		if(l_item->getName()==p_name) return l_item;	
	}
	return nullptr;
}


TDoubleLinkedListItem<TTabDef> *TTabDefList::getByNo(int p_no)
{
	TDoubleLinkedListItem<TTabDef> *l_item=this->getStart();
	while(l_item != nullptr){				
		if(l_item->getItem()->getNo() == p_no) return l_item;
		l_item=l_item->getNext();
	}
	return nullptr;
}

TDoubleLinkedListItem<TTabDef>* TTabDefList::getByPosition(int p_pos)
{
	int l_pos=0;
	TDoubleLinkedListItem<TTabDef> *l_item=this->getStart();
	while(l_item != nullptr){				
		if(l_pos==p_pos) return l_item;
		l_pos++;
		l_item=l_item->getNext();
	}
	return nullptr;
}

void TTabDefList::read()
{
	QVariant l_data;
	QVariant l_value;
	g_config.getTabDef(l_data);
	QList<QVariant> l_list=l_data.toList();
	QListIterator<QVariant> l_iter(l_list);
	int l_no=0;
	while(l_iter.hasNext()){
		l_value=l_iter.next();
		TTabDef *l_def=new TTabDef(l_value);
		if(l_def->getNo()==-1)l_def->setNo(l_no);
		append(l_def);
		l_no++;
	}
	
}

void TTabDefList::save()
{
	QList<QVariant> l_data;
	TDoubleLinkedListIterator<TTabDef> l_iter(this);	
	while(l_iter.hasNext()){
		l_iter.next()->toJson(l_data);		
	}
	QVariant l_value(l_data);
	g_config.setTabDef(l_value);
	g_config.sync();
}


