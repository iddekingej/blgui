#ifndef __GLOBALS_H_
#define __GLOBALS_H_

#define PROG_NAME "blgui"
/**
 *  Definition of fields available for the main grid
 */
typedef struct {
	const char *title; //Title of field
	const char type;   //Sort type of field
	const char *fieldName; //Field name in extended condition
	int realValue;
} TFieldInfo;

//List of fields shown in "Device" tab

extern const  int g_numDeviceFields;
extern const  TFieldInfo g_deviceFields[];

typedef enum{
	FIELD_DEVICE_NAME=0
,	FIELD_PARTITION_NAME=1
,	FIELD_SIZE=2
,	FIELD_MODEL=3
,	FIELD_TYPE=4
,	FIELD_MOUNTED=5
,	FIELD_LABEL=6
,	FIELD_SIZE_KMG=7
,	FIELD_READONLY=8
,	FIELD_REMOVABLE=9
,	FIELD_LOOPBACKFILE=10
,	FIELD_SLAVES=11
,	FIELD_FREE_SPACE=12
,	FIELD_SCSI_BUS=13
,	FIELD_ISCSI_HOST=14
,	FIELD_START=15
,	FIELD_FREE_SPACE_KMG=16
,	FIELD_ROTATIONAL=17
,	FIELD_USB_BUS=18
,	FIELD_PCI_BUS=19
,	FIELD_VG_NAME=20
,	FIELD_LVM_NAME=21
} TField;
#endif
