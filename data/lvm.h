#ifndef __LVM_H__
#define __LVM_H__
#include <QString>
#include "base/stringlineiterator.h"
#include "base/linklist.h"
#include "devicelist.h"
using namespace std;

class TLVMResponseParser{
private:
	QString text;
	QString prefix;
	TStringLineIterator *iter;
public:
	TLVMResponseParser(QString &p_text);
	virtual ~TLVMResponseParser();
	void main(QString &p_code);
	virtual void chapter(QString p_item);
	void parseChapter();
	void section(QString &p_section);
	virtual void setVar(QString &p_name,QString &p_value);
	void parse();
	
};



class TPVInfo{
private:
	QString key;
	int device;
	long long dev_size;
	QString format;
	int label_sector;
	QString id;
	int mdao_ignore;
	int mdao_start;
	long long mdao_size;
	long long mdao_free_sectors;
	long long dao_offset;
	long long dao_size;
	QString vgid;
	QString vgName;
	TDeviceBase *realDevice;
public:
	inline TDeviceBase *getRealDevice(){ return realDevice;}
	inline void setRealDevice(TDeviceBase *p_realDevice){ realDevice=p_realDevice;}
	inline QString getVgId(){ return vgid;}
	inline void setVgId(QString &p_vgid){ vgid=p_vgid;}
	inline QString getVgName(){ return vgName;}
	inline void setVgName(QString &p_vgName){ vgName=p_vgName;}
	inline long long getDaoSize(){ return dao_size;}
	inline void setDaoSize(long long p_daoSize){ dao_size=p_daoSize;}
	inline long long getDaoOffset(){ return dao_offset;}
	inline void setDaoOffset(int p_daoOffset){ dao_offset=p_daoOffset;}
	inline long long getMdaoFreeSectors(){ return mdao_free_sectors;}
	inline void setMdaoFreeSectors(long long p_mdaoFreeSectors){ mdao_free_sectors=p_mdaoFreeSectors;}
	inline long long getMdaoSize(){ return mdao_start;}
	inline void setMdaoSize(long long p_mdaoSize){ mdao_size=p_mdaoSize;}
	inline int getMdaoStart(){ return mdao_start;}
	inline void setMdaoStart(int p_mdaoStart){ mdao_start=p_mdaoStart;}
	inline int getMdaoIgnore(){ return mdao_ignore;}
	inline void setMdaoIgnore(int p_mdaoIgnore){ mdao_ignore=p_mdaoIgnore;}
	inline QString getId(){ return id;}
	inline void setId(QString &p_id){ id=p_id;}
	inline int getLabelSector(){ return label_sector;}
	inline void setLabelSector(int p_labelSector){ label_sector=p_labelSector;}
	inline QString getFormat(){ return format;}
	inline void setFormat(QString &p_format){ format=p_format;}
	inline long getDevSize(){ return dev_size;}
	inline void setDevSize(long long p_devSize){ dev_size=p_devSize;}
	
	inline int getDevice(){ return device;}
	inline void setDevice(int p_device){ device=p_device;}
	inline QString getKey(){ return key;}
	inline void setKey(QString &p_key){ key=p_key;}
};

class TPVParser:public TLVMResponseParser{
private:
	TLinkList<TPVInfo> *items;
	TPVInfo *current;
	TDeviceList *devList;
public:
	TPVParser(TDeviceList *p_devList,QString &p_text);
	virtual void chapter(QString p_item) override;
	virtual void setVar(QString &p_name,QString &p_value) override;
	TLinkList<TPVInfo> *getItems(){ return items;}	

};

class TLVM{
private:
	int readSocket;
	bool hasData();
	bool writeSocket(const char *p_str);
	bool sendMessage(const char *p_message,QString &p_return);

public:
	bool openLVMSocket();	
	TLinkList<TPVInfo> *PvList(TDeviceList *p_devList);
};
#endif
