#include "visibletabs.h"
#include "base/config.h"

/**
 *  Setup window
 *  The GUI is defined in  visibletabs.ui
 */
TVisibleTabs::TVisibleTabs():QDialog()
{
	ui.setupUi(this);
	connect(ui.pushCancel,SIGNAL(clicked()),this,SLOT(close()));
	connect(ui.pushOk,SIGNAL(clicked()),this,SLOT(okPressed()));
	ui.checkDisk->setCheckState(g_config.getDisksTab()?Qt::Checked:Qt::Unchecked);
	ui.checkFsTab->setCheckState(g_config.getFsTabTab()?Qt::Checked:Qt::Unchecked);
	ui.checkIsci->setCheckState(g_config.getIscsiTab()?Qt::Checked:Qt::Unchecked);
	ui.checkRaid->setCheckState(g_config.getRaidTab()?Qt::Checked:Qt::Unchecked);
	ui.checkStats->setCheckState(g_config.getStatsTab()?Qt::Checked:Qt::Unchecked);
	ui.checkLVM->setCheckState(g_config.getLVMTab()?Qt::Checked:Qt::Unchecked);
}

/**
 *  When ok is pressed settings is saved to the configuration file.
 */
void TVisibleTabs::okPressed()
{	
	g_config.setdiskTab(ui.checkDisk->checkState()==Qt::Checked);
	g_config.setFsTabTab(ui.checkFsTab->checkState()==Qt::Checked);
	g_config.setIscsiTab(ui.checkIsci->checkState()==Qt::Checked);
	g_config.setRaidTab(ui.checkRaid->checkState()==Qt::Checked);
	g_config.setStatsTab(ui.checkStats->checkState()==Qt::Checked);
	g_config.setLVMTab(ui.checkLVM->checkState()==Qt::Checked);
	close();
}

