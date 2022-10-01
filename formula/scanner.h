#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <QString>

#include "../data/devicebase.h"

enum class TToken:int{
	FIELD
,	INTEGER
,	STRING
,	CHAR
,	FILE_END
,	IDENT
,	COND_EQUAL
,	COND_NE
,	COND_BIGGER
,	COND_SMALLER
,	COND_BE
,	COND_SE
,	COND_UNEUQAL
,	COND_NOT
,	HOOK_L
,	HOOK_R
,	OP_AND
,	OP_OR
,	ERROR
};


enum class TType:int{
	STRING
,	INT
,	UINT
,	BOOLEAN
};


class TScanner
{
private:
	QString condition;
	QString tokenText;
	QString errorText;
	TToken  token=TToken::FILE_END;
	int current=0;
	int lineStart =0;
	int line=0;
	int tokenCol;
	int tokenLine;
	bool parseIdent();
	bool parseString(QChar p_end);
    bool parseInt();
	void skipSpace();
	
public:	
	inline TToken getToken(){ return token;}
	inline int getTokenCol(){ return tokenCol;}
	inline int getTokenLine(){ return tokenLine;}
	inline int getCol(){ return current-lineStart;}
	inline int getLine(){ return line;}
	inline int getCurrent(){return current;}
	inline const QString &getFormula(){ return condition;}
	inline const QString &getTokenText(){ return tokenText;}
	TScanner(const QString &p_condition);
	bool nextToken();
};



#endif
