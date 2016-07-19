#ifndef __ABOUT_H_
#define __ABOUT_H_
#include "gui/about.h"
#include "ui_about.h"
#include <QDialog>
class TAbout:public QDialog
{
private:
	Ui::about ui;
public:
	TAbout();
	
};
#endif