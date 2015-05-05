%skeleton "lalr1.cc"
%defines
%define namespace "Lambda"
%define parser_class_name "BisonParser"
%parse-param { Lambda::FlexScanner &scanner}
%lex-param { Lambda::FlexScanner &scanner}

%code requires
{
	// Declare Scanner class
	namespace Lambda {
		class FlexScanner;
	}	
}

%code {
	
	static int yylex(Lambda::BisonParser::semantic_type *yylval, Lambda::FlexScanner &scanner);
}
%union
{
	int num;
	char* str;
}

%token <num> NUM
%token <str> ID COMMENT
%token LET IN MAX MIN NEG 

%%
program : E {}
;
E : E T  { std::cout << " PRIMENA " << std::endl;}
| E '+' T  { std::cout << " PLUS " << std::endl;}
| E '-'  { std::cout << " MINUS " << std::endl;}
| T { std::cout << " T " << std::endl;} 
;
T : LET ID '=' F IN F { std::cout << " LET " << std::endl;} 
| '\\' ID '.' F { std::cout << " LAMBDA " << std::endl;}
| T '*' F  { std::cout << " PUTA " << std::endl;}
| T '/' F  { std::cout << " PODELJENO " << std::endl;}
| T '%' F  { std::cout << " MOD " << std::endl;} 
| MAX '(' F ',' F ')'  { std::cout << " MAX " << std::endl;}
| MIN  '(' F ',' F ')' { std::cout << " MIN " << std::endl;}
| NEG '(' F ')' { std::cout << " NEG " << std::endl;}
| F { std::cout << " F " << std::endl;} 
;
F: NUM  { std::cout << " BROJ " <<  std::to_string($1) << std::endl;}
| ID { std::cout << " ID " << $1 << std::endl;}
| '(' E ')'  { std::cout << " ZAGRADE " << std::endl;}
;
%%

void Lambda::BisonParser::error(const Lambda::BisonParser::location_type &loc, const std::string &s)
{
	std::cerr << "Error: " << s << std::endl;
}

// Implement yylex function, after parser declaration
#include "LambdaScanner.h"

static int yylex(Lambda::BisonParser::semantic_type *yylval, Lambda::FlexScanner &scanner)
{
	return scanner.yylex(yylval);
}

