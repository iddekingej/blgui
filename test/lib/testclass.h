#ifndef __TESTCLASS_H_
#define __TESTCLASS_H_
#include <iostream>
#include "testconfig.h"
#define fail(p_message) error(__FILE__,__FUNCTION__,p_message)


class TTestClass{
private:
	bool failed=false;
	TTestConfig *config;
protected:
	virtual void doRun();	
public:
	inline void setConfig(TTestConfig *p_config){ config=p_config;}
	inline TTestConfig *getConfig(){ return config;}
	inline bool getFailed(){ return failed;};
	void error(const char *p_file,const char *p_method,const char *p_message);
	bool run();
	virtual ~TTestClass(){};
};
#endif
