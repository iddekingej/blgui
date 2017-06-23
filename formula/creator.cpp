#include "creator.h"
#include "base/globals.h"

bool TDeviceCreator::getFieldValue(TField p_no, QVariant& p_value)
{
	
	return device->getFieldValue((TField)p_no,p_value);	
}


TDeviceCreator::TDeviceCreator(TDeviceBase* p_device)
{
	device=p_device;
}
