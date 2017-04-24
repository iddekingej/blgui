#include "globals.h"
#include <klocalizedstring.h>
/**
 *  List of possible fields shown in "Device" tab
 */


const TFieldInfo  g_deviceFields[]={
	{I18N_NOOP("Size"),'N',-1}
,	{I18N_NOOP("Model"),'S',-1}
,	{I18N_NOOP("Type"),'S',-1}
,	{I18N_NOOP("Mounted"),'S',-1}
,	{I18N_NOOP("Label"),'S',-1}
,	{I18N_NOOP("Size (KMG)"),'S',0}
,	{I18N_NOOP("Read only"),'S',-1}
,	{I18N_NOOP("Removable"),'S',-1}
,	{I18N_NOOP("Loop back file"),'S',-1}
,	{I18N_NOOP("Slaves"),'S',-1}
,	{I18N_NOOP("Free space"),'S',-1}
,	{I18N_NOOP("Scsi bus"),'S',-1}
,	{I18N_NOOP("Iscsi host"),'S',-1}
,	{I18N_NOOP("Start(bytes)"),'N',-1}
,	{I18N_NOOP("Free space (KMG)"),'S',10}
,	{I18N_NOOP("Rotational"),'S',-1}
,	{I18N_NOOP("USB bus"),'S',-1}
,	{I18N_NOOP("PCI bus"),'S',-1}
,	{I18N_NOOP("Volume group name"),'S',-1}
,	{I18N_NOOP("Lvm name"),'S',-1}
};



/**
 *  Number of fields in g_deviceFields
 */
const  int g_numDeviceFields=sizeof(g_deviceFields)/sizeof(TFieldInfo);
