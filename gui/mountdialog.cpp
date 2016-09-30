#include <QDialog>
#include "gui/mountdialog.h"
#include <klocalizedstring.h>
#include <QMessageBox>
#include <sys/mount.h>
#include <string.h>
#include "data/filesystems.h"
#include "base/linklist.h"



TMountDialog::TMountDialog(TDeviceBase* p_device)
{
	QStringList l_fileSystems;
	ui.setupUi(this);
	device=p_device;
	ui.deviceName->setText(device->getName());
	connect(ui.okButton,SIGNAL(pressed()),this,SLOT(handleAction()));
	connect(ui.cancelButton,SIGNAL(pressed()),this,SLOT(close()));	
//Get available file systems for OS and fill file type combo	
	getFileSystems(l_fileSystems);
	QString l_lower=p_device->getType().toLower();
	int l_foundIndex=-1;
	int l_index=0;
	for(QString l_fileSystem:l_fileSystems){
		ui.fsType->addItem(l_fileSystem);
		if(l_fileSystem.toLower()==l_lower) l_foundIndex=l_index;
		l_index++;		
	}
//When filetype not found add it....
	if(l_foundIndex==-1){
		ui.fsType->addItem(p_device->getType());
		l_foundIndex=l_index;
	}
	ui.fsType->setCurrentIndex(l_foundIndex);
	ui.accesTimeSet->addItem(i18n("Do not update access time"));
	ui.accesTimeSet->addItem(i18n("Only later then mod. time"));
	ui.accesTimeSet->addItem(i18n("Allways"));
	ui.accesTimeSet->setCurrentIndex(0);
	
//Fill what to umount? selection box	
	TLinkList<TMount> *l_mounts=device->getMounts();
	if(l_mounts->isEmpty()){
		ui.optionUnmount->setDisabled(true);
		ui.optionMount->setChecked(true);
	}else {
		ui.optionUnmount->setChecked(true);
		if(l_mounts->getLength()>1){
			ui.unmountWhat->addItem(QStringLiteral(""));
		}
		TLinkListIterator<TMount> l_iter(l_mounts);
		TMount *l_item;	
		while(l_iter.hasNext()){
			l_item=l_iter.next();
			ui.unmountWhat->addItem(l_item->getMountPoint());
		}
	}
	connect(ui.optionChange,SIGNAL(clicked()),this,SLOT(actionClicked()));
	connect(ui.optionMount,SIGNAL(clicked()),this,SLOT(actionClicked()));
	connect(ui.optionUnmount,SIGNAL(clicked()),this,SLOT(actionClicked()));
	connect(ui.optionMove,SIGNAL(clicked()),this,SLOT(actionClicked()));
	actionClicked();
}

void TMountDialog::actionClicked()
{
	ui.unmountForm->setMaximumHeight(ui.optionUnmount-> isChecked()?16777215:0);
	ui.mountForm->setMaximumHeight(ui.optionMount->isChecked()?16777215:0);
	QApplication::processEvents( QEventLoop::ExcludeUserInputEvents );
	resize( sizeHint() );
}


void TMountDialog::handleAction()
{
	if(ui.optionMount->isChecked()){
		mountDevice();
	} else if(ui.optionUnmount->isChecked()){
		unmountDevice();
	}
}
void TMountDialog::unmountDevice()
{
	QString l_what=ui.unmountWhat->currentText();
	if(l_what.length()==0){
		QMessageBox::information(nullptr,i18n("Error"),i18n("Please select what to unmount"));
	} else {
		if(qumount(l_what,ui.lazyUnmount->checkState()==Qt::Checked)){
			close();
		} else {
			int l_err=errno;
			QMessageBox::information(nullptr,i18n("Unmounting failed"),strerror(l_err));
		}
	}
}
void TMountDialog::mountDevice()
{
	if(ui.mountpoint->text().length()==0){
		QMessageBox::information(nullptr,i18n("Error"),i18n("Mount point is empty"));
		return;
	}
	int l_flags=0;
	if(ui.noExec->checkState()==Qt::Checked) l_flags |= MS_NOEXEC;
	if(ui.noSuid->checkState()==Qt::Checked) l_flags |= MS_NOSUID;
	if(ui.readOnly->checkState()==Qt::Checked) l_flags |= MS_RDONLY;
	if(ui.readOnly->checkState()==Qt::Checked) l_flags |= MS_NODEV;
	if(ui.noAccessDir->checkState()==Qt::Checked) l_flags |= MS_NODIRATIME;
	switch(ui.accesTimeSet->currentIndex()){
		case 0:l_flags |= MS_NOATIME;break;
		case 1:l_flags |= MS_RELATIME;break;
		case 2:l_flags |= MS_STRICTATIME;break;
	}
	
	bool l_ret=qmount(device->getDevPath(),ui.mountpoint->text(),ui.fsType->currentText(),l_flags,QStringLiteral(""));
	
	if(!l_ret){
		int l_err=errno;
		QMessageBox::information(nullptr,i18n("Error during mounting"),strerror(l_err));
	} else {
		close();
	}
}
