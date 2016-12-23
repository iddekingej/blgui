#include "test01.h"
#include "../lib/testclass.h"

void TTest01::doRun()
{
	test01();
	if(getFailed()) return;
	test02();
}

void TTest01::test01()
{
	if(list->getStart() != nullptr) fail(" getStart is not null");
	if(list->getLength() != 0) fail(" Length !=0");
}


void TTest01::test02()
{
	list->append(new TTestItem(1));
	if(list->getStart()==nullptr) {
		fail(" GetStart is null after append");
		return;
	}
	if(list->getLength()!= 1){
		fail(" length != 1 after append");
		return;
	}
	if(list->getStart()->getItem()->getSomeValue()!=1){
		fail(" GetSomeValue !=1");
		return;
	}
}

TTest01::~TTest01()
{
	delete list;
}

TTest01::TTest01()
{	
	list=new TLinkList<TTestItem>();
}

