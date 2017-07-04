#include "config.h"
#include "globals.h"
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

/**
 *  Save if the iscsi disk tab is visible in the configuration file
 * 
 * \param p_flag Flag indicating if iscsi tab is visible 
 */

void TConfig::setIscsiTab(bool p_flag){
	configGui.writeEntry(QStringLiteral("iscsiTab"),p_flag);
}

/**
 * The "Stats" tab can be set hidden or set visible. This is saved in the 
 * configuration file.
 * This routine reads the "statsTab" configuration entry.
 * @see setStatsTab()
 * 
 * \return True if the disk stats is visible, false it is hidden
 * 
 */

bool TConfig::getStatsTab()
{
	return configGui.readEntry(QStringLiteral("statsTab"),true);
}

/**
 * Save the flag if the stats tab is visible in the configuration file
 * 
 * \param p_flag  True if stats tab is visible and false when hidden.
 */

void TConfig::setStatsTab(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("statsTab"),p_flag);
}

/**
 *  The "LVM" tab can be set hidden or visible. This is saved in the
 *  configuration file.
 *  This rotine reads the "lvmTab" configuration value.
 * 
 * \return true  - Lvm tab is visible
 *         false - Lvm tab is hidden 
 */

bool TConfig::getLVMTab()
{
	return configGui.readEntry(QStringLiteral("lvmTab"),true);
}

/**
 * Save the flag if the LVM tab is displayed or hidden in the configuration file
 * 
 * \param p_flag true :LVM tab is visible and when false it is hidden.
 */

void TConfig::setLVMTab(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("lvmTab"),p_flag);
}

/**
 *  The device grid can be displayed as a tree (First device and then partition)
 *  or as a linear list (device and partition are in one list)
 *  This method reads the "devicetree" configuration value.
 *  This value is set by @see  void TConfig::setDeviceAsTree()
 * 
 * \return  true  - device grid is displayed as a tree
 *          false - device grid is displayed as a list
 */
bool TConfig::getDeviceAsTree()
{
	return configGui.readEntry(QStringLiteral("devicetree"),true);
}

/**
 *  Save the flag if the device grid is displayed as a tree or as a list
 *  The value is read by @See TConfig::getDeviceAsTree()
 * 
 *  \param p_flag  true  - device list is displayed as a tree
 *                 false - device list is displayed as list
 */

void TConfig::setDeviceAsTree(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("devicetree"),p_flag);
}

/**
 *  When the device tab is displayed as a tree, it is possible to auto expand the tree
 *  This method reads 'expanddefault' 
 *  This value is ignored then the devicelist is displayed as a list (devicetree=false)
 * 
 *  \return  true - expand tree by default
 *           false - Tree is collapse  by default
 */

bool TConfig::getExpandByDefault()
{
	return configGui.readEntry(QStringLiteral("expanddefault"),true);
}


/**
 *  When the device tab is displayed as a tree, it is possible to auto expand the tree
 *  This method saves the expand tree flag.
 *  This value is read by  @see  TConfig::getExpandByDefault()
 * 
 *  \param p_expand true  expand tree by default , false: tree is collapsed by default.
 */

void TConfig::setExpandByDefault(bool p_expand)
{
	configGui.writeEntry(QStringLiteral("expanddefault"),p_expand);
}

/**
 * When  a device is mounted, removed or added there is a notification on the top of the main window.
 * This notification can be enabled or hidden by a configuration setting "shownotifications".
 * 
 * \return  true - show show notifications 
 *          false - don't show notifications
 */

bool TConfig::getShowNotifications()
{
	return configGui.readEntry(QStringLiteral("shownotifications"),true);
}

/**
 * The setting for displaying notifications a save with this method.
 * See also @see TConfig::getShowNotifications
 * 
 * \param p_flag True when the notification is display, false when hidden.
 */

void TConfig::setShowNotification(bool p_flag)
{
	configGui.writeEntry(QStringLiteral("shownotifications"),p_flag);
}


TConfig g_config;
