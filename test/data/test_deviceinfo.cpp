#include "test_deviceinfo.h"

/**
 * Set up device info object 
 * and set the base path to the test data
 */

void TTestDataDeviceInfo::setup()
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
	QString l_value;
	while(l_current != nullptr){
		for(int l_cnt=0;l_cnt<g_numDeviceFields+2;l_cnt++){
			l_current->getItem()->fillDataRow((TField)l_cnt,l_value);//TODO TFIELD
		}
		l_parCurrent=l_current->getItem()->getPartitionStart();
		while(l_parCurrent != nullptr){
			for(int l_cnt=0;l_cnt<g_numDeviceFields+2;l_cnt++){
				l_parCurrent->getItem()->fillDataRow((TField)l_cnt,l_value); //TODO TFIELD
			}
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
