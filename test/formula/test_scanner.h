#ifndef __TEST_TESTSCANNER_H__
#define __TEST_TESTSCANNER_H__

#include "../lib/testclass.h"

class TTestScanner:public TTestClass
{
private:
	void test1();
	void test2();
protected:
	virtual void doRun() override;	
public:
	TTestScanner();
	virtual ~TTestScanner();
};


#endif
