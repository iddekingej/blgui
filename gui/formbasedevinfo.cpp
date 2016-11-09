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

/**
 * Fill alias grid
 * \param grid       to fill
 * \param p_noAlias  "Not aliases found" message label, displayed when device has no aliases
 * \param p_device   Display alases from device/partition device
 */

void TFormBaseDevInfo::fillAliases(QTableView *p_view,QLabel *p_noAlias,TDeviceBase *p_device)
{
	if(p_device->getDeviceAlias()->isEmpty()){
		p_view->setVisible(false);
	}else{
		TDeviceAlias *l_alias;
		int l_cnt=0;	
		QStandardItemModel *l_model=new QStandardItemModel(1,2,this);
		l_model->setHorizontalHeaderItem(0,new QStandardItem(i18n("Type")));
		l_model->setHorizontalHeaderItem(1,new QStandardItem(i18n("Alias")));
		TLinkListIterator<TDeviceAlias> l_aliasIter(p_device->getDeviceAlias());
		while(l_aliasIter.hasNext()){
			l_alias=l_aliasIter.next();
			l_model->setItem(l_cnt,0,new QStandardItem(l_alias->getType()));
			l_model->setItem(l_cnt,1,new QStandardItem(l_alias->getAlias()));
			l_cnt++;			
		}
		p_view->setModel(l_model);	
		p_noAlias->setVisible(false);
		p_view->resizeRowsToContents();
		p_view->resizeColumnsToContents();	
	}
	
}

TFormBaseDevInfo::~TFormBaseDevInfo()
{

}

