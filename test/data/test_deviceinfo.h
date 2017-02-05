#ifndef __TESTDATADEVICEINFO_H__
#define  __TESTDATADEVICEINFO_H__
#include "../../data/deviceinfo.h"
#include "../lib/testclass.h"

class  TTestDataDeviceInfo:public TTestClass
{	
	TDeviceInfo *deviceInfo;
public:
	TTestDataDeviceInfo();
	~TTestDataDeviceInfo();
	virtual void doRun() override;
	void test1() ;
};
#endif
