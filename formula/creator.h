#ifndef __CREATOR_H_
#define __CREATOR_H_

#include <QString>
#include "../data/devicebase.h"

class TCreator
{
private:
	QString error;	
public:
	inline void resetError(){ error="";}
	inline void setError(const QString &p_error){ error=p_error;}
	inline const QString &getError(){ return error;}

	virtual bool getFieldValue(TField p_no,QVariant &p_value)=0;
	virtual ~TCreator(){};
};

class TDeviceCreator:public TCreator
{
private:

	TDeviceBase *device;
public:
	TDeviceCreator(TDeviceBase *p_device);
	virtual bool getFieldValue(TField p_no,QVariant &p_value) override;
};

#endif

