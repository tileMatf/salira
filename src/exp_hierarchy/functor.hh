#ifndef FUNCTOR_H__
#define FUNCTOR_H__

/*
 * Core of whole mechanism. It's most complex class in mechanism.
 * Contains all methods for generating gcode. 
 * 
 * Functor class represent function and implements basic functionality
 * for GCode generation. 
 */

#include "exp.hh"
#include "token.hh"
#include <vector>
#include <initializer_list>

class Functor : public ExpressionBase{
private:
	// Contains names of already declared functions
	static FMap _map;
	// Names of base functions
	// Reason for this implementation is possibility of enlarging begining set of 
	// existing functions.
	static FMap _base_functions;
	// Arguments of function
	std::vector<Expression> _args;
	// Self explanatory
	std::string _identifier;
	// Number of arguments, used only in declaration.
	int _num_of_args;
public:
	Functor(std::string, std::initializer_list<Expression>, int = 0);
	Functor(std::string, std::vector<Expression>& , int = 0);
	
	/* 
	 * Static interface for preparing and 
	 */
	static void insertInMap(std::string ) throw();	
	static void initBaseFunctions();
	
	// Method for generating head and end of gcode.
	static void gCodeBegin();
	static void gCodeEnd(Expression);
	
	// Interface API (ingerited from ExpressionBase)
	virtual std::string print() const {return std::string("Functor")+_identifier;}
	virtual Type getType() const {return ExpressionBase::S_FUNCTOR;};
  virtual void generateGCode();

private:
	// Checking if function is already defined, so it must be 
	// function call.
	bool isDefined() const;
	// Checking if function is one of default gcode machine instructions
	// $ADD, $DIV, $SUB, $MUL, $NEG
	bool isBase() const;
	
	// GCode
	  // Generate function declaration gcode
	void gCodeDeclaration() const;
	  // Generate function call in gcode
	void gCodeCall() const;
	  // Generate base function call in gcode
	// NOTE: See if there is need for two different function call g code
	// generation for base and custom functions.
	void baseGcode(bool = true) const;
};

#endif // FUNCTOR_H__