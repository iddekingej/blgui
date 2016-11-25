#ifndef __LVM_H__
#define __LVM_H__
#include <QString>
#include "base/stringlineiterator.h"
#include "base/linklist.h"
#include "devicelist.h"
using namespace std;

typedef enum{
	st_top
,	st_data
,	st_pv
,	st_vg
,	st_da0
,	st_pvsection
,       st_lvsection
,       st_lv
} TSectionType;


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
	inline void setDaoOffset(long long p_daoOffset){ dao_offset=p_daoOffset;}
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

class TLVMResponseParser{
private:
	QString text;
	QString prefix;
	TStringLineIterator *iter;
protected:
	TSectionType sectionType;
public:
	TLVMResponseParser(QString &p_text);
	virtual ~TLVMResponseParser();
	virtual bool chapter(QString p_item);
	void parseChapter();	
	virtual void setVar(QString &p_name,QString &p_value);
	void parse();
	
};


class TPVParser:public TLVMResponseParser{
private:
	TLinkList<TPVInfo> *items;
	TPVInfo *current;
	TDeviceList *devList;
public:
	TPVParser(TDeviceList *p_devList,QString &p_text);
	virtual bool chapter(QString p_item) override;
	virtual void setVar(QString &p_name,QString &p_value) override;
	TLinkList<TPVInfo> *getItems(){ return items;}	

};

class TVGInfo;

class TLogicalVolume{
private:
	QString id;
	QString name;
	TVGInfo *volumeGroup;
public:
	inline QString getId(){return id;}
	inline void setId(QString p_id){id=p_id;}
	inline QString getName(){return name;}
	inline TVGInfo *getVolumeGroup(){ return volumeGroup;}
	TLogicalVolume(QString &p_name,TVGInfo *p_volumeGroup);
};

class TVGInfo{
private:
	QString key;
	QString name;
	TLinkList<TLogicalVolume> logicalVolumns;
public:
	inline void setKey(QString &p_key){ key=p_key;}
	inline QString &getKey(){ return key;}
	inline void setName(QString &p_name){ name=p_name;}
	inline QString &getName(){ return name;}
	TLogicalVolume *addLv(QString &p_name);
	TLinkList<TLogicalVolume> *getLogicalVolumns(){ return &logicalVolumns;}
	TVGInfo();
};



class TVGMainParser:public TLVMResponseParser{
private:
	TLinkList<TVGInfo> *items;
	TVGInfo *current;
public:
	TVGMainParser(QString &p_text);
	virtual bool chapter(QString p_item) override;
	virtual void setVar(QString &p_name,QString &p_value) override;
	TLinkList<TVGInfo> *getItems(){ return items;}	

};


class TVGParser:public TLVMResponseParser{
private:
	TVGInfo *current;
	TLogicalVolume *currentLv;
public:
	TVGParser(TVGInfo *p_item,QString &p_text);
	virtual bool chapter(QString p_item) override;
	virtual void setVar(QString &p_name,QString &p_value) override;
};


class TLVMHandler {
private:
	int readSocket;
	bool writeSocket(const char *p_str);
	bool sendMessage(const char *p_message,QString &p_return);

public:
	bool openLVMSocket();	
	void closeLVMSocket();
	TLinkList<TPVInfo> *pvList(TDeviceList *p_devList);	
	TLinkList<TVGInfo> *vgList();
	TLVMHandler();
	~TLVMHandler();
};


class TLVM{
private:
	TLinkList<TPVInfo> *pvList;
	TLinkList<TVGInfo> *vgList;
	QHash<QString,TPVInfo *> pvIndexByDevice;
public:
	inline TLinkList<TPVInfo> *getPvList(){ return pvList;}
	inline TPVInfo *getByDevice(QString &p_name){ return pvIndexByDevice.value(p_name);}
	inline TLinkList<TVGInfo> *getVgList(){return vgList;}
	void processInfo(TDeviceList *p_devList);
};

#endif
