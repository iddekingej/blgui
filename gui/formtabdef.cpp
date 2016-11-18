#include "formtabdef.h"
#include "base/globals.h"
#include "data/tabdef.h"
#include "formnewtab.h"
#include "base/utils.h"
#include <QMessageBox>
void TFormTabDef::fillConditionField()
{
	ui.conditionField->addItem("");
	for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
		ui.conditionField->addItem(g_deviceFields[l_cnt]);
	}
}


void TFormTabDef::fillFields()
{
	ui.fieldSelector->clear();
	ui.fieldSelector->addItem("",-1);
	if(current != nullptr){
		for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
			if(!current->hasFieldInSelected(l_cnt))	ui.fieldSelector->addItem(g_deviceFields[l_cnt],l_cnt);
		}	
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

void TFormTabDef::fillSelectedFields()
{
	fieldListModel->clear();
	   QVector<int> *l_fields=current->getSelectedList();
	for(int l_cnt=0;l_cnt<l_fields->size();l_cnt++){
		int l_field=(*l_fields)[l_cnt];
		addFieldToFieldListModel(l_field);
		
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
	fillSelectedFields();
}

void TFormTabDef::formToCurrentTabDef()
{
	if(current != nullptr){
		current->setName(ui.tabLabel->text());
		current->setConditionObject(ui.filterPartition->isChecked()?TT_Partition:TT_Device);
		current->setConditionField(ui.conditionField->currentIndex()-1);
		current->setConditionType((TConditionType)(ui.conditionType->currentIndex()-1));
		current->setConditionValue(ui.conditionValue->text());
		current=nullptr;
		ui.editTabDef->setVisible(false);
	}
}


void TFormTabDef::selectTabDev(const QItemSelection & p_selected, const QItemSelection & p_deselected)
{
	QModelIndex l_index=ui.tabList->currentIndex();
	int l_id=l_index.row();	
	TDoubleLinkedListItem<TTabDef> *l_item=tabDefs->getByPosition(l_id);
	if(l_item != nullptr){
		ui.upDef->setEnabled(l_item->getPrv() != nullptr );
		ui.downDef->setEnabled(l_item->getNext() != nullptr);
		TTabDef *l_def=l_item->getItem();
		if(current != nullptr){
			formToCurrentTabDef();
			tabDefModel->setItem(currentRow,0,new QStandardItem(ui.tabLabel->text()));
		}
		ui.editTabDef->setVisible(true);
		currentRow= l_id;
		fillFormByTabDef(l_def);
		fillFields();
	}

}

void TFormTabDef::saveTabDef()
{
	formToCurrentTabDef();
	tabDefs->save();
	accept();
}


void TFormTabDef::cancelDef()
{	
	tabDefs->clear();
	tabDefs->read();
	reject();
}

TFormTabDef::~TFormTabDef()
{
	delete tabDefModel;
	delete fieldListModel;
}

void TFormTabDef::fillTabDef()
{
	tabDefModel->clear();
	tabDefModel->setRowCount(tabDefs->getLength());
	TDoubleLinkedListIterator<TTabDef> l_iter(tabDefs);
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


void TFormTabDef::refreshList(int p_move)
{
	QModelIndex l_index=ui.tabList->currentIndex();
	int l_row=l_index.row()+p_move;
	fillTabDef();
	QModelIndex l_newIndex=tabDefModel->index(l_row,0);
	ui.tabList->setCurrentIndex(l_newIndex);
}

TDoubleLinkedListItem<TTabDef> * TFormTabDef::getCurrentItem()
{
	QModelIndex l_index=ui.tabList->currentIndex();
	QVariant l_idv=l_index.data(Qt::UserRole+1);
	int l_id=l_idv.toInt();
	TDoubleLinkedListItem<TTabDef> *l_item=tabDefs->getByPosition(l_id);
	return l_item;
}


void TFormTabDef::delDef()
{	
	TDoubleLinkedListItem<TTabDef> *l_item=getCurrentItem();
	if(l_item != nullptr){
		tabDefs->del(l_item);
		refreshList();
		current=nullptr;
	}
}


void TFormTabDef::upDef()
{
	formToCurrentTabDef();
	TDoubleLinkedListItem<TTabDef> *l_item=getCurrentItem();
	if(l_item != nullptr){
		tabDefs->moveDown(l_item);
	}
	refreshList(-1);
}

void TFormTabDef::downDef()
{
	formToCurrentTabDef();
	TDoubleLinkedListItem<TTabDef> *l_item=getCurrentItem();
	if(l_item != nullptr){
		tabDefs->moveUp(l_item);
	}
	refreshList(1);
}

void TFormTabDef::addFieldToFieldListModel(int p_index)
{
	auto l_item=new QStandardItem(g_deviceFields[p_index]);
	l_item->setData(p_index);
	fieldListModel->appendRow(l_item);
}


void TFormTabDef::addField()
{
	QVariant l_userData=ui.fieldSelector->currentData();
	int l_index=l_userData.toInt();
	if(l_index==-1){
		QMessageBox::information(nullptr,i18n("Error"),i18n("Please select a field to add"));
	} else{
		addFieldToFieldListModel(l_index);
		if(current != nullptr){
			current->addSelectedList(l_index);
		}
		fillFields();
	}

}


TFormTabDef::TFormTabDef(TTabDefList *p_list):QDialog()
{
	ui.setupUi(this);
	tabDefModel=new QStandardItemModel(0,1);
	ui.tabList->setModel(tabDefModel);
	fieldListModel=new QStandardItemModel(0,1);
	ui.fieldList->setModel(fieldListModel);
	tabDefs=p_list;	
	current=nullptr;
	fillConditionField();
	fillConditionType();
	fillTabDef();
	connect(ui.conditionType,SIGNAL(currentIndexChanged(int)),this,SLOT(changeConditionType(int)));
	connect(ui.addTab, SIGNAL(clicked()),this,SLOT(newTab()));
	connect(ui.tabList->selectionModel() ,SIGNAL(selectionChanged(const QItemSelection &,const QItemSelection &)),this,SLOT(selectTabDev(const QItemSelection &,const QItemSelection &)));
	connect(ui.okButton,SIGNAL(clicked()),this,SLOT(saveTabDef()));
	connect(ui.cancelButton,SIGNAL(clicked()),this,SLOT(cancelDef()));
	connect(ui.delDef,SIGNAL(clicked()),this,SLOT(delDef()));
	connect(ui.upDef,SIGNAL(clicked()),this,SLOT(upDef()));
	connect(ui.downDef,SIGNAL(clicked()),this,SLOT(downDef()));
	connect(ui.addField,SIGNAL(clicked()),this,SLOT(addField()));
	ui.upDef->setDisabled(true);
	ui.downDef->setDisabled(true);
	ui.conditionValue->setVisible(false);
	ui.editTabDef->setVisible(false);
}
