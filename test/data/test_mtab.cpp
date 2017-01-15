#include "test_mtab.h"
#include  <iostream>


TTestDataMTab::TTestDataMTab()
{
	alias=createAliasList();
	deviceList=createDeviceList(alias);
	mtab=new TMTab(deviceList);
	mtab->setSourceFile(getFilePath("data/test_mtab1"));
}

TTestDataMTab::~TTestDataMTab()
{
	if(alias != nullptr) delete alias;
	if(deviceList != nullptr) delete deviceList;
	if(mtab != nullptr)delete mtab;
}

void TTestDataMTab::doRun()
{
	std::cout << "data/mtab test begin" <<std::endl;
	test1();
	if(!getFailed()){
		test2();		
		test3();
	}
	std::cout << "data/mtab test end" <<std::endl;
}

void TTestDataMTab::test1()
{
	if(!mtab->processInfo()){
		fail("Error reading file");
	}
}

void  TTestDataMTab::test2()
{
	long l_le=mtab->getEntries()->getLength();
	expect("Number of entries read from test mtab",4,l_le);
}

void TTestDataMTab::test3()
{
	if(!mtab->hasMount("/dev/sda1","/mnt/home/")){
		fail("hasMount on sda1 and /mnt/home should return true");
	}
	if(mtab->hasMount("/dev/sda1","/mnt/homex/")){
		fail("hasMount on sda1 and /mnt/homex should return false");
	}
	if(mtab->hasMount("x","y")){
		fail("hasMount on 'x' and 'y' should return false");
	}
}
