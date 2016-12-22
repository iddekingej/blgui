#include "runner.h"

bool TRunner::run()
{
	doRun();
	return failed;
}

void TRunner::runner(TTestClass p_object)
{
	if(p_object.run()) failed=true;
}

