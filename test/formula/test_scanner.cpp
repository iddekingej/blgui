#include "test_scanner.h"
#include "formula/scanner.h"

void TTestScanner::test1()
{
	TScanner l_scanner("   bla >= 3");
	l_scanner.nextToken();
	expecti("Token 1 must be an ident ",TToken::IDENT,l_scanner.getToken());
	expect("Current position  must be 6",6,l_scanner.getCurrent());
	expect("Token  1 must be 'bla'","bla",l_scanner.getTokenText());
	l_scanner.nextToken();
	expecti("Token 2 Token code",TToken::COND_BE,l_scanner.getToken());
	expect("Token 2 text",">=",l_scanner.getTokenText());
	expect("Token 2 Current position" ,9,l_scanner.getCurrent());
	l_scanner.nextToken();
	l_scanner.nextToken();
	expecti("Token4 mustg be end of file",TToken::FILE_END,l_scanner.getToken());
	
	
}

void  TTestScanner::test2()
{
	TScanner l_scanner("   'a' and 'b'");
	l_scanner.nextToken();
	expecti("Token 1 must be a string",TToken::STRING,l_scanner.getToken());
	expect("Current position for token 1",5,l_scanner.getCurrent());
	l_scanner.nextToken();
	expecti("Token 2 ",TToken::OP_AND,l_scanner.getToken() );
	
}


void TTestScanner::doRun()
{
	test1();
	test2();
}

TTestScanner::TTestScanner()
{
}

TTestScanner::~TTestScanner()
{
}

