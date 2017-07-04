#ifndef __NODE_H__
#define __NODE_H__

#include <QVariant>
#include "creator.h"
#include "scanner.h"
#include "base/linklist.h"
#include <iostream>

class TNode
{
public:
	virtual bool calculate(TCreator *p_creator,QVariant &p_result)=0;
	virtual ~TNode(){};
	virtual void print()=0;
};

class TFieldNode:public TNode
{
private:
	TField fieldId;
public:
	TFieldNode(TField p_fieldId);
	virtual bool calculate(TCreator *p_creator,QVariant &p_result) override;
	virtual void print() override;
};

template <typename T>
class TValueNode:public TNode
{
private:
	QVariant value;
public:
	TValueNode(T p_value){
		value=p_value;
	}
	virtual bool calculate(UNUSEDPAR TCreator *p_creator,QVariant &p_result) override{
		p_result=value;
		return false;
	}
	virtual void print() override{	
		std::cout << "VALUE NODE:" << qstr(value.toString()) << std::endl;
	}

};

class TDualOperatorNode:public TNode
{
private:
	TToken operatorType;
	TNode *left;
	TNode *right;
public:
	inline TToken getOperatorType(){ return operatorType;}
	virtual bool calculate(TCreator *p_creator,QVariant &p_result) override;
	TDualOperatorNode(TToken p_operatorType,TNode *p_left,TNode *p_right);
	virtual ~TDualOperatorNode();
	virtual void print() override;
};



#endif
