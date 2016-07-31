#include <QCoreApplication>
#include <QApplication>
#include <QCommandLineParser>
#include "gui/mainwindow.h"
#include <klocalizedstring.h>
#include <kaboutdata.h>
#include "base/globals.h"
#include <KSharedConfig>
#include <KConfigGroup>
void checkConfig()
{

	KSharedConfig::Ptr config=KSharedConfig::openConfig();
	KConfigGroup  l_mainGroup=config->group("main");
	QString l_check=l_mainGroup.readEntry("check");
	if(l_check.length()==0){
		QVariantList l_enableDeviceFields;
		for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
			l_enableDeviceFields.append(l_cnt);
		}
		KConfigGroup  l_fieldsGroup=config->group("enabledfields");
		l_fieldsGroup.writeEntry("devicefields",l_enableDeviceFields);
		l_mainGroup.writeEntry("check","1");
	}

}
int main(int argc, char **argv) {
	
	g_app=new QApplication(argc,argv);
	KLocalizedString::setApplicationDomain("dingui");
	KAboutData l_aboutData(
			"ding"
		,	i18n("Disk information gui")
		,	"0.4.3"
		,	i18n("X")
		,	KAboutLicense::GPL
		,	i18n("(C) 2016")
		,	i18n("x")
		,	QStringLiteral("X")
		,	QStringLiteral("X")
		   );
	l_aboutData.addAuthor(i18n("Jeroen van Iddekinge"),i18n("X"),("iddekingej@lycos.com"));
	KAboutData::setApplicationData(l_aboutData);

	QCommandLineParser l_parser;
	l_parser.addHelpOption();
	l_parser.addVersionOption();
	l_aboutData.setupCommandLine(&l_parser);
	l_parser.process(*g_app);
	l_aboutData.processCommandLine(&l_parser);	
	checkConfig();
	TMainWindow *l_main=new TMainWindow();
	l_main->show();
	int l_exit=g_app->exec();
	delete l_main;
	delete g_app;
	return l_exit;
}