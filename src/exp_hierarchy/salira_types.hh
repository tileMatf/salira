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
    virtual Expression eval(const std::vector<Expression>& values) const =0;
    
};

/* 
 * Derived Primitive Value class SaliraInt which basically represents integer.
 */

class SaliraInt : public PrimitiveValue {
private:
  int _value;
public:
  SaliraInt(int value) : PrimitiveValue(), _value(value) {}
  virtual void print() const { std::cout << " " << _value << " "; }
  inline int value() { return _value; }
  inline void setValue(int new_value) { _value = new_value;}
  virtual Type getType() const {return S_INT;};
  // Eval
  virtual Expression eval(const std::vector<Expression>& values) const {
    return new SaliraInt(_value);
  }
};

/*
 * Derived Primitive Value class SaliraDouble. Represents double.
 */
class SaliraDouble : public PrimitiveValue {
private:
  double _value;
public:
  SaliraInt(double value) : PrimitiveValue(), _value(value) {}
  virtual void print() const { std::cout << " " << _value << " "; }
  inline double value() { return _value; }
  inline void setValue(double new_value) { _value = new_value;}
  virtual Type getType() const {return S_DOUBLE;};
  // Eval
  virtual Expression eval(const std::vector<Expression>& values) const {
    return new SaliraDouble(_value);
  }  
};

class SaliraList : public Expression {
private:
  Type _type_of_elements;
  std::vector<Expression> _elements;
public:
  SaliraList(Type type) : _type_of_elements(type) {}
  inline virtual bool isToken() const {return false;}
  inline virtual bool isConstant() const {return false;}
    
};

/*
 * Dummy class which will represent arguments in function. More precisely it represent places where arguments
 * should be placed inside of Expressiovn tree.  
 */

class Token : public ExpressionBase {
private:
  int _placement;
public:
  virtual void print() const { std::cout << " Token:" << _placement << " ";}
  virtual bool isToken() const { return true; }
  virtual bool isConstant() const { return false; }
  virtual Expression eval(const std::vector<Expression>& values) const{ 
    // NOTE: Possible problem, not sure yet
    // Inside of recursive iteration one of tokens can be another function, problem is giving aditional 
    // arguments for that function. Possibility of different values vector which next line couldn't solve
    // Again not sure, its 2:46am
    return values[_placement]->eval(values);
  }
  virtual Type getType() const {return S_TOKEN;};
  Token(int place) : _placement(place), ExpressionBase(false) {}
};


#endif // SALIRA_TYPES_H__