#ifndef __TEST01_H_
#define __TEST01_H_
#include "../lib/testclass.h"
#include "../../base/linklist.h"
class TTest01:public TTestClass
{
public:
	void test01();
	virtual void doRun();	
	TTest01();
	virtual ~TTest01();
};

#endif
