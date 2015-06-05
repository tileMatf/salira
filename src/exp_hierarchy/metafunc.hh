#ifndef METAFUNC_H__
#define METAFUNC_H__

#include "expression.hh"
#include "salira_types.hh"
#include "SaliraExceptions.hh"
#include "salira_log.hh"
/*
 * Class for enabling type checking. It consists addiotionall data for functors.
 * Intention is to encapsulate more than one functor which have more than one implementation (Pattern Matching)
 * 
 */

class MetaFunc {
  friend class SaliraDev;
private:
  /*
   * Private structure for internal saving and easy searchin through functor declarations.
   */
  struct FuncTypes{    
    FuncDecl f;
    std::vector<Expression> args;
    int arg_num;
    FuncTypes(FuncDecl f_, std::vector<Expression> args_) 
      : f(f_),args(args_){
	arg_num = args_.size();
      }
  };
  public:
  std::vector<FuncTypes> _declarations;
public:
  MetaFunc(){}
  ~MetaFunc(){}
  
  /*
   * Adding new declaration of functor. Remove method is not necessary.
   */
  void addDeclaration(std::vector<Expression> args, FuncDecl f);
  /*
   * Finding suitable functor declaration
   */
  FuncDecl find(std::vector<Expression> args) throw();
};



#endif // METAFUNC_H__