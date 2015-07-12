#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// Override interface for yylex
#undef YY_DECL
#define YY_DECL int Lambda::FlexScanner::yylex() 

// Include Bison for types / tokens
#include "lambda.tab.h"


namespace Lambda
{
	class FlexScanner : public yyFlexLexer
	{
	  
		public:
			// Save the pointer to yylval so we can change it, and invoke scanner
			int yylex(Lambda::BisonParser::semantic_type *lval)
			{
				yylval = lval;
				return yylex();
			}
		private:
			// Scanning function created by Flex; make this private to force usage
			// of the overloaded method so we can get a pointer to Bison's yylval
			int yylex();
			
			// Point to yylval (provided by Bison in overloaded yylex)
			Lambda::BisonParser::semantic_type *yylval;
	};
}
