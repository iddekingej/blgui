#include "formtabdef.h"
#include "base/globals.h"
#include "data/tabdef.h"
#include "formnewtab.h"
#include "base/utils.h"
void TFormTabDef::fillConditionField()
{
	ui.conditionField->addItem("");
	for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
		ui.conditionField->addItem(g_deviceFields[l_cnt]);
	}
}

void TFormTabDef::fillConditionType()
{
	ui.conditionType->addItem("");
	ui.conditionType->addItem("Is empty");
	ui.conditionType->addItem("Is not empty");
	ui.conditionType->addItem("Has value");
}

void TFormTabDef::changeConditionType(int p_index)
{
	ui.conditionValue->setVisible(p_index==3);
}

void TFormTabDef::newTab()
{
	TFormNewTab l_form("");
	if(l_form.exec()==QDialog::Accepted){
		QString l_name=l_form.getTabName();
		int l_id=tabDefs->getLength();
		tabDefs->createTabDef(l_name);
		QStandardItem *l_si=new QStandardItem(l_name);
		l_si->setData(l_id);
		tabDefModel->appendRow(l_si);		
	}
	
}

void TFormTabDef::fillFormByTabDef(TTabDef* p_def)
{
	current=p_def;
	ui.tabLabel->setText(p_def->getName());
	if(p_def->getConditionObject()==TT_Partition){
		ui.filterPartition->setChecked(true);
	} else {
		ui.filterDevice->setChecked(true);
	}	
	ui.conditionField->setCurrentIndex(p_def->getConditionField()+1);
	ui.conditionValue->setText(p_def->getConditionValue());
	ui.conditionType->setCurrentIndex((int)(p_def->getConditionType())+1);
}

void TFormTabDef::formToCurrentTabDef()
{
	if(current != nullptr){
		current->setName(ui.tabLabel->text());
		current->setConditionObject(ui.filterPartition->isChecked()?TT_Partition:TT_Device);
		current->setConditionField(ui.conditionField->currentIndex()-1);
		current->setConditionType((TConditionType)(ui.conditionType->currentIndex()-1));
		current->setConditionValue(ui.conditionValue->text());
		
	}
}


void TFormTabDef::selectTabDev(QModelIndex p_index)
{
	QVariant l_idv=p_index.data(Qt::UserRole+1);
	int l_id=l_idv.toInt();
	TTabDef *l_def=tabDefs->getByPosition(l_id);
	if(current != nullptr){
		formToCurrentTabDef();
		tabDefModel->setItem(currentRow,0,new QStandardItem(ui.tabLabel->text()));
	}
	currentRow=p_index.row();
	if(l_def != nullptr) fillFormByTabDef(l_def);

}

void TFormTabDef::saveTabDef()
{
	formToCurrentTabDef();
	tabDefs->save();
	accept();
}

TFormTabDef::~TFormTabDef()
{
	delete tabDefModel;
}

void TFormTabDef::fillTabDef()
{
	tabDefModel->clear();
	tabDefModel->setRowCount(tabDefs->getLength());
	TLinkListIterator<TTabDef> l_iter(tabDefs);
	int l_cnt=0;
	QStandardItem *l_item;
	TTabDef *l_def;
	while(l_iter.hasNext()){
		l_def=l_iter.next();
		l_item =new QStandardItem(l_def->getName());
		l_item->setData(l_cnt);
		tabDefModel->setItem(l_cnt,0,l_item);
		l_cnt++;
	}
}


void TFormTabDef::refreshList()
{
	fillTabDef();
	
}


TFormTabDef::TFormTabDef(TTabDefList *p_list):QDialog()
{
	ui.setupUi(this);
	tabDefModel=new QStandardItemModel(0,1);
	ui.tabList->setModel(tabDefModel);

	tabDefs=p_list;	
	current=nullptr;
	fillConditionField();
	fillConditionType();
	fillTabDef();
	connect(ui.conditionType,SIGNAL(currentIndexChanged(int)),this,SLOT(changeConditionType(int)));
	connect(ui.addTab, SIGNAL(clicked()),this,SLOT(newTab()));
	connect(ui.tabList,SIGNAL(clicked(QModelIndex)),this,SLOT(selectTabDev(QModelIndex)));
	connect(ui.okButton,SIGNAL(clicked()),this,SLOT(saveTabDef()));
	ui.conditionValue->setVisible(false);
}
