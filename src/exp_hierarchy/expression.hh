#ifndef EXPRESSION_H__
#define EXPRESSION_H__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include "SaliraExceptions.hh"

// Forward declaration of Expression so I can write bunch of aliases.
class ExpressionBase;
/*
 * Declaring map with functions. At the moment its based around expression (or more precise evaluating expression).
 * Need to be modified if functions should build somtething else instead of expression, GCode for example
 */
using Expression = ExpressionBase*;
//using Expression = std::shared_ptr<ExpressionBase>;
using FuncDecl = std::function< Expression ( std::vector<Expression> ) >;
using FuncMap = std::unordered_map<std::string, FuncDecl>;

/*
 * Base type
 */
class ExpressionBase{
private:
  enum Type {S_INT, S_DOUBLE, S_FUNCTOR, S_TOKEN}
  bool _is_constant;  
public:
  ExpressionBase(bool t = false){
    _is_constant = t;
  }
  inline virtual bool isConstant() const = 0;
  inline virtual bool isToken() const = 0;
  virtual void print() const = 0;
  virtual Type getType() const = 0;
  virtual Expression eval(const std::vector<Expression>& values)const = 0;
  
  virtual ~Expression() {}
};

#endif // EXPRESSION_H__