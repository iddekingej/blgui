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

class TVolumeGroup;
class TVolumeGroupList;

class TPhysicalVolume {
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
	TVolumeGroup *volumeGroup;
public:
	inline TVolumeGroup *getVolumeGroup(){ return volumeGroup;}
	inline void setVolumeGroup(TVolumeGroup *p_volumeGroup){ volumeGroup=p_volumeGroup;}
	inline TDeviceBase *getRealDevice(){ return realDevice;}
	inline void setRealDevice(TDeviceBase *p_realDevice){ realDevice=p_realDevice;}
	inline QString &getVgId(){ return vgid;}
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
	   TPhysicalVolume();
};

class TPhysicalVolumeList:public TLinkList<TPhysicalVolume>{
public:
	void processList(TVolumeGroupList *p_lie);
};



class TVolumeGroup;

class TLogicalVolume{
private:
	QString id;
	QString name;
	   TVolumeGroup *volumeGroup;
	TDevice *realDevice;
public:
	inline TDevice *getRealDevice(){ return realDevice;}
	inline void setRealDevice(TDevice *p_device)
	{
		realDevice=p_device;
	}
	inline QString getId(){return id;}
	inline void setId(QString &p_id){id=p_id;}
	inline QString getName(){return name;}
	inline TVolumeGroup *getVolumeGroup(){ return volumeGroup;}
	TLogicalVolume(QString &p_name,TVolumeGroup *p_volumeGroup);
};

class TVolumeGroup {
private:
	QString key;
	QString name;
	TLinkList<TLogicalVolume> logicalVolumns;
public:
	inline void setKey(QString &p_key){ key=p_key;}
	inline QString &getKey(){ return key;}
	inline void setName(QString &p_name){ name=p_name;}
	inline QString &getName(){ return name;}
	inline TLogicalVolume *getLVByName(QString &p_name);
	TLogicalVolume *addLv(QString &p_name);
	TLinkList<TLogicalVolume> *getLogicalVolumns(){ return &logicalVolumns;}
	   TVolumeGroup();
};

class TVolumeGroupList:public TLinkList<TVolumeGroup>{
public:
	TVolumeGroup *getVolumeGroupById(QString &p_name);
	void processInfo(TDeviceList *p_list);
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
	virtual bool chapter(QStringRef &p_item);
	void parseChapter();	
	virtual void setVar(QString &p_name,QString &p_value);
	void parse();
	
};

class TTokenParser:public TLVMResponseParser{
private:
	QString token;	
public:
	TTokenParser(QString &p_text);
	virtual void setVar(QString &p_name,QString &p_value) override;
	inline QString  getToken(){ return token;}
};




class TPVParser:public TLVMResponseParser{
private:
	TPhysicalVolumeList *items;
	TPhysicalVolume *current;
	TDeviceList *devList;
public:
	TPVParser(TDeviceList *p_devList,QString &p_text);
	virtual bool chapter(QStringRef &p_item) override;
	virtual void setVar(QString &p_name,QString &p_value) override;
	TPhysicalVolumeList *getItems(){ return items;}	

};


class TVGMainParser:public TLVMResponseParser{
private:
	TVolumeGroupList *items;
	TVolumeGroup *current;
public:
	TVGMainParser(QString &p_text);
	virtual bool chapter(QStringRef &p_item) override;
	virtual void setVar(QString &p_name,QString &p_value) override;
	TVolumeGroupList *getItems(){ return items;}	

};


class TVGParser:public TLVMResponseParser{
private:
	   TVolumeGroup *current;
	TLogicalVolume *currentLv;
public:
	TVGParser(TVolumeGroup *p_item,QString &p_text);
	virtual bool chapter(QStringRef &p_item) override;
	virtual void setVar(QString &p_name,QString &p_value) override;
};


class TLVMHandler {
private:
	int readSocket;
	bool writeSocket(const char *p_str);
	bool sendMessage(const char *p_message,QString &p_return);
	QString token;
public:
	bool openLVMSocket();	
	void closeLVMSocket();
	void getToken();
	TPhysicalVolumeList *pvList(TDeviceList *p_devList);	
	TVolumeGroupList *vgList();
	TLVMHandler();
	~TLVMHandler();
};


class TLVM{
private:
	TPhysicalVolumeList *pvList;
	TVolumeGroupList    *vgList;
	QString token;
public:
	
	inline TLinkList<TPhysicalVolume> *getPvList(){ return pvList;}
	inline TLinkList<TVolumeGroup> *getVgList(){return vgList;}
	void processInfo(TDeviceList *p_devList);
	TLVM();
	~TLVM();
};

#endif
