#include "test_devicelist.h"
#include <iostream>

TTestDataDeviceList::TTestDataDeviceList()
{
	alias=new TAlias();
	deviceList=new TDeviceList(alias);
}

TTestDataDeviceList::~TTestDataDeviceList()
{
	delete alias;
	delete deviceList;
}

void TTestDataDeviceList::test1()
{
	deviceList->readInfo();
}

void TTestDataDeviceList::doRun()
{
	std::cout << "data/test_devicelist begin" << std::endl;
	test1();
	std::cout << "data/test_devicelist end" << std::endl;
}

