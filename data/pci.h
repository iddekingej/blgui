#ifndef __PCI_H__
#define __PCI_H__
#include <QString>
#include <QHash>
class TPCIInfo
{
private:
	QHash<QString,QString> scsiToPciIndex;
	void processBus(QString p_path,QString p_pciBus);
	void processAta(QString p_path,QString p_pciBus);
	void processHost(QString p_path,QString p_pciBus);	
	void processTarget(QString p_path,QString p_pciBus);	
public:
	
	bool getPciBus(QString &p_scsibus,QString &p_pciBus);
	void readInfo();	

};

#endif