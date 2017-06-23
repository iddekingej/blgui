#ifndef __TESTDATADEVICEINFO_H__
#define  __TESTDATADEVICEINFO_H__
#include "../../data/deviceinfo.h"
#include "../lib/testclass.h"
/**
 * Check the whold data read
 */
class  TTestDataDeviceInfo:public TTestClass
{	
	/**
	 * TDeviceInfo object to test
	 */
	TDeviceInfo *deviceInfo;
protected:
	virtual void setup() override;
	virtual void doRun() override;
public:
	~TTestDataDeviceInfo();
	
	void test1();
	void test2();
};
#endif
