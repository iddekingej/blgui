#include "test_mtab.h"
#include  <iostream>
#include "../../data/mount.h"

TTestDataMTab::TTestDataMTab()
{
	alias=createAliasList();
	deviceList=createDeviceList(alias);
	mtab=new TMTab(deviceList);
	mtab->setSourceFile(getConfig()->getFilePath("test_mtab1"));
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

void TTestDataMTab::test4()
{
	mtab->addMountTODevices();
	TDeviceBase *l_dev=deviceList->getDeviceByName("sda1");
	if(l_dev==nullptr){
		fail("Device sda1 not found");
	} else {
		expect("Is mounted",l_dev->isMounted(),true);
		expect("Number of mounts ",1,l_dev->getMounts()->getLength());
		if(l_dev->getMounts()->getStart()==nullptr){
			fail("mount.getStart return null");
		} else {
			TMount *l_mount=l_dev->getMounts()->getStart()->getItem();
			expect("Mount point ",l_mount->getMountPoint(),"/mnt/home");
			expect("Type",l_mount->getType(),"btrfs");
		}
	}
}

