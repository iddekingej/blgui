#include "run_base.h"
#include "test01.h"

class TRunBaseRunner:public TRunner
{
protected:
	virtual void doRun()
	{
		runner(new TTest01());
	}
};

bool run_base()
{

	TRunBaseRunner l_run;
	return l_run.run();
}

