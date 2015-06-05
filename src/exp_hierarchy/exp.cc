/*
 *  Hierarchy of classe for creating expressions. Purpose is defining
 *  proper API for representating lambda (and other) expressions in
 *  function oriented enviroment.
 * 
 */

#include "auto_load.hh"
#include "salira_dev.hh"

int main() {
  Functor::initBaseFunctions();
  Expression p = new Token(0,ExpressionBase::S_INT);
  std::vector<Expression> _args;
  std::vector<Expression> tint;
  tint.push_back(p);
  // 1
  Expression m1 = new SaliraInt(1);
  Expression m2 = new SaliraInt(1);
  _args.push_back(m2);
  // end of recursion, pattern match
  SaliraUtility::insertFunctionInPool("f", m1, _args);
  
  //recursive declaration
  Expression min = new Functor("minus", {p, m1});
  Expression fp = new Functor("f",{min});
  Expression f = new Functor("plus",{p,fp});
  SaliraUtility::insertFunctionInPool("f", f, tint);
  Expression testInput = new SaliraInt(5);
  _args.clear();
  _args.push_back(testInput);
  SaliraDev::MapPrint();
  std::cout << " Test : " << ((SaliraInt*)f->eval(_args))->value() << std::endl;
  
  /*
  // insert f 1 = 1
  SaliraUtility::insertFunctionInPool("f", m1, _args);
  
  // insert f n = n + f (n-1)
  Expression f = new Functor("plus",{p})
  
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
  */
//SaliraDev::MapPrint();
  std::cout << "Test" << std::endl;
  return 0;
}