#include "about.h"
TAbout::TAbout(){
	ui.setupUi(this);
	connect(ui.closeButton,SIGNAL(clicked()),this,SLOT(close()));
}