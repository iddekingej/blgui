#include "run_base.h"
#include "test01.h"

class TRunBaseRunner:public TRunner
{
	void doRun()
	{
		runner(TTest01());
	}
};

bool run_base()
{
	TRunBaseRunner l_run;
	return l_run.run();
}

