#include "tabdef.h"
#include <QJsonArray>
#include <QJsonObject>
#include "base/config.h"
#include <QJsonValueRef>
#include "base/utils.h"
TTabDef::TTabDef(const QString &p_name)
{
	name=p_name;
}


TTabDef::TTabDef(QJsonObject& p_json)
{
	name=p_json["name"].toString();
	int l_co=p_json["conditionObject"].toInt();
	conditionObject=(l_co==TT_Device)?TT_Device:TT_Partition;
	conditionType=(TConditionType)(p_json["conditionType"].toInt());
	conditionValue=p_json["conditionValue"].toString();	
	conditionField=p_json["conditionField"].toInt();
}


void TTabDef::addSelectedList(int p_field)
{
	selectedList.push_back(p_field);
}


void TTabDef::toJson(QJsonArray& p_document)
{
	QJsonObject l_object;
	l_object["name"]=name;
	l_object["conditionObject"]=conditionObject;
	l_object["conditionType"]=conditionType;
	l_object["conditionValue"]=conditionValue;
	l_object["conditionField"]=conditionField;
	p_document.push_back(l_object);
}


//TODO: Exception when allready exists
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
	TLinkListIterator<TTabDef> l_iter(this);
	TTabDef *l_item;
	while(l_iter.hasNext()){
		l_item=l_iter.next();
		if(l_item->getName()==p_name) return l_item;	
	}
	return nullptr;
}

TTabDef* TTabDefList::getByPosition(int p_pos)
{
	TLinkListIterator<TTabDef> l_iter(this);
	int l_pos=0;
	TTabDef *l_item;
	while(l_iter.hasNext()){		
		l_item=l_iter.next();
		if(l_pos==p_pos) return l_item;
		l_pos++;
	}
	return nullptr;
}

void TTabDefList::read()
{
	QJsonArray l_data;
	g_config.getTabDef(l_data);
	QJsonObject l_object;	
	for(int l_cnt=0;l_cnt<l_data.size();l_cnt++){
		QJsonValue l_value=l_data[l_cnt];
		if(l_value.isObject()){			
			l_object=l_value.toObject();
			TTabDef *l_def=new TTabDef(l_object);
			append(l_def);
		} else {
			printf("Not an object \n");
		}
	}
	
}

void TTabDefList::save()
{
	QJsonArray l_data;
	TLinkListIterator<TTabDef> l_iter(this);	
	while(l_iter.hasNext()){
		l_iter.next()->toJson(l_data);		
	}
	g_config.setTabDef(l_data);
	g_config.sync();
}


