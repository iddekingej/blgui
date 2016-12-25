#include "testclass.h"
#include <iostream>
#include "base/utils.h"

void TTestClass::error(const char * p_file,const char *p_method,const char* p_message)
{
	std::cout << p_file << ":" << p_method <<":" << p_message <<std::endl;
	failed=true;
}

void TTestClass::errorv(const char* p_file, const char* p_method, const char* p_message, const char *p_result)
{
	std::cout << p_file << ":" << p_method <<":" << p_message <<" returned:" << p_result <<std::endl;
	failed=true;

}

void TTestClass::errorv(const char* p_file, const char* p_method, const char* p_message, QString p_value)
{
	errorv(p_file,p_method,p_message,qstr(p_value));
}


void TTestClass::errorv(const char* p_file, const char* p_method, const char* p_message, long p_value)
{
	std::cout << p_file << ":" << p_method <<":" << p_message <<" returned:" << p_value <<std::endl;
}


bool TTestClass::run()
{

	doRun();	
	return failed;
}

void TTestClass::doRun(){
	error(__FILE__,__FUNCTION__,"Called TTestClass::doRun");
}
