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

/**
 *  Read data from current device
 */
void TTestDataDeviceList::test1()
{
	deviceList->readInfo();
}

/**
 *  Read data from test data
 */

void TTestDataDeviceList::test2()
{
	delete deviceList;
	deviceList=new TDeviceList(alias);
	deviceList->setSysBlockPath(getConfig()->getFilePath("/sys/block/"));
	deviceList->readInfo();
}	

/**
 *  Check device1 and checkdevice2:
 *  - Size
 *  - Device name
 *  - Device model
 *  - Device vendor
 */
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
			expect("Vendor of dev 2","TestVendor",l_item->getItem()->getVendor());
		}
	}
}

void TTestDataDeviceList::test4()
{
	TLinkListItem<TDevice> *l_item=deviceList->getStart();
	TDevice *l_device=l_item->getItem();
	if(l_device ==nullptr){
		fail("First device returns null");
		return;
	}
	
	if(expect("Number of paritions",3,l_device->getPartitions()->getLength())){
		return;
	}
	TPartition *l_partition=l_device->getPartitions()->getStart()->getItem();
	if(l_partition==nullptr){
		fail("Partitions is null");
		return;
	}
	expect("Partition 1 name ","sda1",l_partition->getName());
	expect("Partition 1 size ",102400,l_partition->getSize());
}


void TTestDataDeviceList::doRun()
{
	std::cout << "data/test_devicelist begin" << std::endl;
	test1();
	test2();
	test3();
	test4();
	std::cout << "data/test_devicelist end" << std::endl;
}

