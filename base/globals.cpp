#include "globals.h"
#include <klocalizedstring.h>
//List of fields shown in "Device" tab

const  int g_numDeviceFields=9;
const  char *g_deviceFields[g_numDeviceFields]={
	I18N_NOOP("Size")
,	I18N_NOOP("Model")
,	I18N_NOOP("Type")
,	I18N_NOOP("Mounted")
,	I18N_NOOP("Label")
,	I18N_NOOP("Size (KMG)")
,	I18N_NOOP("Read only")
,	I18N_NOOP("Removable")
,	I18N_NOOP("Loop back file")
};