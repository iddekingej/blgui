#ifndef __MOUNTDIALOG_H__
#define __MOUNTDIALOG_H__

#include <QDialog>
#include <QString>
#include "ui_mount.h"
#include "data/devicebase.h"

/**
 * Dialog for mounting or unmounting a selected device
 */

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
	/**
	 * Layout of the dialog
	 * Generated from mount.ui
	 */
	Ui::MountDialog ui;
	/**
	 * Currently selected device
	 */
	TDeviceBase *device;
	/**
	 * Availbe devices on system
	 * This list contain block devicises (for example sda) and partitions
	 */
	const QHash<QString,TDeviceBase *> *devices;

	void unmountDevice();
	void mountDevice();
	inline TDeviceBase *getCurrentDevice(){ return devices->value(ui.mountDevice->currentText());}
public:
	TMountDialog(TDeviceBase *p_device,const QHash<QString,TDeviceBase *> *p_devices);
};

#endif
