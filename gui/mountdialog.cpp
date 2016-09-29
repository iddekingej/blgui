#include <QDialog>
#include "gui/mountdialog.h"
#include <klocalizedstring.h>
#include <QMessageBox>
#include <sys/mount.h>
#include <string.h>


TMountDialog::TMountDialog(TDeviceBase* p_device)
{
	ui.setupUi(this);
	device=p_device;
	ui.deviceName->setText(device->getName());
	connect(ui.okButton,SIGNAL(pressed()),this,SLOT(mountDevice()));
	connect(ui.cancelButton,SIGNAL(pressed()),this,SLOT(close()));	
}

void TMountDialog::mountDevice()
{
	
	int l_ret=mount(device->getDevPath().toUtf8().data(),ui.mountpoint->text().toUtf8().data(),device->getType().toUtf8().data(),0,"");
	
	if(l_ret<0){
		int l_err=errno;
		QMessageBox l_msg;
		l_msg.setText(strerror(l_err));
		l_msg.setStandardButtons(QMessageBox::Ok);		
		l_msg.exec();
	} else {
		close();
	}
}
