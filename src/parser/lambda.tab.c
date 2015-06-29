// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "lambda.tab.c" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "lambda.tab.h"

// User implementation prologue.

#line 51 "lambda.tab.c" // lalr1.cc:407
// Unqualified %code blocks.
#line 24 "lambda.y" // lalr1.cc:408

	
	#include "../exp_hierarchy/auto_load.hh"

	// Arguments of function		  
	std::vector<Expression> arguments{};
	
	// Variables map and their position in arguments order
	std::unordered_map< std::string, int > variables{};
	
	// Position of current variable in arguments order
	int counter = 0;
	
	// Prototype for the yylex function
	static int yylex(Lambda::BisonParser::semantic_type *yylval, Lambda::FlexScanner &scanner);
			      

#line 71 "lambda.tab.c" // lalr1.cc:408


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 3 "lambda.y" // lalr1.cc:474
namespace Lambda {
#line 138 "lambda.tab.c" // lalr1.cc:474

  /// Build a parser object.
  BisonParser::BisonParser (Lambda::FlexScanner &scanner_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg)
  {}

  BisonParser::~BisonParser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  BisonParser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }


  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  BisonParser::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  BisonParser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  BisonParser::by_type::by_type ()
     : type (empty)
  {}

  inline
  BisonParser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  BisonParser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  BisonParser::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  BisonParser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  BisonParser::by_state::by_state ()
    : state (empty)
  {}

  inline
  BisonParser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  BisonParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  BisonParser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  BisonParser::symbol_number_type
  BisonParser::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  BisonParser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  BisonParser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  BisonParser::stack_symbol_type&
  BisonParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }


  template <typename Base>
  inline
  void
  BisonParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  BisonParser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  BisonParser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  BisonParser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  BisonParser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  BisonParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  BisonParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  BisonParser::debug_level_type
  BisonParser::debug_level () const
  {
    return yydebug_;
  }

  void
  BisonParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline BisonParser::state_type
  BisonParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  BisonParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  BisonParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  BisonParser::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, scanner));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 4:
#line 109 "lambda.y" // lalr1.cc:847
    {
			      //NOTE: Need to  be called at the begining of program to load all basic functions
			      Functor::initBaseFunctions();
	
			      std::cout << " USAO " << std::endl; 
			    
			      std::cout << (yystack_[3].value.str) << std::endl;
			      std::cout << arguments.size() << std::endl;
			      std::cout << "args " << std::endl;
			      // printing arguments
			      for(auto item : arguments)
			      {
				  std::cout << item->print() << std::endl;
			      }
			      SaliraUtility::insertFunctionInPool((yystack_[3].value.str), (yystack_[0].value.e), arguments);
			      // testing
			      
			      SaliraDev::MapPrint();
			      
			      std::vector<Expression> test;
			      
			      for(unsigned i = 0, ie = arguments.size(); i < ie; i++)
				test.push_back(new SaliraInt(6));
				std::cout << "args2 " << std::endl;
			      for(auto item : test){
				std::cout << item->print() << std::endl;
			      }
			      
			      Expression f = new Functor((yystack_[3].value.str), test);
			      SaliraInt* temp =(SaliraInt*) f->eval(test);
			      std::cout << "Rez" <<  temp->value() << std::endl;
			      arguments.clear();
			      variables.clear();
			      counter = 0;
}
#line 568 "lambda.tab.c" // lalr1.cc:847
    break;

  case 5:
#line 145 "lambda.y" // lalr1.cc:847
    {}
#line 574 "lambda.tab.c" // lalr1.cc:847
    break;

  case 6:
#line 146 "lambda.y" // lalr1.cc:847
    {}
#line 580 "lambda.tab.c" // lalr1.cc:847
    break;

  case 7:
#line 148 "lambda.y" // lalr1.cc:847
    {	
      std::cout << " ID " << (yystack_[0].value.str)<< std::endl; 
      if(variables.find((yystack_[0].value.str)) == variables.end()){
	 variables[(yystack_[0].value.str)] = counter;
	 counter++;
	}
	arguments.push_back(new Token(variables[(yystack_[0].value.str)],ExpressionBase::S_INT ));
}
#line 593 "lambda.tab.c" // lalr1.cc:847
    break;

  case 8:
#line 156 "lambda.y" // lalr1.cc:847
    {
	    std::cout << " INT_NUM " << std::endl; 
	    arguments.push_back(Expression(new SaliraInt((yystack_[0].value.intNum))));
	   }
#line 602 "lambda.tab.c" // lalr1.cc:847
    break;

  case 9:
#line 160 "lambda.y" // lalr1.cc:847
    {
	    std::cout << " DOUBLE_NUM " << std::endl; 
	    arguments.push_back(Expression(new SaliraInt((yystack_[0].value.doubleNum))));
	    }
#line 611 "lambda.tab.c" // lalr1.cc:847
    break;

  case 10:
#line 164 "lambda.y" // lalr1.cc:847
    {
	  (yylhs.value.e) = new Functor((yystack_[3].value.str),{(yystack_[1].value.e)});
}
#line 619 "lambda.tab.c" // lalr1.cc:847
    break;

  case 11:
#line 186 "lambda.y" // lalr1.cc:847
    {}
#line 625 "lambda.tab.c" // lalr1.cc:847
    break;

  case 12:
#line 188 "lambda.y" // lalr1.cc:847
    { 
	std::cout << "PLUS" << std::endl;
	(yylhs.value.e) = new Functor("plus",{(yystack_[2].value.e),(yystack_[0].value.e)});
	}
#line 634 "lambda.tab.c" // lalr1.cc:847
    break;

  case 13:
#line 192 "lambda.y" // lalr1.cc:847
    { 
	std::cout << " MINUS " << std::endl;
	(yylhs.value.e) = new Functor("minus",{(yystack_[2].value.e),(yystack_[0].value.e)});
	}
#line 643 "lambda.tab.c" // lalr1.cc:847
    break;

  case 14:
#line 196 "lambda.y" // lalr1.cc:847
    {
	std::cout << " MULT " << std::endl;
	(yylhs.value.e) = new Functor("mult",{(yystack_[2].value.e),(yystack_[0].value.e)});
	}
#line 652 "lambda.tab.c" // lalr1.cc:847
    break;

  case 15:
#line 200 "lambda.y" // lalr1.cc:847
    { 
	std::cout << " DIV " << std::endl;
	(yylhs.value.e) = new Functor("div",{(yystack_[2].value.e),(yystack_[0].value.e)});
}
#line 661 "lambda.tab.c" // lalr1.cc:847
    break;

  case 16:
#line 204 "lambda.y" // lalr1.cc:847
    { 
	  std::cout << " INT_NUM " <<  std::to_string((yystack_[0].value.intNum)) << std::endl;
	  (yylhs.value.e) = new SaliraInt((yystack_[0].value.intNum));
}
#line 670 "lambda.tab.c" // lalr1.cc:847
    break;

  case 17:
#line 208 "lambda.y" // lalr1.cc:847
    {
	  std::cout << " DOUBLE_NUM " <<  std::to_string((yystack_[0].value.doubleNum)) << std::endl;
	  (yylhs.value.e) = new SaliraInt((yystack_[0].value.doubleNum));
}
#line 679 "lambda.tab.c" // lalr1.cc:847
    break;

  case 18:
#line 212 "lambda.y" // lalr1.cc:847
    {
	  (yylhs.value.e) = new Functor((yystack_[3].value.str),{(yystack_[1].value.e)});
}
#line 687 "lambda.tab.c" // lalr1.cc:847
    break;

  case 19:
#line 215 "lambda.y" // lalr1.cc:847
    {
	std::cout << " ID " << (yystack_[0].value.str) << std::endl;
	
	if(variables.find((yystack_[0].value.str)) == variables.end()){
	  throw SaliraException("Variable not exists in declaration of function arguments.");
	}
	
	// NOTE: Second argument is artificial, todo -> type checking
	(yylhs.value.e) = new Token(variables[(yystack_[0].value.str)], ExpressionBase::S_INT);
}
#line 702 "lambda.tab.c" // lalr1.cc:847
    break;

  case 20:
#line 225 "lambda.y" // lalr1.cc:847
    { 	
		  std::cout << " ZAGRADE " << std::endl;
		  (yylhs.value.e) = (yystack_[1].value.e);
		  }
#line 711 "lambda.tab.c" // lalr1.cc:847
    break;

  case 21:
#line 246 "lambda.y" // lalr1.cc:847
    {}
#line 717 "lambda.tab.c" // lalr1.cc:847
    break;

  case 22:
#line 247 "lambda.y" // lalr1.cc:847
    {}
#line 723 "lambda.tab.c" // lalr1.cc:847
    break;


#line 727 "lambda.tab.c" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  BisonParser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  BisonParser::yysyntax_error_ (state_type, symbol_number_type) const
  {
    return YY_("syntax error");
  }


  const signed char BisonParser::yypact_ninf_ = -13;

  const signed char BisonParser::yytable_ninf_ = -20;

  const signed char
  BisonParser::yypact_[] =
  {
      -1,    46,     4,    -7,   -12,    57,    62,     1,    51,     5,
     -13,    67,   -13,     3,   -13,    51,   -13,   -13,   -13,     2,
      48,    51,   -13,    51,    51,    51,    51,   -13,    67,    23,
      51,   -13,    67,    20,    20,    12,   -13,    72,    67,    29,
     -13
  };

  const unsigned char
  BisonParser::yydefact_[] =
  {
       0,     0,     0,     0,     8,     9,     7,     0,     0,     0,
       6,    11,     1,     0,     3,     0,    16,    17,    19,     0,
       0,     0,     5,     0,     0,     0,     0,     2,    22,     0,
       0,    20,     4,    12,    13,    14,    15,    10,    21,     0,
      18
  };

  const signed char
  BisonParser::yypgoto_[] =
  {
     -13,   -13,    36,   -13,    30,    -8,    10
  };

  const signed char
  BisonParser::yydefgoto_[] =
  {
      -1,     2,     3,     9,    10,    11,    29
  };

  const signed char
  BisonParser::yytable_[] =
  {
      20,   -16,   -16,   -16,    12,   -16,     1,    28,     4,     5,
       6,     1,     7,    32,    14,    33,    34,    35,    36,    15,
      30,    38,    28,     8,    27,    21,    16,    17,    18,    26,
      19,    38,    16,    17,    18,    25,    19,    26,    13,    22,
      39,     8,    37,     0,     0,     0,     0,     8,    40,     4,
       5,     6,     0,     7,    16,    17,    18,     0,    19,     0,
       0,    23,    24,    25,     8,    26,     0,    31,     0,     8,
     -17,   -17,   -17,     0,   -17,   -19,   -19,   -19,     0,   -19,
      23,    24,    25,     0,    26,   -18,   -18,   -18,     0,   -18
  };

  const signed char
  BisonParser::yycheck_[] =
  {
       8,    13,    14,    15,     0,    17,     7,    15,     3,     4,
       5,     7,     7,    21,    21,    23,    24,    25,    26,    18,
      18,    29,    30,    18,    21,    20,     3,     4,     5,    17,
       7,    39,     3,     4,     5,    15,     7,    17,     2,     9,
      30,    18,    19,    -1,    -1,    -1,    -1,    18,    19,     3,
       4,     5,    -1,     7,     3,     4,     5,    -1,     7,    -1,
      -1,    13,    14,    15,    18,    17,    -1,    19,    -1,    18,
      13,    14,    15,    -1,    17,    13,    14,    15,    -1,    17,
      13,    14,    15,    -1,    17,    13,    14,    15,    -1,    17
  };

  const unsigned char
  BisonParser::yystos_[] =
  {
       0,     7,    23,    24,     3,     4,     5,     7,    18,    25,
      26,    27,     0,    24,    21,    18,     3,     4,     5,     7,
      27,    20,    26,    13,    14,    15,    17,    21,    27,    28,
      18,    19,    27,    27,    27,    27,    27,    19,    27,    28,
      19
  };

  const unsigned char
  BisonParser::yyr1_[] =
  {
       0,    22,    23,    23,    24,    25,    25,    26,    26,    26,
      26,    26,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    28,    28
  };

  const unsigned char
  BisonParser::yyr2_[] =
  {
       0,     2,     3,     2,     4,     2,     1,     1,     1,     1,
       4,     1,     3,     3,     3,     3,     1,     1,     4,     1,
       3,     2,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const BisonParser::yytname_[] =
  {
  "$end", "error", "$undefined", "INT_NUM", "DOUBLE_NUM", "ID", "COMMENT",
  "ID_F", "LET", "IN", "MAX", "MIN", "NEG", "'+'", "'-'", "'*'", "UMINUS",
  "'/'", "'('", "')'", "'='", "';'", "$accept", "PROGRAM", "LINE", "ARGS",
  "ARGEXP", "EXP", "ARGS_F", YY_NULLPTR
  };


  const unsigned char
  BisonParser::yyrline_[] =
  {
       0,   106,   106,   107,   109,   145,   146,   148,   156,   160,
     164,   186,   188,   192,   196,   200,   204,   208,   212,   215,
     225,   246,   247
  };

  // Print the state stack on the debug stream.
  void
  BisonParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  BisonParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  BisonParser::token_number_type
  BisonParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      18,    19,    15,    13,     2,    14,     2,    17,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    21,
       2,    20,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    16
    };
    const unsigned int user_token_number_max_ = 268;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 3 "lambda.y" // lalr1.cc:1155
} // Lambda
#line 1080 "lambda.tab.c" // lalr1.cc:1155
#line 249 "lambda.y" // lalr1.cc:1156


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


