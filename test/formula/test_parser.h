#ifndef __TEST_PARSER_H__
#define __TEST_PARSER_H__

#include "../lib/testclass.h"

class TTestParser:public TTestClass
{
private:
	void test1();
	void test2();
	void test3();
protected:
	virtual void doRun() override;
};
#endif
