#include <QDialog>
#include "gui/mountdialog.h"
#include <klocalizedstring.h>
#include <QMessageBox>
#include <QFileInfo>
#include <sys/mount.h>
#include <string.h>
#include "data/filesystems.h"
#include "base/linklist.h"
#include "base/compat.h"


/** TMount Dialog constructor
* \param p_device   This device will be selected in device selection list (mount device)
* \parem p_devices  device list=>Used to fill "mount device" selection list
*/
TMountDialog::TMountDialog(TDeviceBase* p_device,const QHash<QString,TDeviceBase *> *p_devices)
{
	ui.setupUi(this);
	device=p_device;
	devices=p_devices;
	fillDeviceSelectList();
	onDevChange(0);
	
	

	ui.accesTimeSet->addItem(i18n("Do not update access time"));
	ui.accesTimeSet->addItem(i18n("Only later then mod. time"));
	ui.accesTimeSet->addItem(i18n("Always"));
	ui.accesTimeSet->setCurrentIndex(0);
	
	connect(ui.okButton,SIGNAL(pressed()),this,SLOT(handleAction()));
	connect(ui.cancelButton,SIGNAL(pressed()),this,SLOT(close()));	
	connect(ui.mountDevice,SIGNAL(currentIndexChanged(int)),this,SLOT(onDevChange(int)));
	connect(ui.optionMount,SIGNAL(clicked()),this,SLOT(actionClicked()));
	connect(ui.optionUnmount,SIGNAL(clicked()),this,SLOT(actionClicked()));
	connect(ui.mountpoint,SIGNAL(textChanged(const QString &)),this, SLOT(mountpointChanged(const QString& )));
	ui.errorLabel->setVisible(false);
	actionClicked();
}

void TMountDialog::mountpointChanged(const QString& p_text)
{
	QFileInfo l_info(p_text);
	QString l_text="";
	if(!l_info.exists()){
		l_text=i18n("Path doesn't exists.");		
	} else if (!l_info.isDir()){
		l_text=i18n("Path is not a directory but a file");
	}
	if(l_text.length()>0){
		ui.errorLabel->setText(l_text);
		ui.errorLabel->setVisible(true);		
	} else {
		ui.errorLabel->setVisible(false);
	}
}

void TMountDialog::onDevChange(int p_index)
{
	QStringList l_fileSystems;

	//Get available file systems for OS and fill file type combo	
	getFileSystems(l_fileSystems);
	QString l_deviceName=ui.mountDevice->currentText();
	TDeviceBase *l_device=devices->value(l_deviceName);
	if(l_device != nullptr){
		ui.fsType->clear();
		QString l_lower=l_device->getType().toLower();
		int l_foundIndex=-1;
		int l_index=0;
		for(QString l_fileSystem:l_fileSystems){
			ui.fsType->addItem(l_fileSystem);
			if(l_fileSystem.toLower()==l_lower) l_foundIndex=l_index;
			l_index++;		
		}
		//When file type not found add it....
		if(l_foundIndex==-1){
			ui.fsType->addItem(l_device->getType());
			l_foundIndex=l_index;
		}
		ui.fsType->setCurrentIndex(l_foundIndex);
	
		//Fill what to umount? selection box	
		ui.unmountWhat->clear();
		TLinkList<TMount> *l_mounts=l_device->getMounts();
		if(l_mounts->isEmpty()){
			ui.optionUnmount->setDisabled(true);
			ui.optionMount->setChecked(true);
		}else {
			ui.optionUnmount->setDisabled(false);

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
	}
	actionClicked();
}


void TMountDialog::fillDeviceSelectList()
{
	QHashIterator<QString,TDeviceBase *> l_iter(*devices);
	int l_index=1;
	int l_selected=0;
	ui.mountDevice->addItem("");
	while(l_iter.hasNext()){
		l_iter.next();
		if(!l_iter.value()->hasPartitions()){
			ui.mountDevice->addItem(l_iter.key());
			if(device != nullptr){
				if(l_iter.key()==device->getName()) l_selected=l_index;
			}
			l_index++;
		}
	}
	ui.mountDevice->setCurrentIndex(l_selected);
	ui.mountDevice->model()->sort(0);
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
	} else {
		QMessageBox::information(nullptr,i18n("Error"),i18n("Please select operation"));

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
	TDeviceBase *l_device;
	int l_flags=0;
	l_device=getCurrentDevice();
	if(l_device==nullptr){
		QMessageBox::information(nullptr,i18n("Error"),i18n("No device selected"));
		return;
	}
	if(ui.mountpoint->text().length()==0){
		QMessageBox::information(nullptr,i18n("Error"),i18n("Mount point is empty"));
		return;
	}
	
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
	
	bool l_ret=qmount(l_device->getDevPath(),ui.mountpoint->text(),ui.fsType->currentText(),l_flags,qstr(ui.extraOptions->text()));
	
	if(!l_ret){
		int l_err=errno;
		QMessageBox::information(nullptr,i18n("Error during mounting"),strerror(l_err));
	} else {
		close();
	}
}
