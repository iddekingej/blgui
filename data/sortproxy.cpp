#include "sortproxy.h"


TSortProxy::TSortProxy(QVector<int>* p_fields, QObject* p_parent): QSortFilterProxyModel(p_parent)
{
	fields=p_fields;
}

/**
 *\brief Get the type of sort (numeric or string)  for a certain column
 * 
 * \param p_col  Column index (in @see g_deviceFields array)
 * \return  Type of sort returns TSortType::NUMERIC  for numeric or TSortType::STRING for string.
 */
TSortType TSortProxy::getSortType(int p_col) const
{
	if(p_col>=flexStart && p_col<fields->size()){
		int l_fieldNo=(*fields)[p_col-flexStart];
		if(l_fieldNo>=0 && l_fieldNo < g_numDeviceFields){
			return g_deviceFields[l_fieldNo].sortType;
		}
	}
	return TSortType::STRING ;
}

/**
 *\brief Compares columns for sorting
 * 
 * Used for sorting. Return true when left value < right value   
 * Checks first if column contains a number. If the display value for left and right is a valid number, values a compared as number
 * otherwise the values are compared as string
 * 
 * \param p_left    Model index of left value
 * \param p_right   Model index of right value
 * \return   true when left < right , false otherwise
 * */


bool TSortProxy::lessThan(const QModelIndex& p_left, const QModelIndex &p_right) const
{
	TSortType l_type=getSortType(p_left.column());
	bool l_ok;
	if(l_type==TSortType::NUMERIC){
		long long l_left=p_left.data(Qt::DisplayRole).toLongLong(&l_ok);
		if(l_ok){
			long long  l_right=p_right.data(Qt::DisplayRole).toLongLong(&l_ok);
			if(l_ok){				
				return l_left<l_right;
			}
		}
	}
	return QSortFilterProxyModel::lessThan(p_left,p_right);
}
