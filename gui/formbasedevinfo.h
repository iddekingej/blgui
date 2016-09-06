#ifndef __FORBASEDEVINFO_H_
#define __FORBASEDEVINFO_H_
#include <QDialog>
#include <QVariantList>
#include <QTableView>
#include <QLabel>
#include "data/devicebase.h"

class TFormBaseDevInfo:public QDialog
{
	
protected:
	QVariantList enableDeviceFields;
public:
	void readConfiguation();
	TFormBaseDevInfo();
	void fillAliases(QTableView *p_view,QLabel *p_noAlias,TDeviceBase *p_device);
	virtual ~TFormBaseDevInfo();
};

#endif