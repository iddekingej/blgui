#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <KSharedConfig>
#include <KConfigGroup>
#include <KConfig>
#include <QVariantList>
/*
 * Singelton to manage configuration
 */


class TConfig
{
private:
	KSharedConfig::Ptr config;
	KConfigGroup configGui;
	
public:
	TConfig();
	void setup();
	void sync();
	void setDeviceFields(QVariantList p_list);
	QVariantList getDeviceFields();
	void setMainWindowSize(int p_width,int p_height);
	int getMainWindowWidth();
	int getMainWindowHeight();
};

extern TConfig g_config;

#endif