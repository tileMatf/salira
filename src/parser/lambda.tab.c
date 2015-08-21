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
			      

#line 85 "lambda.tab.c" // lalr1.cc:408


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
#line 152 "lambda.tab.c" // lalr1.cc:474

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
  case 2:
#line 138 "lambda.y" // lalr1.cc:847
    { 
}
#line 549 "lambda.tab.c" // lalr1.cc:847
    break;

  case 3:
#line 141 "lambda.y" // lalr1.cc:847
    {
}
#line 556 "lambda.tab.c" // lalr1.cc:847
    break;

  case 4:
#line 143 "lambda.y" // lalr1.cc:847
    { 
}
#line 563 "lambda.tab.c" // lalr1.cc:847
    break;

  case 5:
#line 146 "lambda.y" // lalr1.cc:847
    {
      
			  Expression f = new Functor(std::string("$")+std::string((yystack_[3].value.str)), {(yystack_[0].value.e)}, arguments.size());
			  f->tree(0);
			  SaliraLog::log("ttt");
			  f->generateGCode();
			  arguments.clear();
			  variables.clear();
			  counter = 0;
			  
			  // debug
			  std::cout << "Deklaracija " <<(yystack_[3].value.str) << std::endl;
}
#line 581 "lambda.tab.c" // lalr1.cc:847
    break;

  case 6:
#line 159 "lambda.y" // lalr1.cc:847
    {
	  std::cout << "Udje " <<(yystack_[1].value.str) << std::endl;
	  
	  Expression f = new Functor(std::string("$")+std::string((yystack_[1].value.str)), values, values.size());
	  Functor::gCodeEnd(f);

      }
#line 593 "lambda.tab.c" // lalr1.cc:847
    break;

  case 7:
#line 166 "lambda.y" // lalr1.cc:847
    {}
#line 599 "lambda.tab.c" // lalr1.cc:847
    break;

  case 8:
#line 167 "lambda.y" // lalr1.cc:847
    {}
#line 605 "lambda.tab.c" // lalr1.cc:847
    break;

  case 9:
#line 169 "lambda.y" // lalr1.cc:847
    {	
	    if(variables.find((yystack_[0].value.str)) == variables.end())
	    {
	      variables[(yystack_[0].value.str)] = counter;
	      counter++;
	    }
	    arguments.push_back(new Token(variables[(yystack_[0].value.str)]));
  }
#line 618 "lambda.tab.c" // lalr1.cc:847
    break;

  case 10:
#line 178 "lambda.y" // lalr1.cc:847
    {
      }
#line 625 "lambda.tab.c" // lalr1.cc:847
    break;

  case 11:
#line 180 "lambda.y" // lalr1.cc:847
    {
}
#line 632 "lambda.tab.c" // lalr1.cc:847
    break;

  case 12:
#line 183 "lambda.y" // lalr1.cc:847
    {
	    values.push_back(Expression(new SaliraInt((yystack_[0].value.intNum))));
	   }
#line 640 "lambda.tab.c" // lalr1.cc:847
    break;

  case 13:
#line 186 "lambda.y" // lalr1.cc:847
    {
	    values.push_back(Expression(new SaliraInt((yystack_[0].value.doubleNum))));
	   }
#line 648 "lambda.tab.c" // lalr1.cc:847
    break;

  case 14:
#line 190 "lambda.y" // lalr1.cc:847
    {    
		  (yylhs.value.e) = new Functor("$ADD",{(yystack_[2].value.e),(yystack_[0].value.e)});
		  std::cout << "+" << std::endl;
	}
#line 657 "lambda.tab.c" // lalr1.cc:847
    break;

  case 15:
#line 194 "lambda.y" // lalr1.cc:847
    { 
	      (yylhs.value.e) = new Functor("$SUB",{(yystack_[2].value.e),(yystack_[0].value.e)});
	      std::cout << "-" << std::endl;
	}
#line 666 "lambda.tab.c" // lalr1.cc:847
    break;

  case 16:
#line 198 "lambda.y" // lalr1.cc:847
    {
		(yylhs.value.e) = new Functor("$MUL",{(yystack_[2].value.e),(yystack_[0].value.e)});
		std::cout << "*" << std::endl;
	}
#line 675 "lambda.tab.c" // lalr1.cc:847
    break;

  case 17:
#line 202 "lambda.y" // lalr1.cc:847
    { 
		(yylhs.value.e) = new Functor("$DIV",{(yystack_[2].value.e),(yystack_[0].value.e)});
		std::cout << "//" << std::endl;
}
#line 684 "lambda.tab.c" // lalr1.cc:847
    break;

  case 18:
#line 206 "lambda.y" // lalr1.cc:847
    {   
	  (yylhs.value.e) = new SaliraInt((yystack_[0].value.intNum));
	  std::cout << (yystack_[0].value.intNum) << std::endl;
}
#line 693 "lambda.tab.c" // lalr1.cc:847
    break;

  case 19:
#line 210 "lambda.y" // lalr1.cc:847
    {
	    (yylhs.value.e) = new SaliraInt((yystack_[0].value.doubleNum));
}
#line 701 "lambda.tab.c" // lalr1.cc:847
    break;

  case 20:
#line 213 "lambda.y" // lalr1.cc:847
    {
			    (yylhs.value.e) = new Functor(std::string("$")+std::string((yystack_[1].value.str)),args_f);
			    args_f.clear();
			    std::cout << (yystack_[1].value.str) << std::endl;
}
#line 711 "lambda.tab.c" // lalr1.cc:847
    break;

  case 21:
#line 218 "lambda.y" // lalr1.cc:847
    {
			    (yylhs.value.e) = new Functor("$NEG",{(yystack_[1].value.e)});
			    std::cout << " NEG " << std::endl;
}
#line 720 "lambda.tab.c" // lalr1.cc:847
    break;

  case 22:
#line 222 "lambda.y" // lalr1.cc:847
    {
      if(variables.find((yystack_[0].value.str)) == variables.end())
      {
	  throw SaliraException("Variable not exists in declaration of function arguments.");
	}
	
      (yylhs.value.e) = new Token(variables[(yystack_[0].value.str)]);
      std::cout << (yystack_[0].value.str) << std::endl;
}
#line 734 "lambda.tab.c" // lalr1.cc:847
    break;

  case 23:
#line 231 "lambda.y" // lalr1.cc:847
    { 	
		  (yylhs.value.e) = (yystack_[1].value.e);
		  }
#line 742 "lambda.tab.c" // lalr1.cc:847
    break;

  case 24:
#line 235 "lambda.y" // lalr1.cc:847
    {
				  args_f.push_back((yystack_[0].value.e));
				  std::cout  <<" argumenti funkcije" << std::endl;
}
#line 751 "lambda.tab.c" // lalr1.cc:847
    break;

  case 25:
#line 239 "lambda.y" // lalr1.cc:847
    { 
		    args_f.push_back((yystack_[0].value.e));
		    std::cout << "argument funkcije" << std::endl;
}
#line 760 "lambda.tab.c" // lalr1.cc:847
    break;


#line 764 "lambda.tab.c" // lalr1.cc:847
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


  const signed char BisonParser::yypact_ninf_ = -10;

  const signed char BisonParser::yytable_ninf_ = -1;

  const signed char
  BisonParser::yypact_[] =
  {
      -6,    34,     5,    -6,     0,   -10,   -10,   -10,    -5,   -10,
      10,   -10,   -10,     9,   -10,    -1,   -10,   -10,   -10,   -10,
     -10,   -10,    -1,    -4,    -1,    17,    17,    -1,    -1,    -9,
      -1,    -1,    -1,    -1,    17,    11,   -10,    22,    22,    23,
     -10,   -10
  };

  const unsigned char
  BisonParser::yydefact_[] =
  {
       0,     0,     0,     2,     0,    12,    13,     9,     0,     8,
       6,    11,     1,     0,     4,     0,     7,    10,     3,    18,
      19,    22,     0,     0,     0,     5,    25,    20,     0,     0,
       0,     0,     0,     0,    24,     0,    23,    14,    15,    16,
      17,    21
  };

  const signed char
  BisonParser::yypgoto_[] =
  {
     -10,   -10,   -10,    40,   -10,    36,   -10,    35,    -7,   -10
  };

  const signed char
  BisonParser::yydefgoto_[] =
  {
      -1,     2,     3,     4,     8,     9,    10,    11,    25,    27
  };

  const unsigned char
  BisonParser::yytable_[] =
  {
       7,     1,    19,    20,    21,    12,    22,    30,    31,    32,
      33,    23,    36,     5,     6,    26,    28,    29,    15,    24,
      34,    35,    14,    37,    38,    39,    40,    30,    31,    32,
      33,    18,    41,    30,    31,    32,    33,     5,     6,     7,
      32,    33,    33,    13,    16,    17
  };

  const unsigned char
  BisonParser::yycheck_[] =
  {
       5,     7,     3,     4,     5,     0,     7,    16,    17,    18,
      19,    12,    21,     3,     4,    22,    20,    24,    23,    20,
      27,    28,    22,    30,    31,    32,    33,    16,    17,    18,
      19,    22,    21,    16,    17,    18,    19,     3,     4,     5,
      18,    19,    19,     3,     8,    10
  };

  const unsigned char
  BisonParser::yystos_[] =
  {
       0,     7,    25,    26,    27,     3,     4,     5,    28,    29,
      30,    31,     0,    27,    22,    23,    29,    31,    22,     3,
       4,     5,     7,    12,    20,    32,    32,    33,    20,    32,
      16,    17,    18,    19,    32,    32,    21,    32,    32,    32,
      32,    21
  };

  const unsigned char
  BisonParser::yyr1_[] =
  {
       0,    24,    25,    26,    26,    27,    27,    28,    28,    29,
      30,    30,    31,    31,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    33,    33
  };

  const unsigned char
  BisonParser::yyr2_[] =
  {
       0,     2,     1,     3,     2,     4,     2,     2,     1,     1,
       2,     1,     1,     1,     3,     3,     3,     3,     1,     1,
       2,     4,     1,     3,     2,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const BisonParser::yytname_[] =
  {
  "$end", "error", "$undefined", "INT_NUM", "DOUBLE_NUM", "ID", "COMMENT",
  "ID_F", "LET", "IN", "MAX", "MIN", "NEG", "\"func\"", "\"func2\"",
  "\"func1\"", "'+'", "'-'", "'*'", "'/'", "'('", "')'", "';'", "'='",
  "$accept", "P", "PROGRAM", "LINE", "ARGS", "ARGEXP", "VALS", "VAL",
  "EXP", "ARGS_F", YY_NULLPTR
  };


  const unsigned char
  BisonParser::yyrline_[] =
  {
       0,   138,   138,   141,   143,   146,   159,   166,   167,   169,
     178,   180,   183,   186,   190,   194,   198,   202,   206,   210,
     213,   218,   222,   231,   235,   239
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
      20,    21,    18,    16,     2,    17,     2,    19,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
       2,    23,     2,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15
    };
    const unsigned int user_token_number_max_ = 270;
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
#line 1111 "lambda.tab.c" // lalr1.cc:1155
#line 244 "lambda.y" // lalr1.cc:1156


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
























