#include "formnewtab.h"
#include <QMessageBox>

TFormNewTab::TFormNewTab(QString p_name):QDialog()
{
	ui.setupUi(this);
	ui.tabName->setText(p_name);
	connect(ui.okButton,SIGNAL(clicked()),this,SLOT(accept()));
	connect(ui.cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}


void TFormNewTab::save()
{
	if(ui.tabName->text().length()==0){
		QMessageBox::information(nullptr,i18n("Error"),i18n("Name can't be empty"));
	} else {
		accept();
	}
}
