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

	#include "../exp_hierarchy/auto_load.hh"

	std::vector<Expression> arguments{};
	std::unordered_map< std::string, int > variables{};
	static int yylex(Lambda::BisonParser::semantic_type *yylval, Lambda::FlexScanner &scanner);
	
	  
}
%union
{
	int num;
	char* str;
	Expression e;
}

%token <num> NUM
%token <str> ID COMMENT
%token LET IN MAX MIN NEG 
%type <Expression> ArGr
%type <Expression> T
%type <Expression> F

%%
program : ID ARGS '=' ArGr  {std::cout << " USAO " << std::endl; 
			      for(auto i  : arguments)
				  {
				      std::cout << ((SaliraInt*)i.get())->value() << std::endl;
				  }
			      SaliraUtility::insertFunctionInPool($1, $4);
}
;
ARGS : ARGS ID  {std::cout << " Args ID " << std::endl;	
		 
		if(variables.find($2) == variables.end()){
		  variables[$2] = variables.size();
		}
}
| 
/*ARGS NUM {
	    std::cout << " Args NUM" << std::endl; 
	    arguments.push_back(Expression(new SaliraInt($2)));

}
| NUM {
	    std::cout << " NUM " << std::endl; 
	    arguments.push_back(Expression(new SaliraInt($1)));
}
| */
ID {	
      std::cout << " ID " << std::endl; 
      if(variables.find($1) == variables.end()){
	 variables[$1] = variables.size();
	}
}
;
ArGr : ArGr '+' T { 
	std::cout << "PLUS" << std::endl;
	$$ = Expression(new Functor("plus",{$1,$3}));}
| ArGr '-' T { 
	std::cout << " MINUS " << std::endl;
	$$ = Expression(new Functor("minus",{$1,$3}));}
| T { 
      std::cout << " T " << std::endl;
      $$ = $1;
} 
;
T : T '*' F  { 
	std::cout << " PUTA " << std::endl;
	$$ = Expression(new Functor("mult",{$1,$3}));}
| T '/' F  { 
	std::cout << " PODELJENO " << std::endl;
	$$ = Expression(new Functor("div",{$1,$3}));
} 
| F { 
      std::cout << " F " << std::endl;
      $$ = $1;
} 
;
F: NUM  { 
	  std::cout << " BROJ " <<  std::to_string($1) << std::endl;
	  $$ = Expression(new SaliraInt($1));
}
| ID { 
	std::cout << " ID " << $1 << std::endl;
	
	if(variables.find($1) == variables.end()){
	  throw SaliraExeption("Variable not exists in declaration of function arguments.");
	}
	$$ = Expression(new Token($1));
	
}
| '(' ArGr ')'   { 	
		  std::cout << " ZAGRADE " << std::endl;
		  $$ = $2; 
		  }
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

