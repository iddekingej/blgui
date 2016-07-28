#include "formbasedevinfo.h"
#include <QDialog>
#include <KSharedConfig>
#include <KConfigGroup>
#include <QStandardItem>
#include <klocalizedstring.h>


void TFormBaseDevInfo::readConfiguation()
{
	enableDeviceFields.clear();
	KSharedConfig::Ptr config=KSharedConfig::openConfig();
	KConfigGroup  configGroup=config->group("enabledfields");
	enableDeviceFields=configGroup.readEntry("devicefields",QVariantList());
}

TFormBaseDevInfo::TFormBaseDevInfo():QDialog()
{
	readConfiguation();
}

void TFormBaseDevInfo::fillAliases(QTableView *p_view,QLabel *p_noAlias,TDeviceBase *p_device)
{
	TLinkListItem<TDeviceAlias> *l_current=p_device->getDeviceAliasStart();
	QStandardItemModel *l_model=new QStandardItemModel(1,2,this);
	if(l_current==nullptr){
		p_view->setVisible(false);
	}else{
		int l_cnt=0;	
		l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Type")));
		l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Alias")));
		while(l_current !=nullptr){
			l_model->setItem(l_cnt,0,new QStandardItem(l_current->getItem()->getType()));
			l_model->setItem(l_cnt,1,new QStandardItem(l_current->getItem()->getAlias()));
			l_cnt++;
			l_current=l_current->getNext();
		}
		p_view->setModel(l_model);	
		p_noAlias->setVisible(false);
		p_view->resizeRowsToContents();
		p_view->resizeColumnsToContents();	
	}
	
}