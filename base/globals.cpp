#include "globals.h"
#include <klocalizedstring.h>
/**
 *  List of possible fields shown in "Device" tab
 */


const TFieldInfo  g_deviceFields[]={
	{I18N_NOOP("Size"),'N',"size",-1}
,	{I18N_NOOP("Model"),'S',"model",-1,}
,	{I18N_NOOP("Type"),'S',"type",-1}
,	{I18N_NOOP("Mounted"),'S',"mounted",-1}
,	{I18N_NOOP("Label"),'S',"label",-1}
,	{I18N_NOOP("Size (KMG)"),'S',"readable_size",0}
,	{I18N_NOOP("Read only"),'S',"readonly",-1}
,	{I18N_NOOP("Removable"),'S',"removable",-1}
,	{I18N_NOOP("Loop back file"),'S',"loopback_file",-1}
,	{I18N_NOOP("Slaves"),'S',"slaves",-1}
,	{I18N_NOOP("Free space"),'S',"freespace",-1}
,	{I18N_NOOP("Scsi bus"),'S',"scsibus",-1}
,	{I18N_NOOP("Iscsi host"),'S',"iscsi_host",-1}
,	{I18N_NOOP("Start(bytes)"),'N',"start",-1}
,	{I18N_NOOP("Free space (KMG)"),'S',"readable_freespace",10}
,	{I18N_NOOP("Rotational"),'S',"rotaional",-1}
,	{I18N_NOOP("USB bus"),'S',"usb_bus",-1}
,	{I18N_NOOP("PCI bus"),'S',"pci_bus",-1}
,	{I18N_NOOP("Volume group name"),'S',"volume_group_name",-1}
,	{I18N_NOOP("Lvm name"),'S',"lvm_name",-1}
};



/**
 *  Number of fields in g_deviceFields
 */
const  int g_numDeviceFields=sizeof(g_deviceFields)/sizeof(TFieldInfo);
