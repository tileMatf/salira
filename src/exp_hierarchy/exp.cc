/*
 *  Hierarchy of classe for creating expressions. Purpose is defining
 *  proper API for representating lambda (and other) expressions in
 *  function oriented enviroment.
 * 
 */

#include "expression.hh"
#include "functor.hh"
#include "salira_types.hh"
#include "salira_utility.hh"

int main() {
  Functor::initBaseFunctions();
  Expression p = Expression(new Token(0));
  Expression p1 = Expression(new Token(1));
  
  
  Expression pt1 = Expression(new SaliraInt(7));
  Expression pt2 = Expression(new SaliraInt(5));
  
  Expression ptt1 = Expression(new SaliraInt(7));
  Expression ptt2 = Expression(new SaliraInt(4));
  
  std::vector<Expression> test {pt1,pt2};
  std::vector<Expression> test1 {ptt1, ptt2};
  Expression p2 = Expression(new SaliraInt(8));
  Expression e1 = Expression (new Functor("minus", {p,p1}));
  Expression e = Expression(new Functor("plus", {p2, e1}));
  SaliraUtility::insertFunctionInPool("test", e);
  Expression result = e->eval(test);
  std::cout << ((SaliraInt*)result.get())->value() << std::endl;
  
  result = e->eval(test1);
  std::cout << ((SaliraInt*)result.get())->value() << std::endl;
  
  std::cout << "Test" << std::endl;
  return 0;
}