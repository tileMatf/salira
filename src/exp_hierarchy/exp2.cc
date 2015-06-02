/*
 *  Hierarchy of classe for creating expressions. Purpose is defining
 *  proper API for representating lambda (and other) expressions in
 *  function oriented enviroment.
 * 
 */

#include "auto_load.hh"

int main() {
  Functor::initBaseFunctions();
  Expression p = new Token(0,ExpressionBase::T_INT);
  Expression p1 =new Token(1,ExpressionBase::T_INT);
  std::vector<Expression> _args;
  _args.push_back(p);
  _args.push_back(p1);
  
  
  Expression pt1 = new SaliraInt(7);
  Expression pt2 = new SaliraInt(5);
  
  Expression ptt1 = new SaliraInt(7);
  Expression ptt2 = new SaliraInt(4);
  
  std::vector<Expression> test {pt1,pt2};
  std::vector<Expression> test1 {ptt1, ptt2};
  Expression p2 = new SaliraInt(8);
  Expression e1 = new Functor("minus", {p,p1});
  Expression e = new Functor("plus", {p2, e1});
  SaliraUtility::insertFunctionInPool("test", e,_args);
  Expression result = e->eval(test);
  std::cout << ((SaliraInt*)result)->value() << std::endl;
  
  result = e->eval(test1);
  std::cout << ((SaliraInt*)result)->value() << std::endl;
  
  std::cout << "Test" << std::endl;
  return 0;
}