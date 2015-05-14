#ifndef EXPRESSION_H__
#define EXPRESSION_H__

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <functional>
#include "SaliraExceptions.hh"

// Forward declaration of Expression so I can write bunch of aliases.
/* Deklaracija osnovne klase */
class ExpressionBase;
/*
 * Declaring map with functions. At the moment its based around expression (or more precise evaluating expression).
 * Need to be modified if functions should build somtething else instead of expression, GCode for example
 */

using Expression = std::shared_ptr<ExpressionBase>;
using FuncDecl = std::function< Expression ( std::vector<Expression> ) >;
using FuncMap = std::unordered_map<std::string, FuncDecl>;

/*
 * Base type
 */
class ExpressionBase : public std::enable_shared_from_this<ExpressionBase> {
private:
  bool _is_constant;  
public:
  ExpressionBase(bool t = false){
    _is_constant = t;
  }
  inline virtual bool isConstant() const = 0;
  inline virtual bool isToken() const = 0;
  virtual Expression eval(const std::vector<Expression>& values) = 0;
  
};

#endif // EXPRESSION_H__