#include "formnewtab.h"
#include <QMessageBox>
#include <klocalizedstring.h>
#include <stdio.h>
TFormNewTab::TFormNewTab(QString p_name):QDialog()
{
	ui.setupUi(this);
	ui.tabName->setText(p_name);
	TFormNewTab::connect(ui.okButton,SIGNAL(clicked()),this,SLOT(saveData()));
	connect(ui.cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}


void TFormNewTab::saveData()
{
    
	if(ui.tabName->text().trimmed().length()==0){
		QMessageBox::information(this,i18n("Error"),i18n("Name can't be empty"));
	} else {
		accept();
	}
}
