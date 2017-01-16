#include "test_device.h"

void TTestDevice::doRun()
{
	std::cout << "TestDevice::doRun begin" <<std::endl;
	test1();
	std::cout << "TestDevice::doRun end" <<std::endl;

}


void TTestDevice::test1()
{
	if(device->getName() != "Test1"){
		failv("getName doesn't return 'Test1'",device->getName());
	}
	if(device->getModel() != "Test2"){
		failv("getModel doesn't return 'Test2'",device->getModel());
	}
	if(device->getSize() != 1024*1024){
		failv("getSize doesnt return 1024*1024",device->getSize());
	}
	if(device->getReadableSize() != "1M"){
		failv("getSize doesn't return 1M",device->getReadableSize());
	}
}


void TTestDevice::test2()
{
	device->setIscsiAddress("D1");
	if(device->getIScsiAddress()!="D1"){
		fail("getUIsciAddress doesn't return D1");
	}
	device->setLoopbackFile("some file");
	if(device->getLoopbackFile() != "some file"){
		fail("GetLoopback file doesn't return 'some file'");
	}
}


TTestDevice::TTestDevice():TTestClass()
{
	device=new TDevice("Test1",1024*1024);
	device->setModel("Test2");
}

TTestDevice::~TTestDevice()
{
	if(device != nullptr) delete device;
}


