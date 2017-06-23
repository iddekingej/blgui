#ifndef __TESTCLASS_H_
#define __TESTCLASS_H_
#include <iostream>
#include <QString>
#include <QVariant>
#include "testconfig.h"
#include "../../data/devicelist.h"
#include "../../data/alias.h"
#define fail(p_message) error(__FILE__,__FUNCTION__,p_message)
#define failv(p_message,p_value) errorv(__FILE__,__FUNCTION__,p_message,p_value)
#define expect(p_message,p_expected,p_found) fexpect(__FILE__,__FUNCTION__,p_message,p_expected,p_found)
#define expecti(p_message,p_expected,p_found) fexpect(__FILE__,__FUNCTION__,p_message,(long int)p_expected,(long int)p_found)
class TTestClass{
private:
	bool failed=false;
	TTestConfig *config=nullptr;
protected:
	virtual void doRun();	
	virtual void setup();
public:
	inline void setConfig(TTestConfig *p_config){ config=p_config;}
	inline TTestConfig *getConfig(){ return config;}
	inline bool getFailed(){ return failed;};
	void error(const char *p_file,const char *p_method,const char *p_message);
	void error(const char *p_file,const char *p_method,const QString  &p_message){
		error(p_file,p_method,qstr(p_message));
	}
	void errorv(const char* p_file, const char* p_method, const char* p_message, const char *p_result);
	void errorv(const char* p_file, const char* p_method, const char* p_message, QString p_result);
	void errorv(const char* p_file, const char* p_method, const char* p_message, long p_result);
	bool fexpect(const char* p_file,const char *p_method,const char* p_message, long p_expected,long p_found);
	bool fexpect(const char* p_file,const char *p_method,const char* p_message, int p_expected,int p_found);
	bool fexpect(const char* p_file,const char *p_method,const char* p_message, int p_expected,long p_found);
	bool fexpect(const char* p_file,const char *p_method,const char* p_message, bool p_expected,bool p_found);
	bool fexpect(const char* p_file, const char* p_method, const char* p_message, QString p_expected, QString p_found);
bool fexpect(const char* p_file, const char* p_method, const char* p_message, QVariant p_expected, QVariant p_found);
	TAlias      *createAliasList();
	TDeviceList *createDeviceList(TAlias *p_alias);
	TDeviceList *createDeviceList2(TAlias *p_alias);
	bool run();
	virtual ~TTestClass(){};
};
#endif
