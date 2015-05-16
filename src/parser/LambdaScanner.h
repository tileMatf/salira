#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// Override interface for yylex
#undef YY_DECL
#define YY_DECL int Lambda::FlexScanner::yylex() 

#include "lambda.tab.h"

#include "../exp_hierarchy/auto_load.hh"

namespace Lambda
{
	class FlexScanner : public yyFlexLexer
	{
		public:
			int yylex(Lambda::BisonParser::semantic_type *lval)
			{
				yylval = lval;
				return yylex();
			}
		private:
			int yylex();
			Lambda::BisonParser::semantic_type *yylval;
	};
}
