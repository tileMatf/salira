%skeleton "lalr1.cc"
%defines
%define api.namespace {Lambda}
%define parser_class_name {BisonParser}
%parse-param { Lambda::FlexScanner &scanner}
%lex-param { Lambda::FlexScanner &scanner}


%code requires
{
	#include "location.hh"
	#include "position.hh"
	#include "../exp_hierarchy/auto_load.hh"
	// Declare Scanner class
	namespace Lambda {
		class FlexScanner;
	}
	
	
	
}

%code {
	
	#include "../exp_hierarchy/auto_load.hh"

	std::vector<Expression> arguments{};
	std::unordered_map< std::string, int > variables{};
	int counter = 0;
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
%type <e> ArGr
%type <e> T
%type <e> F

%%
program : ID ARGS '=' ArGr  {std::cout << " USAO " << std::endl; 
			      for(auto i  : arguments)
				  {
				      std::cout << ((SaliraInt*)i)->value() << std::endl;
				  }
			//NOTE: Need to  be called at the begining of program to load all basic functions
			      Functor::initBaseFunctions();
			      SaliraUtility::insertFunctionInPool($1, $4);
			      // testing
			      std::vector<Expression> test;
			      test.push_back(new SaliraInt(6));
			      test.push_back(new SaliraInt(12));
			      SaliraInt* temp =(SaliraInt*) $4->eval(test);
			      std::cout << "Rez" <<  temp->value() << std::endl;
}
;
ARGS : ARGS ID  {std::cout << " Args ID " << std::endl;	
		 
		if(variables.find($2) == variables.end()){
		  variables[$2] = counter;
		  counter++;
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
	 variables[$1] = counter;
	 counter++;
	}
}
;
ArGr : ArGr '+' T { 
	std::cout << "PLUS" << std::endl;
	$$ = new Functor("plus",{$1,$3});}
| ArGr '-' T { 
	std::cout << " MINUS " << std::endl;
	$$ = new Functor("minus",{$1,$3});}
| T { 
      std::cout << " T " << std::endl;
      $$ = $1;
} 
;
T : T '*' F  { 
	std::cout << " PUTA " << std::endl;
	$$ = new Functor("mult",{$1,$3});}
| T '/' F  { 
	std::cout << " PODELJENO " << std::endl;
	$$ = new Functor("div",{$1,$3});
} 
| F { 
      std::cout << " F " << std::endl;
      $$ = $1;
} 
;
F: NUM  { 
	  std::cout << " BROJ " <<  std::to_string($1) << std::endl;
	  $$ = new SaliraInt($1);
}
| ID { 
	std::cout << " ID " << $1 << std::endl;
	
	if(variables.find($1) == variables.end()){
	  throw SaliraException("Variable not exists in declaration of function arguments.");
	}
	$$ = new Token(variables[$1]);
	
}
| '(' ArGr ')'   { 	
		  std::cout << " ZAGRADE " << std::endl;
		  $$ = $2; 
		  }
;
%%

void Lambda::BisonParser::error(const std::string &s)
{
	std::cerr << "Error: " << s << std::endl;
}

// Implement yylex function, after parser declaration
#include "LambdaScanner.h"

static int yylex(Lambda::BisonParser::semantic_type *yylval, Lambda::FlexScanner &scanner)
{
	return scanner.yylex(yylval);
}

