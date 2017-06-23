
#include "parser.h"
#include "node.h"
#include "base/globals.h"
#include <QString>

TNode *TParser::parseField()
{
	TField l_no=getFieldIdByName(scanner->getTokenText());
	if(TField::NOTFOUND == l_no){
		error = QStringLiteral("Unknown field :'%1'").arg(scanner->getTokenText());
		return nullptr;
	}
	TFieldNode *l_node=new TFieldNode(l_no);
	scanner->nextToken();
	return l_node;
	
}

TNode *TParser::parseString()
{

	TNode *l_node=new TValueNode<QString>(scanner->getTokenText());
	scanner->nextToken();
	return l_node;
}

TNode * TParser::parseSimple()
{
	TToken l_token=scanner->getToken();
	if(l_token==TToken::IDENT){
		return parseField();
	} else if (l_token==TToken::STRING){
		return parseString();
	} else if(l_token==TToken::HOOK_L){
		TNode *l_node=parseExpression();
		if(scanner->getToken() != TToken::HOOK_R){
			error="')' expected";
			delete l_node;
			return nullptr;
		}
		scanner->nextToken();
		return l_node;
	} else {
		
		//TODO Ident or "(" expected		
		error=QStringLiteral("'%1' found but Identifier, string constant or '(' expected").arg(scanner->getTokenText());;
		return nullptr;
	}
}

TNode * TParser::parseCond()
{
	TNode *l_left;
	TNode *l_right;
	TToken l_token;
	
	l_left=parseSimple();
	if(l_left==nullptr){
		return l_left;
	}
	l_token=scanner->getToken();
	switch(l_token){
		case TToken::COND_BIGGER:
		case TToken::COND_BE:
		case TToken::COND_SMALLER:
		case TToken::COND_SE:
		case TToken::COND_EQUAL:
		case TToken::COND_NE:
			scanner->nextToken();

			l_right=parseSimple();			
			if(l_right==nullptr){
				delete l_left;
				return nullptr;
			}
			return new TDualOperatorNode(l_token,l_left,l_right);
			
		default:
			return l_left;
	}
}

TNode * TParser::parseBO()
{
	TNode *l_left;
	TNode *l_right;
	TToken l_token;
	
	l_left=parseCond();
	if(l_left==nullptr){
		return l_left;
	}
	l_token=scanner->getToken();
	
	switch(l_token){
		case TToken::OP_AND:
		case TToken::OP_OR:
			scanner->nextToken();
			l_right=parseCond();
			
			if(l_right==nullptr){
				delete l_left;
				return nullptr;
			}
			return new TDualOperatorNode(l_token,l_left,l_right);
			
		default:
			return l_left;
	}
}



TNode * TParser::parseExpression()
{
	return parseBO();
}


TNode *TParser::parseFormula()
{
	scanner->nextToken();
	TNode *l_node=parseExpression();
	
	if(scanner->getToken() != TToken::FILE_END && ""==error){
		error="EOF expected but '"+scanner->getTokenText()+"' found";
	}
	return l_node;
}

TParser::TParser(const QString& p_formula)
{
	scanner=new TScanner(p_formula);
}

TParser::~TParser()
{
	if(scanner != nullptr) delete scanner;
}

TField TParser::getFieldIdByName(const QString& p_name)
{
	if(p_name=="device_name"){
		return TField::DEVICE_NAME;
	} else if(p_name=="partition_name"){
		return TField::PARTITION_NAME;
	}
	for(int l_cnt=0;l_cnt<g_numDeviceFields;l_cnt++){
		if(p_name==g_deviceFields[l_cnt].fieldName){
			return g_deviceFields[l_cnt].fieldId;
		}
	}
	return TField::NOTFOUND;
}
