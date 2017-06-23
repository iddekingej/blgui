#include "base/run_base.h"
#include "data/run_data.h"
#include "formula/run_formula.h"
#include "../base/utils.h"
#include "lib/testconfig.h"
#include <iostream>
/**
 * Main entry point test program
 * 
 */
int main(UNUSEDPAR int argc,UNUSEDPAR char **argv) {
	TTestConfig *l_config=new TTestConfig();
	if(!l_config->initConfig()){
		std::cout << "init config failed" <<std::endl;
		return 255;
	}
	if(run_base(l_config)){
		std::cout <<"run_base failed" <<std::endl;
		return 255;
	}
	if(run_data(l_config)){
		std::cout <<"run_data failed" <<std::endl;
		return 255;
	}
	if(run_formula(l_config)){
		std::cout  << "run_formula failed" <<std::endl;
		return 255;
	}
	delete l_config;
	return 0;
}
