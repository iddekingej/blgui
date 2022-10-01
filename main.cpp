#include <QCoreApplication>
#include <QApplication>
#ifdef KDE5
#include <QCommandLineParser>
#endif
#include "gui/mainwindow.h"
#include <klocalizedstring.h>
#include <kaboutdata.h>
#include "base/globals.h"
#include <KSharedConfig>
#include <KConfigGroup>
#include "base/version.h"
#include "base/config.h"


int main(int argc, char **argv) {
	
	g_app=new QApplication(argc,argv);
//TODO to KDE4
#ifdef KDE5
	KLocalizedString::setApplicationDomain(PROG_NAME);
	KAboutData l_aboutData(
			PROG_NAME
		,	i18n("Disk information gui")
		,	VERSION
		,	i18n("X")
		,	KAboutLicense::GPL
		,	i18n("(C) 2016..2022")
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
#endif
	g_config.setup();
	TMainWindow *l_main=new TMainWindow();
	l_main->show();
	int l_exit=g_app->exec();
	delete l_main;
	delete g_app;
	return l_exit;
}
