#include "../lib/runner.h"
#include "../lib/testconfig.h"
#include "run_formula.h"
#include "test_scanner.h"
#include "test_eval.h"
#include "test_node.h"
#include "test_parser.h"
#include <iostream>

class TFormulaRunner:public TRunner
{
protected:
		
	virtual void doRun()
	{
		std::cout << "Parser test BEGIN" << std::endl;
		runner(new TTestScanner());
		runner(new TTestParser());
		runner(new TTestEval());
		runner(new TTestNode());
		std::cout << "Parser test END" << std::endl;
		
	}
	
public:
	TFormulaRunner(TTestConfig *p_testConfig):TRunner(p_testConfig)
	{
		
	}

};


bool run_formula(TTestConfig* p_config)
{
	TFormulaRunner l_runner(p_config);
	return l_runner.run();
}
