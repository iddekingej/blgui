#include "test_node.h"
#include "../lib/moccreator.h"
#include "formula/node.h"
#include "formula/scanner.h"
void TTestNode::doRun()
{
	test1();
	test2();
	test3();
}

void TTestNode::test1()
{
	TFieldNode *l_field=new TFieldNode(TField::MOUNTED);
	TValueNode<QString> *l_value=new TValueNode<QString>("bla");	
	TDualOperatorNode l_node(TToken::COND_EQUAL,l_field,l_value);
	TMocCreator l_creator;
	l_creator.addValue(TField::MOUNTED, "bla");
	QVariant l_result;
	l_node.calculate(&l_creator,l_result);
	expect("Equal test bla=bla",QVariant(true),l_result);
	l_creator.addValue(TField::MOUNTED, "bla2");
	expect("Equal test bla=bla2",QVariant(true),l_result);
	l_node.calculate(&l_creator,l_result);
	expect("Equal test bla=bla2",QVariant(false),l_result);

}


void TTestNode::test2()
{
	TValueNode<bool> *l_value1=new TValueNode<bool>(true);
	TValueNode<bool> *l_value2=new TValueNode<bool>(true);		
	TDualOperatorNode l_node(TToken::OP_AND ,l_value1,l_value2);
	TMocCreator l_creator;
	QVariant l_result;
	l_node.calculate(&l_creator,l_result);
	expect("true and true",QVariant(true),l_result);
}

void TTestNode::test3()
{
	TValueNode<bool> *l_value1=new TValueNode<bool>(true);
	TValueNode<bool> *l_value2=new TValueNode<bool>(false);		
	TDualOperatorNode l_node(TToken::OP_AND ,l_value1,l_value2);
	TMocCreator l_creator;
	QVariant l_result;
	l_node.calculate(&l_creator,l_result);
	expect("true and false",QVariant(false),l_result);
}
