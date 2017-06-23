#ifndef __GLOBALS_H_
#define __GLOBALS_H_

#define PROG_NAME "blgui"
#include <qglobal.h>
#if QT_VERSION >= QT_VERSION_CHECK( 5, 0, 0 )
#include <qhashfunctions.h>
#else
#include <qhash.h>
#endif



 enum class TField:int{
	DEVICE_NAME=0
,	PARTITION_NAME=1
,	SIZE=2
,	MODEL=3
,	TYPE=4
,	MOUNTED=5
,	LABEL=6
,	SIZE_KMG=7
,	READONLY=8
,	REMOVABLE=9
,	LOOPBACKFILE=10
,	SLAVES=11
,	FREE_SPACE=12
,	SCSI_BUS=13
,	ISCSI_HOST=14
,	START=15
,	FREE_SPACE_KMG=16
,	ROTATIONAL=17
,	USB_BUS=18
,	PCI_BUS=19
,	VG_NAME=20
,	LVM_NAME=21
,	NOTFOUND=-1
};

/**
 *  Definition of fields available for the main grid
 */
typedef struct {
	const char *title; //Title of field
	const char type;   //Sort type of field
	const char *fieldName; //Field name in extended condition
	int realValue;
	TField fieldId;
} TFieldInfo;

//List of fields shown in "Device" tab

extern const  int g_numDeviceFields;
extern const  TFieldInfo g_deviceFields[];

inline unsigned int qHash(TField p_field){ return qHash((int)p_field);}
#endif
