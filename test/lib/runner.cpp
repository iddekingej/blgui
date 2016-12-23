#include "runner.h"
#include <iostream>
bool TRunner::run()
{
	
	doRun();	
	return failed;
}

void TRunner::runner(TTestClass *p_object)
{
	if(p_object->run()) failed=true;
	delete p_object;
}

