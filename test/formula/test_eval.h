#ifndef __TEST_EVAL_H_
#define __TEST_EVAL_H_
#include "../lib/testclass.h"

class TTestEval:public TTestClass
{
private:
	void test1();
	void test2();
protected:
	virtual void doRun() override;		
public:
	
	TTestEval():TTestClass(){};
	virtual ~TTestEval(){};
};
#endif
