#include "test_deviceinfo.h"

/**
 * Set up device info object 
 * and set the base path to the test data
 */
TTestDataDeviceInfo::TTestDataDeviceInfo()
{
	deviceInfo=new TDeviceInfo();
	deviceInfo->setBasePath(getConfig()->getFilePath("/"));
}

TTestDataDeviceInfo::~TTestDataDeviceInfo()
{
	if(deviceInfo!=nullptr) delete deviceInfo;
}

/**
 * Check reading all the information
 */

void TTestDataDeviceInfo::test1()
{
	deviceInfo->getDisks();
}
/**
 * Execute  fillDatarow on all devices and partitions 
 * This can be used in combination with valgrid to check for 
 * memory,  initialization  or null ptr errors.
 */
void TTestDataDeviceInfo::test2()
{
	TLinkListItem<TDevice> *l_current=deviceInfo->getDevices()->getStart();
	TLinkListItem<TPartition> *l_parCurrent;
	QStringList l_info;
	while(l_current != nullptr){
		l_current->getItem()->fillDataRow(l_info);
		l_parCurrent=l_current->getItem()->getPartitionStart();
		while(l_parCurrent != nullptr){
			l_parCurrent->getItem()->fillDataRow(l_info);
			l_parCurrent=l_parCurrent->getNext();
		}
		l_current=l_current->getNext();
	}
}

/**
 * Run all test.
 */

void TTestDataDeviceInfo::doRun()
{
	std::cout << "Start TTestDataDeviceInfo" << std::endl;
	test1();
	test2();
	std::cout << "End TTestDataDeviceInfo" << std::endl;
}
