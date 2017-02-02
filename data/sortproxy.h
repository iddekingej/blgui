#ifndef __SORTPROXY_H_
#define __SORTPROXY_H_
#include <QSortFilterProxyModel>
#include <QVector>
#include <QModelIndex>

/**
 * Proxy model for sorting the  device fields
 * 
 */

class TSortProxy:public QSortFilterProxyModel
{
private:
	/**
	 * List of fields in list
	 */
	QVector<int> *fields;
	/**
	 * Start of flexible part
	 */
	int  flexStart=0;
	char getSortType(int p_col) const;
protected:
	virtual bool lessThan(const QModelIndex &p_left,const QModelIndex &p_right) const override;
public:
	void setFlexStart(int p_flexStart){ flexStart=p_flexStart;}
	int getFlexStart(){ return flexStart;};
	TSortProxy(QVector<int> *p_fields,QObject *p_parent);
};

#endif