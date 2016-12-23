#ifndef __RUNNER_H_
#define __RUNNER_H_
#include "testclass.h"

class TRunner
{
private:
	bool failed=false;
protected:
	virtual void doRun()=0;
public:
	bool run();
	void runner(TTestClass *p_object);
	virtual ~TRunner(){};
};
#endif
