#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <KSharedConfig>
#include <KConfigGroup>
#include <KConfig>
#include <QVariantList>
#include <QVector>
#include <QVariant>
/*
 * Singelton to manage configuration
 * the configuration is writeer to bdguirc file in the
 * default kde configuration folder
 */


class TConfig
{
private:
	/**
	 * Configuration data
	 */
	KSharedConfig::Ptr config;
	
	/**
	 *  Configuration section used for configure the gui
	 */
	KConfigGroup configGui;
	
	/**
	 * Cache of fields displayed in the "device tab"
	 */
	QVector<int> *deviceFields=nullptr;
	
public:
	TConfig();
	~TConfig();
	void setup();
	void sync();
	void setDeviceFields(QVariantList p_list);
	QVector<int>* getDeviceFields();
	void getTabDef(QVariant &p_list);
	void setTabDef(QVariant &p_list);
	void setMainWindowSize(int p_width,int p_height);
	int getMainWindowWidth();
	int getMainWindowHeight();
	bool getDisksTab();
	void setdiskTab(bool p_flag);
	bool getRaidTab();
	void setRaidTab(bool p_flag);
	bool getFsTabTab();
	void setFsTabTab(bool p_flag);
	bool getIscsiTab();
	void setIscsiTab(bool p_flag);
	bool getStatsTab();
	void setStatsTab(bool p_flag);
	bool getLVMTab();
	void setLVMTab(bool p_flag);
	bool getDeviceAsTree();
	void setDeviceAsTree(bool p_flag);
	bool getExpandByDefault();
	void setExpandByDefault(bool p_flag);
	bool getShowNotifications();
	void setShowNotification(bool p_flag);
};

extern TConfig g_config;

#endif
