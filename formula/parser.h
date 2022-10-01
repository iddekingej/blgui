#ifndef __PARSER_H__
#define __PARSER_H__

#include "scanner.h"
#include "node.h"

class TParser
{
private:
	TScanner *scanner;
	
	QString error;
	int     errorCol=-1;
	int     errorLine=-1;
    
    qlonglong unitToValue(QChar p_value);
    
	TNode *parseField();
	TNode *parseString();    
    TNode *parseInt();
	TNode *parseSimple();
	TNode *parseExpression();
	TNode *parseCond();
	TNode *parseBO();
	TField getFieldIdByName(const QString& p_name);
	void setError(const QString p_error);
public:
	TParser(const QString &p_formula);
	virtual ~TParser();
	inline TScanner *getScanner(){ return scanner;}
	inline QString &getError(){ return error;}
	TNode *parseFormula();
	void getFullError(QString &p_error);
};

#endif
