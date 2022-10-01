#include "run_base.h"
#include "test01.h"
#include "test02.h" 

class TRunBaseRunner:public TRunner
{
protected:
/**
 *Run all base tests
 */		
	void doRun() override
	{
		runner(new TTest01());
		runner(new TTest02());
	}
	
public:
	TRunBaseRunner(TTestConfig *p_testConfig):TRunner(p_testConfig)
	{
		
	}

};

/**
 * Start all base testes
 */
bool run_base(TTestConfig* p_config)
{

	TRunBaseRunner l_run(p_config);
	return l_run.run();
}

