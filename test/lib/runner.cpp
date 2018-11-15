#include "runner.h"
#include <iostream>
bool TRunner::run()
{
	std::cout << "Run " <<__FUNCTION__ <<std::endl;
	doRun();	
	std::cout << "Run " <<__FUNCTION__ << " Failed:" << failed <<std::endl;
	return failed;
}

TRunner::TRunner(TTestConfig* p_config)
{
	config=p_config;
}


void TRunner::runner(TTestClass *p_object)
{	
	p_object->setConfig(config);
	if(p_object->run()) failed=true;	
	delete p_object;
}

