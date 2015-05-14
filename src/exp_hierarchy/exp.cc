/*
 *  Hierarchy of classe for creating expressions. Purpose is defining
 *  proper API for representating lambda (and other) expressions in
 *  function oriented enviroment.
 * 
 */

#include "expression.hh"
#include "functor.hh"
#include "salira_types.hh"

int main() {
  Functor::initBaseFunctions();
  Expression p = Expression(new SaliraInt(6));
  Expression p1 = Expression(new SaliraInt(7));
  Expression p2 = Expression(new SaliraInt(8));
  Expression e1 = Expression (new Functor("minus", {p,p1}));
  Expression e = Expression(new Functor("plus", {p2, e1}));
 
  Expression result = e->eval(std::vector<Expression>());
  std::cout << ((SaliraInt*)result.get())->value() << std::endl;
  std::cout << "Test" << std::endl;
  return 0;
}