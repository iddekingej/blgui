#include "tabdef.h"
#include "base/config.h"
#include "base/utils.h"
#include "base/doublelinkedlist.h"
#include <QMap>
#include <QVariant>
#include <QList>
#include <QListIterator>
#include <sys/time.h>
#include "formula/parser.h"
#include "data/device.h"
#include "data/partition.h"
#include "formula/node.h"
/**
 * Initialize default definition of a tab
 * 
 * \param p_name Name of tab, this also used a title.
 */
TTabDef::TTabDef(const QString &p_name)
{
	name=p_name;
	conditionObject=TObjectType::Device;
	conditionType=TConditionType::NoCondition;
	conditionField=-1;
	conditionValue="";
	isActive=true;
	struct timeval l_time;
	gettimeofday(&l_time,nullptr);
/**
 *Unique ID is current time in usec
 */
	no=((unsigned long)l_time.tv_sec)*1000000+l_time.tv_usec;
}


bool TTabDef::validateCondition(QString &p_error)
{
	if(useExtendedCondition){
		TNode *l_node=getParsedExtendedCondition();
		if(l_node==nullptr){
			p_error=parseError;
			return true;
		}
	}
	p_error="";
	return false;
}


bool TTabDef::checkCondition(TDeviceBase* p_device)
{
		if(conditionObject ==TObjectType::Device){
			if(dynamic_cast<TDevice *>(p_device)==nullptr){
				return false;
			};
		}
		if(conditionObject==TObjectType::Partition){
			if(dynamic_cast<TPartition *>(p_device)==nullptr){
				return false;
			};
		}
		
		bool l_ok=true;
		
		if(useExtendedCondition){
			TNode *l_extendedCondition=getParsedExtendedCondition();
			if(l_extendedCondition != nullptr){
				TDeviceCreator l_creator(p_device);
				QVariant l_check;
				if(l_extendedCondition->calculate(&l_creator,l_check)){
					std::cout << "Error :" << qstr(l_creator.getError()) << std::endl;
				}
				l_ok=l_check.toBool();				
			}
		} else if(conditionField>=0){
			QString l_value;
			p_device->fillDataRow((TField)conditionField,l_value); //TODO TFIELD
			
			switch(conditionType){
				case TConditionType::IsEmpty:l_ok=l_value.isEmpty();break;
				case TConditionType::IsNotEmpty:l_ok=!l_value.isEmpty();break;
				case TConditionType::IsValue:l_ok=(l_value==conditionValue);break;
				case TConditionType::NoCondition:l_ok=true;break;
			}
			
		}
		return l_ok;
}



/**
 * This constructor is used when readign the definition from the configuration
 * The definition is  stored as json.
 * The json is parsed to a qvariant.
 * 
 * \param p_json Definition of tab read from configuration
 */
TTabDef::TTabDef(QVariant& p_json)
{
	QMap<QString,QVariant> l_map=p_json.toMap();
	
	name=l_map["name"].toString();
	TObjectType l_co=(TObjectType)(l_map["conditionObject"].toInt());
	conditionObject=(l_co==TObjectType::Device)?TObjectType::Device :TObjectType::Partition;
	conditionType=static_cast<TConditionType>(l_map["conditionType"].toInt());
	conditionValue=l_map["conditionValue"].toString();	
	conditionField=l_map["conditionField"].toInt();
	if(l_map.contains("tabType")){
		tabType=static_cast<TTabType>(l_map["tabType"].toInt());
	} else {
		tabType=TTabType::disks;
	}
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
	if(l_map.contains("useExtendedCondition")){
		useExtendedCondition=l_map["useExtendedCondition"].toBool();
	} else {
		useExtendedCondition=false;
	}
	if(l_map.contains("extendedCondition")){
		extendedCondition=l_map["extendedCondition"].toString();
	} else {
		extendedCondition = "";
	}
	QList<QVariant> l_fields=l_map["selectedFields"].toList();
	for(int l_cnt=0;l_cnt<l_fields.size();l_cnt++){
		selectedList.append(l_fields[l_cnt].toInt());
	}
}

TTabDef::~TTabDef()
{
	if(parsedExtendedCondition != nullptr ) {
		delete parsedExtendedCondition;
	}
}


TNode * TTabDef::getParsedExtendedCondition()
{
	if(parsedExtendedCondition == nullptr){
		TParser l_parser(extendedCondition);
		parsedExtendedCondition= l_parser.parseFormula();
		l_parser.getFullError(parseError);
	}
	return parsedExtendedCondition;
}



/**
 * selectedList is a list of field that are displayed in the grid
 * The method adds a field to the list.
 * 
 * \param p_field  Field id.
 */

void TTabDef::addSelectedList(int p_field)
{
	selectedList.push_back(p_field);
}

/**
 *  Convert te definition to a QVariant. This data is later written as json to the 
 *  configuration file
 * 
 * \param p_document out param:List of QVariant contain the definition of this tabdef
 */

void TTabDef::toJson(QList<QVariant>& p_document)
{
	QMap<QString,QVariant> l_object;
	l_object["name"]=QVariant(name);
	l_object["conditionObject"]=QVariant((int)conditionObject);
	l_object["conditionType"]=QVariant(static_cast<int>(conditionType));
	l_object["conditionValue"]=QVariant(conditionValue);
	l_object["conditionField"]=QVariant(conditionField);
	l_object["isactive"]=QVariant(isActive);
	l_object["no"]=QVariant((unsigned long long)no);
	l_object["useExtendedCondition"]=QVariant(useExtendedCondition);
	l_object["extendedCondition"]=QVariant(extendedCondition);
	l_object["tabType"]=QVariant(static_cast<int>(tabType));
	QList<QVariant> l_arr;
	for(int l_field:selectedList){
		l_arr.push_back(QVariant(l_field));
	}
	l_object["selectedFields"]=QVariant(l_arr);
	p_document.push_back(l_object);
}

/**
 *  Create new tab def and add this to the list
 * 
 *  \param p_name  Name/title of new tab def 
 *  \return  New tab def object
 */

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

/**
 * Get tab def by unique ID
 * 
 * \param p_no unique ID 
 * \return tab def with unique ID=p_no or null when not found
 */

TDoubleLinkedListItem<TTabDef> *TTabDefList::getByNo(long p_no)
{
	TDoubleLinkedListItem<TTabDef> *l_item=this->getStart();
	while(l_item != nullptr){				
		if(l_item->getItem()->getNo() == p_no) return l_item;
		l_item=l_item->getNext();
	}
	return nullptr;
}

/**
 *  Get tab def  by position in list
 *  
 * \param p_pos  position
 * \return tab def at position or null when not found
 */

TDoubleLinkedListItem<TTabDef>* TTabDefList::getByPosition(long p_pos)
{
	long l_pos=0;
	TDoubleLinkedListItem<TTabDef> *l_item=this->getStart();
	while(l_item != nullptr){				
		if(l_pos==p_pos) return l_item;
		l_pos++;
		l_item=l_item->getNext();
	}
	return nullptr;
}


/**
 * Read tab defs from configuration
 * g_config.getTab def read json from 
 */
void TTabDefList::read(TConfig &p_config)
{
	QVariant l_data;
	QVariant l_value;
	p_config.getTabDef(l_data);
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

/**
 * Save tab def in configuration file.
 * The definition is covnerted to a variant.
 * In g_config the variant is saved as json.
 */
void TTabDefList::save(TConfig &p_config)
{
	QList<QVariant> l_data;
	TDoubleLinkedListIterator<TTabDef> l_iter(this);	
	while(l_iter.hasNext()){
		l_iter.next()->toJson(l_data);		
	}
	QVariant l_value(l_data);
	p_config.setTabDef(l_value);
	p_config.sync();
}



