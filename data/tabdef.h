#ifndef __TABDEF_H_
#define __TABDEF_H_
#include <QString>
#include <QLinkedList>

typedef enum{
	TT_Device=0
,	TT_Partition=1
} TObjectType;

typedef enum{
	CT_IsEmpty=0
,	CT_IsNotEmpty=1
,	CT_IsValue=2
} TConditionType;

class TTabDef{
private:
	QString       name;
	int           conditionField;
	TObjectType   conditionObject;
	TConditionType conditionType;
	QString       conditionValue;
	QLinkedList<int> selectedList;
public:
	inline void setName(QString &p_name){name=p_name;}
	inline QString &getName(){ return name;}
	inline int getConditionField(){ return conditionField;}
	inline void setConditionField(int p_conditionField){ conditionField=p_conditionField;}
	inline TObjectType getConditionObject(){ return conditionObject;}
	inline void setConditionObject(TObjectType p_conditionObject){ conditionObject=p_conditionObject;}
	inline TConditionType getConditionType(){ return conditionType;}
	inline void setConditionType(TConditionType p_conditionType){ conditionType=p_conditionType;}
	inline QString &getConditionValue(){ return conditionValue;}
	void addSelectedList(int p_field);
	TTabDef();
};

#endif
