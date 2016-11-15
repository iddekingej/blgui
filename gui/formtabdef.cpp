#include "formtabdef.h"
#include "base/globals.h"


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

TFormTabDef::TFormTabDef():QDialog()
{
	ui.setupUi(this);
	fillConditionField();
	fillConditionType();
	connect(ui.conditionType,SIGNAL(currentIndexChanged(int)),this,SLOT(changeConditionType(int)));
	ui.conditionValue->setVisible(false);
}
