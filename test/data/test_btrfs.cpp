#include "test_btrfs.h"
#include <QString>
void TBtrfsInfoTest::getRaidLevel(const QString& p_path, QString& p_raidLevel)
{
	TBtrfsInfo::getRaidLevel(p_path,p_raidLevel);
}


void TTestBtrfs::doRun()
{
	test01();
	if(getFailed()) return;
	test02();
}

void TTestBtrfs::test01()
{	
	std::string l_dir=getConfig()->getTempDir();
	getConfig()->tmpMkDir("allocation");
	getConfig()->tmpMkDir("allocation/system");
	QString l_return;
	info->getRaidLevel(l_dir.c_str(),l_return);
	if(l_return != ""){
		fail("getRaidLevel doesn't return empty string");
	}
	
}

void TTestBtrfs::test02()
{
	std::string l_dir=getConfig()->getTempDir();
	getConfig()->tmpMkDir("allocation/system/aaa");
	getConfig()->tmpMkDir("allocation/system/xxx");
	getConfig()->tmpMkDir("allocation/system/raid13");
	QString l_return;
	info->getRaidLevel(l_dir.c_str(),l_return);
	if(l_return != "raid13"){
		fail("getRaidLevel doesn't 'raid13'");
	}
}


TTestBtrfs::TTestBtrfs()
{
	info=new TBtrfsInfoTest();
}

TTestBtrfs::~TTestBtrfs()
{	
	if(info != nullptr) delete info;
}
