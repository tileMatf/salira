
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../exp_hierarchy/auto_load.hh"
#include "../exp_hierarchy/expression.hh"
#include "location.hh"
	#include "position.hh"

#include "LambdaScanner.h"
#include "lambda.tab.h"

%}
%option nodefault yyclass="FlexScanner" noyywrap c++

%%
"let" { return Lambda::BisonParser::token::LET;}
"in" { return Lambda::BisonParser::token::IN;}
"MAX" { return Lambda::BisonParser::token::MAX;}
"MIN" { return Lambda::BisonParser::token::MIN; }
"NEG" { return Lambda::BisonParser::token::NEG;}
"--"[^-]+[\n] {
		// One line comment
		
		yylval->str = (char*) malloc(strlen(yytext) + 1);
		if(yylval->str == NULL)
		{
			std::cerr << "Allocation failure" << std::endl;		
			exit(EXIT_FAILURE);
		}
		// Copy to yylval
		strcpy(yylval->str, yytext);
		
		return Lambda::BisonParser::token::COMMENT;
		}
[A-Z][a-zA-Z0-9_]* { // ID_F: starts with big letter and optional big or small letters or numbers after (F1, Ga2, ...)
		yylval->str = (char*) malloc(strlen(yytext) + 1);
		if(yylval->str == NULL)
		{
			std::cerr << "Allocation failure" << std::endl;		
			exit(EXIT_FAILURE);
		}
		// Copy to yylval
		strcpy(yylval->str, yytext);
		
		return Lambda::BisonParser::token::ID_F;
		}
[a-z][a-zA-Z0-9_]* { 
		// ID: starts with small letter and optional big or small letters or numbers after (x1, minCal, iQ1,...)
		yylval->str = (char*) malloc(strlen(yytext) + 1);
		if(yylval->str == NULL)
		{
			std::cerr << "Allocation failure" << std::endl;		
			exit(EXIT_FAILURE);
		}
		// Copy to yylval
		strcpy(yylval->str, yytext);
		
		return Lambda::BisonParser::token::ID;
		}
[0-9]+ { 	// Int numeric
  
		// Copy to yylval
		yylval->intNum = atoi(yytext);
		return Lambda::BisonParser::token::INT_NUM; 
		}
[0-9]+(\.[0-9]+)? { 
			// Double numeric
			
			// Copy to yylval
			yylval->doubleNum = atof(yytext);
			return Lambda::BisonParser::token::DOUBLE_NUM; 
  			}

[+*\\/%:><=.,!"';()\[\]-] { 
			// One character
			// return ASCII value
			return *yytext;
			}
[ \t\n]+ { // Ignore whitespaces 
	}
. {  
      // Error
      std::cerr << "ERROR: Unrecognized character(s) -> " << yytext << std::endl;
}
%%
