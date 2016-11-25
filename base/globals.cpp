#include "globals.h"
#include <klocalizedstring.h>
//List of fields shown in "Device" tab


const  char *g_deviceFields[]={
	I18N_NOOP("Size")
,	I18N_NOOP("Model")
,	I18N_NOOP("Type")
,	I18N_NOOP("Mounted")
,	I18N_NOOP("Label")
,	I18N_NOOP("Size (KMG)")
,	I18N_NOOP("Read only")
,	I18N_NOOP("Removable")
,	I18N_NOOP("Loop back file")
,	I18N_NOOP("Slaves")
,	I18N_NOOP("Free space")
,	I18N_NOOP("scsi bus")
,	I18N_NOOP("iscsi host")
,	I18N_NOOP("Start(bytes)")
,	I18N_NOOP("Free space (KMG)")
,	I18N_NOOP("Rotational")
,	I18N_NOOP("USB bus")
,	I18N_NOOP("PCI bus")
,	I18N_NOOP("Volume group name")
};
const  int g_numDeviceFields=sizeof(g_deviceFields)/sizeof(char*);
