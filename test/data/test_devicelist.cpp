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
	TDevice *l_device;
	expect("Number of devices read from test /sys/block",3,deviceList->getLength());
	TDeviceBase *l_deviceBase=deviceList->getDeviceByName("sda");
	if(l_deviceBase==nullptr){
		fail("Except first item != nullptr");
	} else {
		l_device=dynamic_cast<TDevice *>(l_deviceBase);
		if( l_device==nullptr){
			fail("Found device sda is not a TDevice *");
		} else {
			expect("Device 1 name ","sda",l_device->getName());
			expect("Size of device 1",3202400*512,(long)l_device->getSize());
		}
		l_deviceBase=deviceList->getDeviceByName("sdb");
		if(l_deviceBase==nullptr){
			fail("Expected second item != nullptr");
		} else {
			if((l_device=dynamic_cast<TDevice *>(l_deviceBase))==nullptr){
				fail("Found device sdb is not a TDevice *");

			} else {
				expect("Device 2 name","sdb",l_device->getName());
				expect("Model of dev 2","bla bla",l_device->getModel());
				expect("Vendor of dev 2","TestVendor",l_device->getVendor());
			}
		}
	}
}

void TTestDataDeviceList::test4()
{	
	TDevice *l_device;
	TDeviceBase *l_deviceBase=deviceList->getDeviceByName("sda");
	if(l_deviceBase ==nullptr){
		fail("First device returns null");
		return;
	}
	
	l_device=dynamic_cast<TDevice *>(l_deviceBase);
	if(l_device==nullptr){
		fail("Device sda is not a TDevice");
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
	expect("Partition 1 size ",102400*512,(long)l_partition->getSize());
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

