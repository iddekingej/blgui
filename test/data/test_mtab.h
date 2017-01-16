#ifndef  __TEST_DATA_MTAB_H__
#define __TEST_DATA_MTAB_H__

#include "../lib/testclass.h"
#include "../../data/mtab.h"

class TTestDataMTab:public TTestClass
{
private:
	TAlias      *alias;
	TDeviceList *deviceList;
	TMTab       *mtab;
protected:
	virtual void doRun() override;	
	void test1();
	void test2();
	void test3();
	void test4();
public:
	TTestDataMTab();
	virtual  ~TTestDataMTab();
	
};
#endif
