/**
 *  Definition about user defined tabes 
 */
#ifndef __TABDEF_H_
#define __TABDEF_H_
#include <QString>
#include <QVector>
#include "qjsonwrapper/Json.h"

#include "../base/doublelinkedlist.h"
/**
 * Type of device displayed in Grid
 * TT_Device - only devices
 * TT_Partition - only oartitions
 * TT_Both - partition and decvices
 */
typedef enum{
	TT_Device=0
,	TT_Partition=1
,	TT_Both=2
} TObjectType;

/**
 * It is possible to define a simple filter.
 * curently only a single condition can be defined:
 *  
 * CT_IsEmpty  - display device when selected field has a empty value
 * CT_IsNotEmpty - When selected field has a non empty value
 * CT_IsValue    - Needs a value.  Information about device/parition is only displayed
 *                 when a selected field has a certain value
 * CT_NoCondition - There is no filter
 */
typedef enum{
	CT_IsEmpty=0
,	CT_IsNotEmpty=1
,	CT_IsValue=2
,       CT_NoCondition=-1
} TConditionType;

/**
 * A object of this class contains de definition of a user defined tab
 */

class TTabDef{
private:
/**
 * Name of tab. This name is also display on the tab
 */
	QString        name;
/**
 * ID of field used for filtering data
 * Field id is the index of base/globals/g_deviceFields
 */	
	int            conditionField;
/**
 * What type of object (Device or parition) to display in list 
 * @see TObjectType
 */
	TObjectType    conditionObject;
/**
 * Condition used in filter
 * @see TConditionType
 */
	TConditionType conditionType;
/**
 * Value used in filter
 * Value is only used  if conditionType==CT_IsValues
 */
	QString        conditionValue;
/**
 * List fields displayed om grod
 * The vector contains field id's
 * Field id's is index  of base/globals/g_deviceFields
 */
	QVector<int>   selectedList;
/**
 * Indicates if the tab is active
 * true - tab is displayed in main window
 * false -tab is not displayed in main window
 */
	bool           isActive;
/**
 * Unique ID of the tab
 */
	long           no=-1;
public:
	inline void setName(const QString &p_name){name=p_name;}
	inline QString &getName(){ return name;}
	inline int getConditionField(){ return conditionField;}
	inline void setConditionField(int p_conditionField){ conditionField=p_conditionField;}
	inline TObjectType getConditionObject(){ return conditionObject;}
	inline void setConditionObject(TObjectType p_conditionObject){ conditionObject=p_conditionObject;}
	inline TConditionType getConditionType(){ return conditionType;}
	inline void setConditionType(TConditionType p_conditionType){ conditionType=p_conditionType;}
	inline QString &getConditionValue(){ return conditionValue;}
	inline void setConditionValue(QString p_value){ conditionValue=p_value;}
	inline QVector<int> *getSelectedList(){ return &selectedList;};
	inline bool getIsActive(){ return isActive;}
	inline void setIsActive(bool p_isActive){ isActive=p_isActive;}
	inline long getNo(){ return no;}
	inline void setNo(long p_no){ no=p_no;}
	void toJson(QList<QVariant> &p_variant);
	TTabDef(QVariant &p_json);
	void addSelectedList(int p_field);
	inline bool hasFieldInSelected(int p_field){ return selectedList.indexOf(p_field) != -1;}
	
	TTabDef(const QString &p_name);
	
};

/**
 * List of all defined user tabs
 */
class TTabDefList:public TDoubleLinkedList<TTabDef>{
public:
	TTabDef *createTabDef(const QString &p_name);
	TTabDef *getByName(QString &p_name);
	TDoubleLinkedListItem<TTabDef> *getByPosition(long p_pos);
	TDoubleLinkedListItem<TTabDef> *getByNo(long p_no);
	void save();
	void read();
};

#endif
