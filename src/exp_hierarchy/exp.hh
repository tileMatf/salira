#ifndef EXPRESSION_H__
#define EXPRESSION_H__

#include <iostream>
#include <vector>
#include <unordered_map>
#include "SaliraExceptions.hh"
#include "salira_writer.hh"

class ExpressionBase;
using Expression = ExpressionBase*;

class ExpressionBase{
public:
  enum Type {S_INT, S_FUNCTOR, S_TOKEN};
  ExpressionBase(){}
  virtual std::string print() const = 0;
  virtual Type getType() const = 0;
	virtual void generateGCode() const = 0; 
  virtual ~ExpressionBase() {}
};


class SaliraInt : public ExpressionBase{
private:
  int _value;
public:
  SaliraInt(int value) : ExpressionBase(), _value(value) {}
  virtual std::string print() const { return 
std::string("SaliraInt:")+std::to_string(_value); }
	virtual Type getType() const {return ExpressionBase::S_INT;};
  virtual void generateGCode() const{
		SaliraWriter& out = SaliraWriter::getInstance();		
    out.write("PUSHINT " + std::to_string(_value));
  }
	
  inline int value() { return _value; }
  inline void setValue(int new_value) { _value = new_value;}
};



#endif // EXPRESSION_H__
