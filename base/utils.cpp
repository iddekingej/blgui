
#include "utils.h"
#include <QDir>
#include <QTextStream>
#include <QIODevice>

void getReadableSize(TDiskSize p_value,TDiskSize &p_size,char &p_ind)
{
	TDiskSize l_size=p_value;
	char l_ind=' ';
	if(l_size>=1024){
		l_size=l_size/1024;
		l_ind='K';
	}
	if(l_size>=1024){
		l_size=l_size/1024;
		l_ind='M';
	}
	if(l_size>=1024){
		l_size=l_size/1024;
		l_ind='G';
	}
	if(l_size>=1024){
		l_size=l_size/1024;
		l_ind='T';
	}
	p_ind=l_ind;
	p_size=l_size;
}

bool readString(QString p_path,QString p_name,QString &p_return)
{
	bool l_succes;
	QDir l_dir=QDir(p_path);	
	QFile l_file(l_dir.absoluteFilePath(p_name));
	if(!l_file.open(QIODevice::ReadOnly|QIODevice::Text)){
		p_return="";
		return false;
	}
	QTextStream l_stream(&l_file);
	p_return=l_stream.readLine();
	l_succes=(l_stream.status() ==  QTextStream::Ok);
	l_file.close();
	
	return l_succes;
}


bool readLong(QString p_path,QString p_name,unsigned long &p_size)
{
	QString l_string;
	p_size=0;
	if(!readString(p_path,p_name,l_string)) return false;
	p_size=l_string.toULong();
	return true;
}