#ifndef EXPRESSION_H__
#define EXPRESSION_H__

/*
 * exp.hh 
 * 
 * Contains base expression class and smaller inherited classes and
 * those without static data fields. 
 *
 * Represents starting point of whole mechanism.
 * 
 * Whole mechanism is intended to be as minimalistic as possible so contains 
 * hierarchy like this:
 * 
 * Root: ExpressionBase
 * Functor : ExpressionBase
 * Token : ExpressionBase
 * SaliraInt : ExpressionBase
 * 
 * Future changes will be focused on SaliraInt so it can support more than
 * one datatype so hierarchy tree will go deeper in that branch.
 *
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include "SaliraExceptions.hh"
#include "salira_writer.hh"

class ExpressionBase;

using Expression = ExpressionBase*;
using FMap = std::unordered_map<std::string,bool>;

/*
 * Root class. Intention is to have universal container class and 
 * to unify some features (as printing and generating gcode method).
 * Like interface in Java or C#.
 * 
 */
class ExpressionBase{
public:
  enum Type {S_INT, S_FUNCTOR, S_TOKEN};
  ExpressionBase(){}
  virtual std::string print() const = 0;
  virtual Type getType() const = 0;
	virtual void generateGCode() = 0; 
  virtual ~ExpressionBase() {}
};


/*
 * Basic type of data currently supported. 
 * Rest of code is basically self explanatory.
 */
class SaliraInt : public ExpressionBase{
private:
  int _value;
public:
  SaliraInt(int value) : ExpressionBase(), _value(value) {}
  virtual std::string print() const { return 
std::string("SaliraInt:")+std::to_string(_value); }
	virtual Type getType() const {return ExpressionBase::S_INT;};
  virtual void generateGCode() {
		SaliraWriter& out = SaliraWriter::getInstance();		
    out.write("PUSHINT " + std::to_string(_value));
  }
	
  inline int value() { return _value; }
  inline void setValue(int new_value) { _value = new_value;}
};



#endif // EXPRESSION_H__
