#ifndef SALIRA_UTILITY_H__
#define SALIRA_UTILITY_H__

/* 
 * Class intended to be set of static method which will represent utilities for Salira project.
 * Its much easier to 
 */

#include "expression.hh"
#include "functor.hh"
#include "SaliraExceptions.hh"

class SaliraUtility{
private:
  // Just to make sure that nobody will create object of SaliraUtility
  SaliraUtility(){
    // Once more, just in case
    throw SaliraException("Invalid constructor called: SaliraUtility");
  }
public:
// Make lambda from expression
  static FuncDecl makeLambda(Expression e){
    // Creating lambda function from expression e, reason why I used lambdas
    // are those that lambda can capture elements by value (or reference) so 
    // its much easier to write, instead of calling overloaded operator() on functor
    // and its much more flexible if want to write your own extension to basic functions.
    FuncDecl f = [e](std::vector<Expression> values){
      return e->eval(values);
    };
    return f;
  }
  
  // Wrapper for easier insertion. 
  static void insertFunctionInPool(std::string identifier, Expression e){
    Functor::insertFunc(identifier, SaliraUtility::makeLambda(e));
  }
  
  
// Write extractors, basically need to write utilities which will extract values from 
// Expression. Only purpose is to make API more usefull and shorter.
  static int extractValueInt(){}
};


#endif //SALIRA_UTILITY_H__