#ifndef __TESTCONFIG_H_
#define __TESTCONFIG_H_
#include <string>

class TTestConfig
{
private:
	std::string tempDir;
public:
	inline std::string &getTempDir(){return tempDir;};
	bool tmpMkDir(const std::string &p_path,std::string *p_fullPath=nullptr);
	bool initConfig();
	TTestConfig();
	~TTestConfig();
};

#endif
