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
	
/**
 * Read information about user defined tabs.
 * This information is stored as a json string inside the configuration file. This is parsed
 * to a QVariant.
 * 
 * \param  p_tabDef returns the parsed json.  
 */	
void TConfig::getTabDef(QVariant& p_tabDef)
{
	QByteArray l_data=configGui.readEntry("tabdef",QByteArray());
	p_tabDef=QJsonWrapper::parseJson(l_data);
}

/**
 * This method saves the data from the user tab def configuration.
 * The TTabDef (User tab configuration) obect creates a QVariant. This data is
 * covnerted to a json string and save as a string to the configuration file
 * 
 * \param p_tabDef  Definition of the user tabs as a QVariant
 */

void TConfig::setTabDef(QVariant& p_tabDef)
{	
	configGui.writeEntry("tabdef",QJsonWrapper::toJson(p_tabDef));
}

	
/**
 * 
 * Sync needs to be called after a change
 */

void TConfig::sync()
{
	config->sync();
}


/**
 *  "deviceFIelds" configuration contains the configured fields and it's order displayed in the device tab
 * 
 * The list is read as a QVariantList and converted to a QVector.
 * The result QVector[pos]=fieldno
 * 
 * fieldno is the index into the field list defined in  g_deviceFields (globals.cpp)
 */

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

/**
 *   Set enable fields displayed in the device tab
 * 
 *  \param p_list list of fieldno's (Fieldno is the index of the g_deviceFields array )
 */

void TConfig::setDeviceFields(QVariantList p_list)
{
	deviceFields=nullptr;
	configGui.writeEntry("devicefields",p_list);
}

/**
 * Saves the main window size  in the configuration file.
 * When the main window is resized, the size is stored in the configurationa. When the program is restarted
 * the size is estored the last window size.
 * 
 * \param p_width - width of the window
 * \param p_height - height of the window
 */

void TConfig::setMainWindowSize(int p_width, int p_height)
{
	configGui.writeEntry(QStringLiteral("mainWidth"),p_width );
	configGui.writeEntry(QStringLiteral("mainHeight"),p_height);
}
/**
 * get the main window height as saved in the configuration. 
 * See  \see TConfig::setMainWindowSize for more information
 * 
 * \return main window height
 */

int TConfig::getMainWindowHeight()
{
	return configGui.readEntry(QStringLiteral("mainHeight"),-1);
}

/**
 * get the main window width as saved in the configuration. 
 * See   \see TConfig::setMainWindowSize for more information
 * 
 * \return  main window width
 */

int TConfig::getMainWindowWidth()
{
	return configGui.readEntry(QStringLiteral("mainWidth"),-1);
}

/**
 *   Show or hide disktab?
 *   It is possible to hide or show the "disk" tab. This is saved in the configuration
 *   file
 * 
 *   \return true if "disktab"  is visible or else false.
 */

bool TConfig::getDisksTab(){
	return configGui.readEntry(QStringLiteral("diskTab"),true);
}

/**
 *   It is possible to hide or show the "disk" tab. This is saved in the configuration
 *   file. 
 *   This method saves the configuration to the configuration file 
 * 
 *   \param p_flag True if the disk tab is visible or false when hidden.
 */


void TConfig::setdiskTab(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("diskTab"),p_flag);
}


/**
 *   Show or hide raid tab?
 *   It is possible to hide or show the "raid" tab. This is saved in the configuration
 *   file
 * 
 *   \return true if "raid" tab  is visible or else false.
 */

bool TConfig::getRaidTab()
{
	return configGui.readEntry(QStringLiteral("raidTab"),true);
}

/**
 *   It is possible to hide or show the "raid" tab. This is saved in the configuration
 *   file. 
 *   This method saves the configuration to the configuration file 
 * 
 *   \param p_flag True if the raid tab is visible or false when hidden.
 */

void TConfig::setRaidTab(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("raidTab"),p_flag);
}
bool TConfig::getFsTabTab(){
	return configGui.readEntry(QStringLiteral("fsTabTab"),true);
}

/**
 * 
 */

void TConfig::setFsTabTab(bool p_flag){
	configGui.writeEntry(QStringLiteral("fsTabTab"),p_flag);
}

/**
 * Get settings if iscsi tab must be displayed
 * This setting is save by the @see TConfig::setIscsiTab(bool) method
 * 
 * \return True if iscsi tab should be displayed
 */

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

bool TConfig::getShowNotifications()
{
	return configGui.readEntry(QStringLiteral("shownotifications"),true);
}

void TConfig::setShowNotification(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("shownotifications"),p_flag);
}


TConfig g_config;
