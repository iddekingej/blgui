#include "test_eval.h"
#include "formula/parser.h"
#include "../lib/moccreator.h"


void TTestEval::doRun()
{
	printf("Test eval begin\n");
	test1();
	test2();
	printf("Test eval end\n");
}


void TTestEval::test1()
{
	TParser l_parser("mounted != 'X'");
	TNode *l_formula=l_parser.parseFormula();
	if(l_formula==nullptr){
		fail("parseFormula returned null, error text is "+l_parser.getError());
		return;
	}
	TMocCreator l_creator;
	l_creator.addValue(TField::MOUNTED,"X");
	QVariant l_variant;	
	if(l_formula->calculate(&l_creator,l_variant)){
		fail("Test 1 failed with error "+l_creator.getError());
	}
	l_formula->print();
	expect("eval 1) X != 'X' ",QVariant(false),l_variant);
	l_creator.addValue(TField::MOUNTED,"");
	l_creator.resetError();
	if(l_formula->calculate(&l_creator,l_variant)){
		fail("Test 2 failed with error "+l_creator.getError());
	}
	expect("eval 1) '' != 'X' ",QVariant(true),l_variant);	
	delete l_formula;
}


void TTestEval::test2()
{
	TParser l_parser("type='sda1' and mounted != 'X'");
	TNode *l_formula=l_parser.parseFormula();
	if(l_formula==nullptr){
		fail("parseFormula returned null, error text is "+l_parser.getError());
		return;
	}
	TMocCreator l_creator;
	l_creator.addValue(TField::TYPE,"sda1");
	l_creator.addValue(TField::MOUNTED,"X");
	QVariant l_variant("SSS");	
	
	if(l_formula->calculate(&l_creator,l_variant)){
		fail("Test 1 failed with error "+l_creator.getError());
	}
	expect("eval 1) sda1=sda1 and X != 'X' ",QVariant(false),l_variant);
	
	l_creator.addValue(TField::MOUNTED,"");
	l_creator.resetError();
	if(l_formula->calculate(&l_creator,l_variant)){
		fail("Test 2 failed with error "+l_creator.getError());
	}
	l_variant="SS";
	expect("eval 1) sda1=sda1 and '' != 'X' ",QVariant(true),l_variant);	
	l_creator.addValue(TField::TYPE,"sdb1");
	l_creator.resetError();
	if(l_formula->calculate(&l_creator,l_variant)){
		fail("Test 2 failed with error "+l_creator.getError());
	}
	expect("eval 1) sdb1=sda1 and '' != 'X' ",QVariant(false),l_variant);	
	delete l_formula;

}
