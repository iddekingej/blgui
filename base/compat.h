#ifndef __COMPAT_H_
#define __COMPAT_H_
#include <QStringList>
#include <QString>
#ifndef  QStringLiteral
#define QStringLiteral(p_a) (p_a)
#endif

#if QT_VERSION >= QT_VERSION_CHECK( 5, 0, 0 )

#define QSTRINGREF QStringRef
#define QREFTOSTRING(p_a) (p_a.toString())
#define QREFADAPT(p_a) (p_a)

#else
/*
operator bool <<(QStringList &p_list,const QString &p_string)
{
	p_list.push_back(p_string);
	return p_list;
}

*/
#define QSTRINGREF QString
#define QREFTOSTRING(p_a) (p_a)
#define QREFADAPT(p_a) (p_a.toString())
#endif

#endif
