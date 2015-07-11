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
	
	// Forward-declare the Scanner class; the Parser needs to be assigned a 
	// Scanner, but the Scanner can't be declared without the Parser
	namespace Lambda {
		class FlexScanner;
	}
	
	
}

%code {
	
	#include "../exp_hierarchy/auto_load.hh"

	// Arguments of function		  
	std::vector<Expression> arguments{};
	
	// Variables map and their position in arguments order
	std::unordered_map< std::string, int > variables{};
	
	// Position of current variable in arguments order
	int counter = 0;
	
	// Prototype for the yylex function
	static int yylex(Lambda::BisonParser::semantic_type *yylval, Lambda::FlexScanner &scanner);
			      
}

// yylval can have one of these types
%union
{
	int intNum;
	double doubleNum;
	char* str;
	Expression e;
}

// Defining types for each token
%token <intNum> INT_NUM
%token <doubleNum> DOUBLE_NUM
%token <str> ID COMMENT ID_F
%token LET IN MAX MIN NEG 
%type <e> EXP ARGS ARGEXP ARGS_F


// Defining priority and associativity
%left '+' '-'
%left '*'
%left '/'
%left '(' ')'
%left '='
%right "func"
%right "func2"
%right "func1"
/*
* 
*  Grammar:
* 
* 
* PROGRAM :: PROGRAM LINE ;
*          | LINE ;
*
* LINE :: ID_F ARGS = EXP
*
* ARGS :: ARGS ARGEXP
* 	  | ARGEXP
*
*
* ARGEXP :: ID
* 	| INT_NUM
* 	| DOUBLE_NUM
* 	| ID ARGS_F 
* 	TODO: EXP here should not be the same EXP as in function definition if we want f(n+1) = sth, not done yet
* 	| EXP 
* 	
*
* EXP :: EXP + EXP
* 	| EXP - EXP
* 	| EXP * EXP
* 	| EXP / EXP
* 	| ID_F ARGS_F 
* 	| ID
* 	| INT_NUM
* 	| DOUBLE_NUM
* 	| ( EXP )
* 	| LIST
*
* LIST :: '[' LIST_INT ']'
*       | '[' LIST_DOUBLE ']'
*       | '[' LIST_LIST ']'
*       
* LIST_INT : LIST_INT ',' INT_NUM
*	| INT_NUM
*
* LIST_DOUBLE : LIST_DOUBLE ',' DOUBLE_NUM
*	| DOUBLE_NUM
*
* LIST_LIST : LIST_LIST ',' LIST
*	| LIST
* 
* ARGS_F :: ARGS_F EXP
* 	| EXP
* 	
* 	
*/

%%
PROGRAM : PROGRAM LINE ';'
| LINE ';'
;
LINE : ID_F ARGS '=' EXP  {
			      //NOTE: Need to  be called at the begining of program to load all basic functions
			      Functor::initBaseFunctions();
	
			      std::cout << " USAO " << std::endl; 
			    
			      std::cout << $1 << std::endl;
			      std::cout << arguments.size() << std::endl;
			      std::cout << "args " << std::endl;
			      // printing arguments
			      for(auto item : arguments)
			      {
				  std::cout << item->print() << std::endl;
			      }
			      SaliraUtility::insertFunctionInPool($1, $4, arguments);
			      // testing
			      
			      SaliraDev::MapPrint();
			      
			      std::vector<Expression> test;
			      
			      for(unsigned i = 0, ie = arguments.size(); i < ie; i++)
				test.push_back(new SaliraInt(6));
				std::cout << "args2 " << std::endl;
			      for(auto item : test){
				std::cout << item->print() << std::endl;
			      }
			      
			      Expression f = new Functor($1, test);
			      SaliraInt* temp =(SaliraInt*) f->eval(test);
			      std::cout << "Rez" <<  temp->value() << std::endl;
			      arguments.clear();
			      variables.clear();
			      counter = 0;
}
;
ARGS : ARGS ARGEXP {} 
| ARGEXP {}
;
ARGEXP : ID {	
      std::cout << " ID " << $1<< std::endl; 
      if(variables.find($1) == variables.end()){
	 variables[$1] = counter;
	 counter++;
	}
	arguments.push_back(new Token(variables[$1],ExpressionBase::S_INT ));
}
| INT_NUM {
	    std::cout << " INT_NUM " << std::endl; 
	    arguments.push_back(Expression(new SaliraInt($1)));
	   }
| DOUBLE_NUM {
	    std::cout << " DOUBLE_NUM " << std::endl; 
	    arguments.push_back(Expression(new SaliraInt($1)));
	    }
/*| ID_F ARGS_F  {
	  $$ = new Functor($1,{$2});
}*/
;
EXP : EXP '+' EXP { 
	std::cout << "PLUS" << std::endl;
	$$ = new Functor("plus",{$1,$3});
	}
| EXP '-' EXP { 
	std::cout << " MINUS " << std::endl;
	$$ = new Functor("minus",{$1,$3});
	}
| EXP '*' EXP {
	std::cout << " MULT " << std::endl;
	$$ = new Functor("mult",{$1,$3});
	}
| EXP '/' EXP { 
	std::cout << " DIV " << std::endl;
	$$ = new Functor("div",{$1,$3});
} 
| INT_NUM { 
	  std::cout << " INT_NUM " <<  std::to_string($1) << std::endl;
	  $$ = new SaliraInt($1);
}
| DOUBLE_NUM {
	  std::cout << " DOUBLE_NUM " <<  std::to_string($1) << std::endl;
	  $$ = new SaliraInt($1);
}
| ID_F ARGS_F  %prec "func"{
	 auto a = new Functor($1,{$2});
	 $$ = a->eval({$2});
}
| ID {
	std::cout << " ID " << $1 << std::endl;
	
	if(variables.find($1) == variables.end()){
	  throw SaliraException("Variable not exists in declaration of function arguments.");
	}
	
	// NOTE: Second argument is artificial, todo -> type checking
	$$ = new Token(variables[$1], ExpressionBase::S_INT);
}
| '(' EXP ')'   { 	
		  std::cout << " ZAGRADE " << std::endl;
		  $$ = $2;
		  }
/*
| LIST {}
;
LIST : '[' LIST_INT ']'
| '[' LIST_DOUBLE ']'
| '[' LIST_LIST ']'
;
LIST_INT : LIST_INT ',' INT_NUM
| INT_NUM
;
LIST_DOUBLE : LIST_DOUBLE ',' DOUBLE_NUM
| DOUBLE_NUM
;
LIST_LIST : LIST_LIST ',' LIST
| LIST
*/
;
ARGS_F : ARGS_F EXP %prec "func1" {}
| EXP %prec "func2"{}
;
%%

// We have to implement the error function
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


