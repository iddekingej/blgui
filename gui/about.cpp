/*
 * About.cpp
 * Information about program
 */
#include "about.h"
#include "base/version.h"
TAbout::TAbout(){
	ui.setupUi(this);
	connect(ui.closeButton,SIGNAL(clicked()),this,SLOT(close()));
	ui.versionLabel->setText(VERSION);
}