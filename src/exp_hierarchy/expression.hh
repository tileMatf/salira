#ifndef EXPRESSION_H__
#define EXPRESSION_H__

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <functional>
#include "SaliraExceptions.hh"
#include "salira_writter.hh"

// Forward declaration of Expression so I can write bunch of aliases.
class ExpressionBase;
/*
 * Declaring map with functions. At the moment its based around expression (or more precise evaluating expression).
 * Need to be modified if functions should build somtething else instead of expression, GCode for example
 */
using Expression = ExpressionBase*;
//using Expression = std::shared_ptr<ExpressionBase>;
using FuncDecl = std::function< Expression ( std::vector<Expression> ) >;


/*
 * Base type, 
 */
class ExpressionBase{
private:
  // Types T_INT, T_DOUBLE, T_LIST represent Token type;
  bool _is_constant;  
public:
  enum Type {S_INT, S_DOUBLE, S_FUNCTOR, S_TOKEN, T_INT, T_DOUBLE, T_LIST};
  ExpressionBase(bool t = false):_is_constant(t){
    
  }
  virtual bool isConstant() const = 0;
  virtual bool isToken() const = 0;
  virtual std::string print() const = 0;
  virtual Type getType() const = 0;
  virtual Expression eval(const std::vector<Expression>& values)const = 0;
  virtual void generateGCode(const SaliraWritter &out) const = 0; 
  
  virtual ~ExpressionBase() {}
};




#endif // EXPRESSION_H__