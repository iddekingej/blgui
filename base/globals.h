#ifndef __GLOBALS_H_
#define __GLOBALS_H_


/**
 *  Definition of fields available for the main grid
 */
typedef struct {
	const char *title; //Title of field
	const char type;   //Sort type of field
	int realValue;
} TFieldInfo;

//List of fields shown in "Device" tab

extern const  int g_numDeviceFields;
extern const  TFieldInfo g_deviceFields[];


#endif
