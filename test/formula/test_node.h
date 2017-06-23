#ifndef __TEST_NODE_H_
#define __TEST_NODE_H_
#include "../lib/testclass.h"

class TTestNode:public TTestClass
{
private:
	void test1();
	void test2();
	void test3();
protected:
	virtual void doRun() override;

	
};

#endif
