#ifndef __TESTCLASS_H_
#define __TESTCLASS_H_
class TTestClass{
private:
	bool failed=false;
public:
	void Error(const char *p_message);
	bool run();
	virtual void doRun();	
	virtual ~TTestClass(){};
};
#endif
