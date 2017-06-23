#ifndef __PARSER_H__
#define __PARSER_H__

#include "scanner.h"
#include "node.h"

class TParser
{
private:
	TScanner *scanner;
	
	QString error;
protected:	
	TNode *parseField();
	TNode *parseString();
	TNode *parseSimple();
	TNode *parseExpression();
	TNode *parseCond();
	TNode *parseBO();
	TField getFieldIdByName(const QString& p_name);
public:
	TParser(const QString &p_formula);
	virtual ~TParser();
	inline TScanner *getScanner(){ return scanner;}
	inline QString &getError(){ return error;}
	TNode *parseFormula();
};

#endif
