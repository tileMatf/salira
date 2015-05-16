#ifndef SALIRA_TYPES_H__
#define SALIRA_TYPES_H__

#include "expression.hh"
/*
 * Primitive value class which inherits expression. Purpose is to identify constant values
 * inside of expression tree. Currently is implemented as template class but in future can be
 * derivated so can represent more complex values as lists, strings, object, etc.
 * 
 */
class PrimitiveValue : public ExpressionBase {
public:
    PrimitiveValue() 
      : ExpressionBase(true){}
    virtual int eval() const {}
    inline virtual bool isToken() const {return false;}
    inline virtual bool isConstant() const {return true;}
    virtual Expression eval(const std::vector<Expression>& values) const =0;
    
};

/* 
 * Derived Primitive Value class SaliraInt which basically 
 */

class SaliraInt : public PrimitiveValue {
private:
  int _value;
public:
  SaliraInt(int value) : PrimitiveValue(), _value(value) {}
  inline int value() { return _value; }
  inline void setValue(int new_value) { _value = new_value;}
  
  // Eval
  virtual Expression eval(const std::vector<Expression>& values) const {
    return Expression(new SaliraInt(_value));
  }
};

/*
 * Dummy class which will represent arguments in function. More precisely it represent places where arguments
 * should be placed inside of Expression tree.  
 */

class Token : public ExpressionBase {
private:
  int _placement;
public:
  virtual bool isToken() const { return true; }
  virtual bool isConstant() const { return false; }
  virtual Expression eval(const std::vector<Expression>& values) const{ 
    return values[_placement];
  }
  Token(int place) : _placement(place), ExpressionBase(false) {}
};


#endif // SALIRA_TYPES_H__