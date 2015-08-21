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
	extern FILE *fp;	
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
	
	
	// Arguments of function call	  
	std::vector<Expression> args_f{};
	
	
	// Values for last function call	  
	std::vector<Expression> vals_f{};
	
	// Values for each argument 		  
	std::vector<Expression> values{};
	
	// Variables map and their position in arguments order
	std::unordered_map< std::string, int > variables{};
	
	// Position of current variable in arguments order
	int counter = 0;
	
	// Object for writting gcode
	
	
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
%type <e> EXP ARGS ARGEXP ARGS_F VALS VAL


// Defining priority and associativity

%left "func"
%left "func2"
%left "func1"
%left '+' '-'
%left '*'
%left '/'
%left '(' ')'


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
P : PROGRAM { 
}
;
PROGRAM : PROGRAM LINE ';' {
}
| LINE ';' { 
}
;
LINE : ID_F ARGS '=' EXP  {
      
			  Expression f = new Functor(std::string("$")+std::string($1), {$4}, arguments.size());
			  f->tree(0);
			  SaliraLog::log("ttt");
			  f->generateGCode();
			  arguments.clear();
			  variables.clear();
			  counter = 0;
			  
			  // debug
			  std::cout << "Deklaracija " <<$1 << std::endl;
}
| ID_F VALS {
	  std::cout << "Udje " <<$1 << std::endl;
	  
	  Expression f = new Functor(std::string("$")+std::string($1), values, values.size());
	  Functor::gCodeEnd(f);

      }
;ARGS : ARGS ARGEXP {} 
| ARGEXP {}
;
ARGEXP : ID {	
	    if(variables.find($1) == variables.end())
	    {
	      variables[$1] = counter;
	      counter++;
	    }
	    arguments.push_back(new Token(variables[$1]));
  }
;
VALS : VALS VAL {
      }
| VAL {
}
;
VAL: INT_NUM {
	    values.push_back(Expression(new SaliraInt($1)));
	   }
| DOUBLE_NUM {
	    values.push_back(Expression(new SaliraInt($1)));
	   }
;
EXP : EXP '+' EXP {    
		  $$ = new Functor("$ADD",{$1,$3});
		  std::cout << "+" << std::endl;
	}
| EXP '-' EXP { 
	      $$ = new Functor("$SUB",{$1,$3});
	      std::cout << "-" << std::endl;
	}
| EXP '*' EXP {
		$$ = new Functor("$MUL",{$1,$3});
		std::cout << "*" << std::endl;
	}
| EXP '/' EXP { 
		$$ = new Functor("$DIV",{$1,$3});
		std::cout << "//" << std::endl;
} 
| INT_NUM {   
	  $$ = new SaliraInt($1);
	  std::cout << $1 << std::endl;
}
| DOUBLE_NUM {
	    $$ = new SaliraInt($1);
}
| ID_F ARGS_F  %prec "func"{
			    $$ = new Functor(std::string("$")+std::string($1),args_f);
			    args_f.clear();
			    std::cout << $1 << std::endl;
}
| ID {
      if(variables.find($1) == variables.end())
      {
	  throw SaliraException("Variable not exists in declaration of function arguments.");
	}
	
      $$ = new Token(variables[$1]);
      std::cout << $1 << std::endl;
}
| '(' EXP ')'   { 	
		  $$ = $2;
		  }
;
ARGS_F : ARGS_F EXP %prec "func1" {
				  args_f.push_back($2);
				  std::cout  <<" argumenti funkcije" << std::endl;
}
| EXP %prec "func2"{ 
		    args_f.push_back($1);
		    std::cout << "argument funkcije" << std::endl;
}
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
























