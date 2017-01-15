#ifndef __TEST_BTRFS_H_
#define __TEST_BTRFS_H_
#include "../lib/testclass.h"
#include "../../data/btrfs.h"


class TBtrfsInfoTest:public TBtrfsInfo
{
public:
	static void getRaidLevel(const QString &p_path,QString &p_raidLevel);
};

class TTestBtrfs:public TTestClass
{
private:
	TBtrfsInfoTest *info;
protected:
	virtual void doRun() override;	
	void test01();
	void test02();
public:
	
	TTestBtrfs();
	virtual ~TTestBtrfs();
};
#endif
