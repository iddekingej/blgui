#include "globals.h"
#include <klocalizedstring.h>
/**
 *  List of possible fields shown in "Device" tab
 */


const TFieldInfo  g_deviceFields[]={
	{I18N_NOOP("Size"),TSortType::NUMERIC,"size",-1,TField::SIZE}
,	{I18N_NOOP("Model"),TSortType::STRING,"model",-1,TField::MODEL}
,	{I18N_NOOP("Type"),TSortType::STRING,"type",-1,TField::TYPE}
,	{I18N_NOOP("Mounted"),TSortType::STRING,"mounted",-1,TField::MOUNTED}
,	{I18N_NOOP("Label"),TSortType::STRING,"label",-1,TField::LABEL}
,	{I18N_NOOP("Size (KMG)"),TSortType::STRING,"readable_size",0,TField::SIZE_KMG}
,	{I18N_NOOP("Read only"),TSortType::STRING,"readonly",-1,TField::READONLY}
,	{I18N_NOOP("Removable"),TSortType::STRING,"removable",-1,TField::REMOVABLE}
,	{I18N_NOOP("Loop back file"),TSortType::STRING,"loopback_file",-1,TField::LOOPBACKFILE}
,	{I18N_NOOP("Slaves"),TSortType::STRING,"slaves",-1,TField::SLAVES}
,	{I18N_NOOP("Free space"),TSortType::STRING,"freespace",-1,TField::FREE_SPACE}
,	{I18N_NOOP("Scsi bus"),TSortType::STRING,"scsibus",-1,TField::SCSI_BUS}
,	{I18N_NOOP("Iscsi host"),TSortType::STRING,"iscsi_host",-1,TField::ISCSI_HOST}
,	{I18N_NOOP("Start(bytes)"),TSortType::NUMERIC,"start",-1,TField::START}
,	{I18N_NOOP("Free space (KMG)"),TSortType::STRING,"readable_freespace",10,TField::FREE_SPACE_KMG}
,	{I18N_NOOP("Rotational"),TSortType::STRING,"rotaional",-1,TField::ROTATIONAL}
,	{I18N_NOOP("USB bus"),TSortType::STRING,"usb_bus",-1,TField::USB_BUS}
,	{I18N_NOOP("PCI bus"),TSortType::STRING,"pci_bus",-1,TField::PCI_BUS}
,	{I18N_NOOP("Volume group name"),TSortType::STRING,"volume_group_name",-1,TField::VG_NAME}
,	{I18N_NOOP("Lvm name"),TSortType::STRING,"lvm_name",-1,TField::LVM_NAME}
};



/**
 * \var
 *  Number of fields in @see g_deviceFields
 */
const  int g_numDeviceFields=sizeof(g_deviceFields)/sizeof(TFieldInfo);

