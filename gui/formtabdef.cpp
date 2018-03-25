#include "formtabdef.h"
#include "base/globals.h"
#include "data/tabdef.h"
#include "formnewtab.h"
#include "base/utils.h"
#include "formula/parser.h"
#include <iostream>
#include <QMessageBox>
#include <klocalizedstring.h>
#include <QSortFilterProxyModel>
#include <QSortFilterProxyModel>
#include <QSortFilterProxyModel>
void TFormTabDef::fillConditionField()
{
	ui.conditionField->addItem("");
	for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
		ui.conditionField->addItem(g_deviceFields[l_cnt].title);
	}
}

/**
 * Fill extendedFields list. This is a list of field available for there
 * extended condition
 */
void TFormTabDef::fillExtendedFields()
{
	ui.extendedFields->addItem("");
	for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
		ui.extendedFields->addItem(g_deviceFields[l_cnt].fieldName);
	}
}

/** This method fills condition type combo box with options
 * 
 */
void TFormTabDef::fillConditionType()
{
	ui.conditionType->addItem(i18n(""));
	ui.conditionType->addItem(i18n("Is empty"));
	ui.conditionType->addItem(i18n("Is not empty"));
	ui.conditionType->addItem(i18n("Has value"));
}




void TFormTabDef::changeConditionType(int p_index)
{
	ui.conditionValue->setVisible(p_index==3);
}

/** Event handler when  "new tab def" button is pressed. 
 *  The user enters a new label and a new tab def object is added to the list with defined tab defs.
 */
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
		int l_rc=tabDefModel->rowCount();
		ui.tabList->setCurrentIndex(tabDefModel->index(l_rc-1,0));		
	}
	
}

/**
 *  Fill list with available fields (which can be added to the grid).
 *  Only fields that aren't selected yet are added.
 * 
 */

void TFormTabDef::fillFields()
{
	ui.fieldSelector->clear();	
	ui.fieldSelector->model()->sort(-1);
	ui.fieldSelector->addItem("",-1);
	int l_idx=1;
	if(current != nullptr){
		for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
			if(!current->hasFieldInSelected(l_cnt)){
				ui.fieldSelector->addItem(g_deviceFields[l_cnt].title,l_cnt);
				l_idx++;
			}
		}	
		ui.fieldSelector->model()->sort(0);
	}

}
/**
 *  Near the "available field" listbox there is a "+" button. When pressing this button, the selected index is 
 *  added to the list.
 */

void TFormTabDef::addField()
{
	QVariant l_userData=ui.fieldSelector->itemData(ui.fieldSelector->currentIndex());
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


/** 
 * Add the selected fields (The fields displayed in the grid) from the selected tab def.
 */

void TFormTabDef::fillSelectedFields()
{
	fieldListModel->clear();
	QVector<int> *l_fields=current->getSelectedList();
	for(int l_cnt=0;l_cnt<l_fields->size();l_cnt++){
		int l_field=(*l_fields)[l_cnt];
		addFieldToFieldListModel(l_field);
		
	}
	
}

/** Fills tab def list widget from list with defined tab defs
 * \param p_def -List with defined tab defs  (read from configuration file)
 */

void TFormTabDef::fillFormByTabDef(TTabDef* p_def)
{
	current=p_def;
	ui.tabLabel->setText(p_def->getName());
	if(p_def->getConditionObject()==TObjectType::TT_Partition){
		ui.filterPartition->setChecked(true);
	} else if(p_def->getConditionObject()==TObjectType::TT_Device) {
		ui.filterDevice->setChecked(true);
	} else {
		ui.filterBoth->setChecked(true);
	}	
	ui.conditionField->setCurrentIndex(p_def->getConditionField()+1);
	ui.conditionValue->setText(p_def->getConditionValue());
	ui.conditionType->setCurrentIndex((int)(p_def->getConditionType())+1);	
	ui.isactive->setCheckState(p_def->getIsActive()?Qt::Checked:Qt::Unchecked);
	ui.extendedCondition->setPlainText(p_def->getExtendedCondition());
	ui.useExtendedCondition->setCheckState(p_def->getUseExtendedCondition()?Qt::Checked:Qt::Unchecked);
	ui.typeSelection->setCurrentIndex(static_cast<int>(p_def->getTabType()));
	toggleUseExtended(p_def->getUseExtendedCondition());
	fillSelectedFields();
}
/**
 * Updates tabdef object with data from form (saves data in object).
 */
void TFormTabDef::formToCurrentTabDef()
{
	if(current != nullptr){
		current->setName(ui.tabLabel->text());
		TObjectType l_type=TObjectType::TT_Partition;
		if(ui.filterDevice->isChecked()){
			l_type=TObjectType::TT_Device;
		} else if(ui.filterBoth->isChecked()){
			l_type=TObjectType::TT_Both;
		}
		current->setConditionObject(l_type);
		current->setConditionField(ui.conditionField->currentIndex()-1);
		current->setConditionType((TConditionType)(ui.conditionType->currentIndex()-1));
		current->setConditionValue(ui.conditionValue->text());
		current->setIsActive(ui.isactive->checkState()==Qt::Checked);
		current->setExendedCondition(ui.extendedCondition->toPlainText());
		current->setUseExtendedCondition(ui.useExtendedCondition->checkState()==Qt::Checked);
		current->setTabType(static_cast<TTabType>(ui.typeSelection->currentIndex()));
		current=nullptr;
		ui.editTabDef->setVisible(false);
		ui.delField->setDisabled(false);
	}
}

/**If tab is selected, this method  fills the form with tab definition
 * \param p_selected - UNUSED
 * \param p_deselected - UNUSED
 */

void TFormTabDef::selectTabDev(UNUSEDPAR const QItemSelection & p_selected,UNUSEDPAR const QItemSelection & p_deselected)
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
		ui.delField->setDisabled(true);
		ui.upField->setEnabled(false);
		ui.downField->setEnabled(false);
		if(current->getUseExtendedCondition()){
			checkExtendedCondition();
		} else {
			setExtendedConditionError("");
		}
		
	}

}

/** 
 * Save tab definition in configuration file
 * 
 */
void TFormTabDef::saveTabDef()
{
	formToCurrentTabDef();
	tabDefs->save();
	accept();
}

/** 
 * Cancel dialog. Reread current configuration file
 * 
 */

void TFormTabDef::cancelDef()
{	
	tabDefs->clear();
	tabDefs->read();
	reject();
}

void TFormTabDef::closeEvent(QCloseEvent* p_event)
{
	tabDefs->clear();
	tabDefs->read();
	p_event->accept();
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
		ui.editTabDef->setVisible(false);
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
	auto l_item=new QStandardItem(g_deviceFields[p_index].title);
	l_item->setData(p_index);
	fieldListModel->appendRow(l_item);
}


void TFormTabDef::selectField(UNUSEDPAR const QItemSelection& p_selected,UNUSEDPAR const QItemSelection& p_deselected)
{
	ui.delField->setEnabled(true);
	QModelIndex l_index=ui.fieldList->currentIndex();
	int l_row=l_index.row();
	ui.upField->setEnabled(l_row>0);
	ui.downField->setEnabled(l_row+1<fieldListModel->rowCount());
}




void TFormTabDef::delField()
{
	QModelIndex l_index=ui.fieldList->currentIndex();
	if(l_index.isValid() && current != nullptr){
		int l_row=l_index.row();
		current->getSelectedList()->remove(l_row);
		fieldListModel->removeRow(l_row);
		if(fieldListModel->rowCount()==0) ui.delField->setEnabled(false);
		fillFields();
	}
}

void TFormTabDef::moveField(int p_dir)
{
	QModelIndex l_index=ui.fieldList->currentIndex();
	if(l_index.isValid() && current != nullptr){
		int l_row=l_index.row();
		int l_newRow=l_row+p_dir;
		if(l_newRow>=0 && l_newRow < fieldListModel->rowCount()){
			QVector<int> *l_list=current->getSelectedList();
			
			int l_item1=(*l_list)[l_row];
			int l_item2=(*l_list)[l_newRow];
			(*l_list)[l_row]=l_item2;
			(*l_list)[l_newRow]=l_item1;
			QStandardItem *l_item=new QStandardItem(g_deviceFields[l_item1].title);
			l_item->setData(l_item1);
			fieldListModel->setItem(l_newRow,0,l_item);
			l_item=new QStandardItem(g_deviceFields[l_item2].title);
			l_item->setData(l_item2);
			fieldListModel->setItem(l_row,0,l_item);
			ui.fieldList->setCurrentIndex(fieldListModel->index(l_newRow,0));
			
		}
		
	}
}


void TFormTabDef::downField()
{
	moveField(1);
}
void TFormTabDef::upField()
{
	moveField(-1);
}

void TFormTabDef::extendedFieldChanged(UNUSEDPAR int p_index)
{
	if(!ui.extendedFields->currentText().isEmpty()){
		QString l_text=ui.extendedFields->currentText()+" ";
		ui.extendedCondition->insertPlainText(l_text);
		ui.extendedCondition->setFocus();		
		QTextCursor l_cursor=ui.extendedCondition->textCursor();
		l_cursor.setPosition(l_cursor.position()+l_text.length());		
	}
}


void TFormTabDef::extendedConditionChanged()
{
	checkExtendedCondition();
}

void TFormTabDef::checkExtendedCondition()
{	
	TParser l_parser(ui.extendedCondition->toPlainText());
	TNode *l_node=l_parser.parseFormula();
	if(l_node != nullptr){
		delete l_node;
	}
	QString l_error;
	l_parser.getFullError(l_error);
	setExtendedConditionError(l_error);
	
}


void TFormTabDef::setExtendedConditionError(QString p_error)
{
	ui.errLabel->setVisible(p_error.length()>0);
	ui.errLabel->setText(p_error);
}


void TFormTabDef::checkUseExtended()
{
	toggleUseExtended(ui.useExtendedCondition->checkState() == Qt::Checked);
}

void TFormTabDef::toggleUseExtended(bool p_flag)
{
	ui.extendedContainer->setVisible(p_flag);
	ui.errLabel->setVisible(p_flag && !ui.errLabel->text().isEmpty());
	ui.simpleCondition->setVisible(!p_flag);
}


void TFormTabDef::tabTypeChanged(int p_index)
{
	ui.userDefinition->setVisible(0==p_index);
}


TFormTabDef::TFormTabDef(TTabDefList *p_list):QDialog()
{
	ui.setupUi(this);
	tabDefModel=new QStandardItemModel(0,1);
	ui.tabList->setModel(tabDefModel);
	
	fieldListModel=new QStandardItemModel(0,1);
	ui.fieldList->setModel(fieldListModel);
//For sorting field selection combobox	
	QSortFilterProxyModel *l_proxy=new QSortFilterProxyModel(ui.fieldSelector);
	l_proxy->setSourceModel(ui.fieldSelector->model());
	ui.fieldSelector->model()->setParent(l_proxy);
	ui.fieldSelector->setModel(l_proxy);
	l_proxy->setSortCaseSensitivity(Qt::CaseInsensitive );
	tabDefs=p_list;	
	current=nullptr;
	fillExtendedFields();
	fillConditionField();
	fillConditionType();
	fillTabDef();
	connect(ui.conditionType,SIGNAL(currentIndexChanged(int)),this,SLOT(changeConditionType(int)));
	connect(ui.addTab, SIGNAL(clicked()),this,SLOT(newTab()));
	connect(ui.tabList->selectionModel() ,SIGNAL(selectionChanged(const QItemSelection &,const QItemSelection &)),this,SLOT(selectTabDev(const QItemSelection &,const QItemSelection &)));
	connect(ui.fieldList->selectionModel(),SIGNAL(selectionChanged(const QItemSelection &,const QItemSelection &)),this,SLOT(selectField(const QItemSelection &,const QItemSelection &)));
	connect(ui.okButton,SIGNAL(clicked()),this,SLOT(saveTabDef()));
	connect(ui.cancelButton,SIGNAL(clicked()),this,SLOT(cancelDef()));
	connect(ui.delDef,SIGNAL(clicked()),this,SLOT(delDef()));
	connect(ui.upDef,SIGNAL(clicked()),this,SLOT(upDef()));
	connect(ui.downDef,SIGNAL(clicked()),this,SLOT(downDef()));
	connect(ui.addField,SIGNAL(clicked()),this,SLOT(addField()));
	connect(ui.delField,SIGNAL(clicked()),this,SLOT(delField()));
	connect(ui.upField,SIGNAL(clicked()),this,SLOT(upField()));
	connect(ui.downField,SIGNAL(clicked()),this,SLOT(downField()));
	connect(ui.useExtendedCondition,SIGNAL(clicked()),this,SLOT(checkUseExtended()));
	connect(ui.extendedCondition,SIGNAL(textChanged()),this,SLOT(extendedConditionChanged()) );
	connect(ui.extendedFields,SIGNAL(currentIndexChanged(int)),this,SLOT(extendedFieldChanged(int)));
	connect(ui.typeSelection,SIGNAL(currentIndexChanged(int)),this,SLOT(tabTypeChanged(int)));
	ui.upDef->setDisabled(true);
	ui.downDef->setDisabled(true);
	ui.conditionValue->setVisible(false);
	ui.editTabDef->setVisible(false);
	ui.upField->setEnabled(false);
	ui.downField->setEnabled(false);
	ui.errLabel->setVisible(false);
	ui.errLabel->setText("");
	ui.typeSelection->addItem(i18n("Disks"));
	ui.typeSelection->addItem(i18n("Raid"));
	ui.typeSelection->addItem(i18n("Fstab"));
	ui.typeSelection->addItem(i18n("Iscsi"));
	ui.typeSelection->addItem(i18n("Stats"));
	ui.typeSelection->addItem(i18n("LVM"));
}
