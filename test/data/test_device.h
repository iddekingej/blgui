#ifndef __TEST_DEVICE_H_
#define __TEST_DEVICE_H_

#include "../lib/testclass.h"
#include "../../data/device.h"
class TTestDevice:public TTestClass
{
private:
	TDevice *device;
protected:
	void doRun();	
	void test1();
	void test2();
public:		
	TTestDevice();
	virtual ~TTestDevice();
};
#endif
