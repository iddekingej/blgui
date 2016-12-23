
#include "run_data.h"
#include "test_btrfs.h"

class TDataRunner:public TRunner
{
protected:
		
	virtual void doRun()
	{
		runner(new TTestBtrfs());
	}
	
public:
	TDataRunner(TTestConfig *p_testConfig):TRunner(p_testConfig)
	{
		
	}

};

bool run_data(TTestConfig* p_config)
{

	TDataRunner l_run(p_config);
	return l_run.run();
}


