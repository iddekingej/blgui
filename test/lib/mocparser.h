#ifndef __MOCPARSER_H__
#define __MOCPARSER_H__
#include "formula/parser.h"
class TMOCParser:public TParser
{
public:
	TField getFieldIdByName(const QString& p_name){
		return TParser::getFieldIdByName(p_name);
	}

	TMOCParser(const QString &p_code):TParser(p_code){};
};
#endif
