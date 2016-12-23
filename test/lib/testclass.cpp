#include "testclass.h"
#include <iostream>


void TTestClass::error(const char * p_file,const char *p_method,const char* p_message)
{
	std::cout << p_file << ":" << p_method <<":" << p_message <<std::endl;
	failed=true;
}


bool TTestClass::run()
{

	doRun();	
	return failed;
}

void TTestClass::doRun(){
	error(__FILE__,__FUNCTION__,"Called TTestClass::doRun");
}
