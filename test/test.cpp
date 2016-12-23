#include "base/run_base.h"
#include "../base/utils.h"
#include <iostream>

int main(UNUSEDPAR int argc,UNUSEDPAR char **argv) {
	if(run_base()){
		std::cout <<"Test failed" <<std::endl;
		return 255;
	}
	return 0;
}
