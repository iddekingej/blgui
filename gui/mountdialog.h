#ifndef __MOUNTDIALOG_H__
#define __MOUNTDIALOG_H__

#include <QDialog>
#include <QString>
#include "ui_mount.h"
#include "data/devicebase.h"

class TMountDialog:public QDialog
{
	Q_OBJECT
private slots:
	void handleAction();
	void actionClicked();
	void fillDeviceSelectList();
	void onDevChange(int p_index);
	void mountpointChanged(const QString &p_text);
private:
	Ui::MountDialog ui;
	TDeviceBase *device;
	void unmountDevice();
	void mountDevice();
	inline TDeviceBase *getCurrentDevice(){ return devices->value(ui.mountDevice->currentText());}

	const QHash<QString,TDeviceBase *> *devices;
public:
	TMountDialog(TDeviceBase *p_device,const QHash<QString,TDeviceBase *> *p_devices);
};

#endif
