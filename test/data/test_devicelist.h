#ifndef _DATA_TEST_DEVICELIST_H_
#define _DATA_TEST_DEVICELIST_H_
#include "../lib/testclass.h"
#include "../../data/mtab.h"
#include "../../data/devicelist.h"

class TTestDataDeviceList:public TTestClass
{
	TAlias *alias;
	TDeviceList *deviceList;
protected:
	virtual void doRun() override;
	virtual void setup() override;
	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
public:
	~TTestDataDeviceList();
};

#endif
