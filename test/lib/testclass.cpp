#include "testclass.h"
#include <iostream>
void TTestClass::Error(const char* p_message)
{
	std::cout << __FILE__ << ":" << p_message;
	failed=true;
}


bool TTestClass::run()
{
	doRun();
	return failed;
}

void TTestClass::doRun(){
	
}
