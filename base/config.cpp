#include "config.h"
#include "globals.h"
#include "compat.h"
#include "utils.h"
#include "qjsonwrapper/Json.h"
#include <QVariant>

TConfig::TConfig()
{
}

TConfig::~TConfig()
{
	if(deviceFields != nullptr) delete deviceFields;
}


/* Initialize config =>called in main after setting up QApplication*/
void TConfig::setup()
{
	config=KSharedConfig::openConfig();
	configGui=config->group("gui");
	KConfigGroup  l_mainGroup=config->group("main");
	QString l_check=l_mainGroup.readEntry("check");
	if(l_check.length()==0){
		QVariantList l_enableDeviceFields;
		for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
			l_enableDeviceFields.append(l_cnt);
		}
		setDeviceFields(l_enableDeviceFields);
		l_mainGroup.writeEntry("check","1");
		config->sync();
	}

}
	
void TConfig::getTabDef(QVariant& p_list)
{
	QByteArray l_data=configGui.readEntry("tabdef",QByteArray());
	p_list=QJsonWrapper::parseJson(l_data);
}

void TConfig::setTabDef(QVariant& p_list)
{	
	configGui.writeEntry("tabdef",QJsonWrapper::toJson(p_list));
}

	
//Sync needs to be called after a change
void TConfig::sync()
{
	config->sync();
}

// Return QVariant list with enabled fields=>is integer
QVector<int>* TConfig::getDeviceFields()
{
	if(deviceFields==nullptr){
		
		QVariantList l_list=configGui.readEntry("devicefields",QVariantList());
		deviceFields=new QVector<int>(l_list.size());
		QListIterator<QVariant> l_iter(l_list);
		int l_cnt=0;
		while(l_iter.hasNext()){
			(*deviceFields)[l_cnt]=l_iter.next().toInt();
			l_cnt++;
		}
	}
	return deviceFields;
}

//Set enabled fields in device list
void TConfig::setDeviceFields(QVariantList p_list)
{
	deviceFields=nullptr;
	configGui.writeEntry("devicefields",p_list);
}

//Set mainw window size in config.  is called from mainwindow.resize

void TConfig::setMainWindowSize(int p_width, int p_height)
{
	configGui.writeEntry(QStringLiteral("mainWidth"),p_width );
	configGui.writeEntry(QStringLiteral("mainHeight"),p_height);
}
//Get Mainwindow height as defined in config. Return=-1 when not set

int TConfig::getMainWindowHeight()
{
	return configGui.readEntry(QStringLiteral("mainHeight"),-1);
}

//Get mainwindow height as set in config. Return=-1 when not set
int TConfig::getMainWindowWidth()
{
	return configGui.readEntry(QStringLiteral("mainWidth"),-1);
}

bool TConfig::getDisksTab(){
	return configGui.readEntry(QStringLiteral("diskTab"),true);
}
void TConfig::setdiskTab(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("diskTab"),p_flag);
}

bool TConfig::getRaidTab()
{
	return configGui.readEntry(QStringLiteral("raidTab"),true);
}

void TConfig::setRaidTab(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("raidTab"),p_flag);
}
bool TConfig::getFsTabTab(){
	return configGui.readEntry(QStringLiteral("fsTabTab"),true);
}

void TConfig::setFsTabTab(bool p_flag){
	configGui.writeEntry(QStringLiteral("fsTabTab"),p_flag);
}
bool TConfig::getIscsiTab(){
	return configGui.readEntry(QStringLiteral("iscsiTab"),true);	
}
void TConfig::setIscsiTab(bool p_flag){
	configGui.writeEntry(QStringLiteral("iscsiTab"),p_flag);
}

bool TConfig::getStatsTab()
{
	return configGui.readEntry(QStringLiteral("statsTab"),true);
}




void TConfig::setStatsTab(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("statsTab"),p_flag);
}

bool TConfig::getLVMTab()
{
	return configGui.readEntry(QStringLiteral("lvmTab"),true);
}

void TConfig::setLVMTab(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("lvmTab"),p_flag);
}


bool TConfig::getDeviceAsTree()
{
	return configGui.readEntry(QStringLiteral("devicetree"),true);
}

void TConfig::setDeviceAsTree(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("devicetree"),p_flag);
}

bool TConfig::getExpandByDefault()
{
	return configGui.readEntry(QStringLiteral("expanddefault"),true);
}

void TConfig::setExpandByDefault(bool p_expand)
{
	configGui.writeEntry(QStringLiteral("expanddefault"),p_expand);
}


TConfig g_config;
