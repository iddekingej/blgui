#include "test_parser.h"
#include "../lib/mocparser.h"
#include "formula/scanner.h"
void TTestParser::doRun()
{
	test1();
	test2();
}
	

void TTestParser::test1()
{
	TMOCParser l_parser("mounted");
	TField l_code=l_parser.getFieldIdByName("mounted");
	expect("Field ID 'mounted'",(int)TField::MOUNTED,(int)l_code);

}

void TTestParser::test2()
{
	
	TMOCParser l_parser("mounted='1' and device_name='sda'");
	TNode *l_node=l_parser.parseFormula();
	expect("Parser error",QString(),l_parser.getError());
	TDualOperatorNode *l_dual=dynamic_cast<TDualOperatorNode *>(l_node);
	if(l_dual==nullptr){
		fail("Top node is not a dual operator");
	} else {
		expect("Top node",(int) TToken::OP_AND,(int) l_dual->getOperatorType());
	}
	delete l_node;
}

void TTestParser::test3()
{
	TMOCParser l_parser("mounted='1' and device_name='sda'");
	l_parser.getScanner()->nextToken();
	
}
