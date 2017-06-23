#ifndef __MOCCREATOR_H_
#define __MOCCREATOR_H_

#include "formula/creator.h"
#include <QVector>

class TMocCreator:public TCreator
{
private:
	QHash <TField,QVariant> values;
	
public:	
	virtual bool getFieldValue(TField p_field, QVariant& p_value) override;
	void addValue(TField p_field,const QVariant p_value){
		values.insert(p_field,p_value);
	}
	virtual ~TMocCreator(){};
};

#endif
