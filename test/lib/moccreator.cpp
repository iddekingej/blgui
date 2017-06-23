#include "moccreator.h"

bool TMocCreator::getFieldValue(TField p_field, QVariant& p_value)
{	
	if(values.contains(p_field)){
		p_value=values.value(p_field);
		return false;
	} 
	return true;
}

