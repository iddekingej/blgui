#ifndef __RUNNER_H_
#define __RUNNER_H_
#include "testclass.h"

class TRunner
{
private:
	bool failed=false;
public:
	bool run();
	void runner(TTestClass p_object);
	virtual void doRun()=0;
	virtual ~TRunner(){};
};
#endif
