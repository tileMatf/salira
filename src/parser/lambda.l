
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
		yylval->str = (char*) malloc(strlen(yytext) + 1);
		if(yylval->str == NULL)
		{
			std::cerr << "Neuspela alokacija" << std::endl;		
			exit(EXIT_FAILURE);
		}
		strcpy(yylval->str, yytext);
		return Lambda::BisonParser::token::COMMENT;
		}
[a-z][a-zA-Z0-9_]* { 	
		yylval->str = (char*) malloc(strlen(yytext) + 1);
		if(yylval->str == NULL)
		{
			std::cerr << "Neuspela alokacija" << std::endl;		
			exit(EXIT_FAILURE);
		}
		strcpy(yylval->str, yytext);
		return Lambda::BisonParser::token::ID;
		}
[0-9]+(\.[0-9]+)? { 
			yylval->num = atoi(yytext);
			return Lambda::BisonParser::token::NUM; 
  			}
[+*\\/%:><=.,!"';()\[\]-] { return *yytext;}
[ \t\n]+ {}
. {  }
"'"[^']"'" {
	   /* yylval.str = malloc(strlen(yytext) - 1);
	    if(yylval.str == NULL)
	    {
	      fprintf(stderr, "Lexer error - malloc. ");
	      exit(EXIT_FAILURE);
	    }
	    strncpy(yylval.str,yytext+1,strlen(yytext)-2);
	    yylval.str[strlen(yytext)-2]='\0';
	    return CHAR;*/
}
"\""[^"]+"\"" { 
		/* yylval.str = malloc(strlen(yytext) - 1);
		if(yylval.str == NULL)
		{
		  fprintf(stderr, "Lexer error - malloc. ");
		  exit(EXIT_FAILURE);
		}
		strncpy(yylval.str,yytext+1,strlen(yytext)-2);
		yylval.str[strlen(yytext)-2]='\0';
		return STRING;*/
		} 
%%
