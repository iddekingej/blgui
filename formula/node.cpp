#include "node.h"
#include <iostream>
bool TFieldNode::calculate(TCreator* p_creator, QVariant& p_result)
{
	//TODO Check if fieldId is out of bounds
	if(p_creator->getFieldValue(fieldId,p_result)){
		p_creator->setError(QStringLiteral("Field Id=%1, not found").arg((int)fieldId));
		return true;
	}
	return false;
	
}

void TFieldNode::print()
{
	std::cout << "Field Id=" << (int)fieldId << std::endl;
}


TFieldNode::TFieldNode(TField p_fieldId)
{
	fieldId=p_fieldId;
}




TDualOperatorNode::TDualOperatorNode(TToken p_compareType, TNode* p_left, TNode* p_right)
{
	operatorType=p_compareType;
	left=p_left;
	right=p_right;
}

TDualOperatorNode::~TDualOperatorNode()
{
	delete left;
	delete right;
}


bool TDualOperatorNode::calculate(TCreator* p_creator, QVariant& p_result)
{
	QVariant l_left;
	QVariant l_right;

	if(left->calculate(p_creator,l_left)){
		return true;
	}
	if(right->calculate(p_creator,l_right)){
		return true;
	}
	
	//TODO compare types
	switch(operatorType){
		case TToken::COND_BIGGER:
			p_result=l_left > l_right;
			break;

		case TToken::COND_BE:
			p_result=l_left >= l_right;
			break;
		
		case TToken::COND_SMALLER:
			p_result=l_left < l_right;
			break;
			
		case TToken::COND_SE:
			p_result=l_left <= l_right;
			break;
			
		case TToken::COND_EQUAL:
			p_result=l_left == l_right;
			break;
		
		case TToken::COND_NE:
			p_result=l_left != l_right;
			break;
		case TToken::OP_AND:
			p_result= l_left.toBool() && l_right.toBool();
			break;
		case TToken::OP_OR:
			p_result= l_left.toBool() || l_right.toBool();
			break;
			
		default:
		//TODO Invalid compare compareType
			return true;
			
	}
	return false;
}

void TDualOperatorNode::print()
{
	std::cout << "BEGIN DUAL OPERATOR" <<std::endl;
	std::cout << "Operator id=" <<(int)operatorType <<std::endl;	
	if(left != nullptr){
		left->print(); 
	} else {
		std::cout <<"Null" <<std::endl;
	}
	if(right != nullptr){
		right->print();
	} else{
		std::cout << "Null" <<std::endl;
	}
	std::cout << "END DUAL OPERATOR";
}


