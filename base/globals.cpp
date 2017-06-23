#include "globals.h"
#include <klocalizedstring.h>
/**
 *  List of possible fields shown in "Device" tab
 */


const TFieldInfo  g_deviceFields[]={
	{I18N_NOOP("Size"),'N',"size",-1,TField::SIZE}
,	{I18N_NOOP("Model"),'S',"model",-1,TField::MODEL}
,	{I18N_NOOP("Type"),'S',"type",-1,TField::TYPE}
,	{I18N_NOOP("Mounted"),'S',"mounted",-1,TField::MOUNTED}
,	{I18N_NOOP("Label"),'S',"label",-1,TField::LABEL}
,	{I18N_NOOP("Size (KMG)"),'S',"readable_size",0,TField::SIZE_KMG}
,	{I18N_NOOP("Read only"),'S',"readonly",-1,TField::READONLY}
,	{I18N_NOOP("Removable"),'S',"removable",-1,TField::REMOVABLE}
,	{I18N_NOOP("Loop back file"),'S',"loopback_file",-1,TField::LOOPBACKFILE}
,	{I18N_NOOP("Slaves"),'S',"slaves",-1,TField::SLAVES}
,	{I18N_NOOP("Free space"),'S',"freespace",-1,TField::FREE_SPACE}
,	{I18N_NOOP("Scsi bus"),'S',"scsibus",-1,TField::SCSI_BUS}
,	{I18N_NOOP("Iscsi host"),'S',"iscsi_host",-1,TField::ISCSI_HOST}
,	{I18N_NOOP("Start(bytes)"),'N',"start",-1,TField::START}
,	{I18N_NOOP("Free space (KMG)"),'S',"readable_freespace",10,TField::FREE_SPACE_KMG}
,	{I18N_NOOP("Rotational"),'S',"rotaional",-1,TField::ROTATIONAL}
,	{I18N_NOOP("USB bus"),'S',"usb_bus",-1,TField::USB_BUS}
,	{I18N_NOOP("PCI bus"),'S',"pci_bus",-1,TField::PCI_BUS}
,	{I18N_NOOP("Volume group name"),'S',"volume_group_name",-1,TField::VG_NAME}
,	{I18N_NOOP("Lvm name"),'S',"lvm_name",-1,TField::LVM_NAME}
};



/**
 *  Number of fields in g_deviceFields
 */
const  int g_numDeviceFields=sizeof(g_deviceFields)/sizeof(TFieldInfo);

