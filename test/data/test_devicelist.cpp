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

void TTestDataDeviceList::test2()
{
	delete deviceList;
	deviceList=new TDeviceList(alias);
	deviceList->setSysBlockPath(getConfig()->getFilePath("/sys/block/"));
	deviceList->readInfo();
}	

void TTestDataDeviceList::test3()
{	
	expect("Number of devices read from test /sys/block",3,deviceList->getLength());
	TLinkListItem<TDevice> *l_item=deviceList->getStart();
	if(l_item==nullptr){
		fail("Except first item != nullptr");
	} else {
		expect("Device 1 name ","sda",l_item->getItem()->getName());
		expect("Size of device 1",3202400*512,(long)l_item->getItem()->getSize());
		l_item=l_item->getNext();
		if(l_item==nullptr){
			fail("Expected second item != nullptr");
		} else {
			expect("Device 2 name","sdb",l_item->getItem()->getName());
			expect("Model of dev 2","bla bla",l_item->getItem()->getModel());
		}
	}
}


void TTestDataDeviceList::doRun()
{
	std::cout << "data/test_devicelist begin" << std::endl;
	test1();
	test2();
	test3();
	std::cout << "data/test_devicelist end" << std::endl;
}

