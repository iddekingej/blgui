#include "base/run_base.h"
#include "../base/utils.h"
#include "lib/testconfig.h"
#include <iostream>

int main(UNUSEDPAR int argc,UNUSEDPAR char **argv) {
	TTestConfig *l_config=new TTestConfig();
	if(!l_config->initConfig()){
		std::cout << "init config failed" <<std::endl;
		return 255;
	}
	if(run_base(l_config)){
		std::cout <<"Test failed" <<std::endl;
		return 255;
	}
	return 0;
}
