#include "test_deviceinfo.h"

TTestDataDeviceInfo::TTestDataDeviceInfo()
{
	deviceInfo=new TDeviceInfo();
	deviceInfo->setSysBlockPath(getConfig()->getFilePath("/sys/block/"));
}

TTestDataDeviceInfo::~TTestDataDeviceInfo()
{
	if(deviceInfo!=nullptr) delete deviceInfo;
}


void TTestDataDeviceInfo::test1()
{
	deviceInfo->getDisks();
}

void TTestDataDeviceInfo::doRun()
{
	std::cout << "Start TTestDataDeviceInfo" << std::endl;
	test1();
	std::cout << "End TTestDataDeviceInfo" << std::endl;
}
