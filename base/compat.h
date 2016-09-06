#ifndef __COMPAT_H_
#define __COMPAT_H_
#include <QStringList>
#ifndef  QStringLiteral
#define QStringLiteral(p_a) (p_a)
#endif

#ifdef kde4
operator <<(QStringList &p_list,const QString &p_string)
{
	p_list.push_back(p_string);
	return p_list;
}
#endif




#endif
