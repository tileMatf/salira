#ifndef FUNCTOR_H__
#define FUNCTOR_H__

#include "expression.hh"
#include "salira_types.hh"

/*
 * Functor, class for representating functions.
 * 
 * Ground for more complex function mechanism. 
 * It should have for starting test version just checking if function is defined. 
 * Further it should be implemented testing for polymorph functions and argument checking.
 * 
 * TODO: Implement argument number check
 * TODO: Implement polymorph 
 * 
 */
class Functor : public ExpressionBase {
private:
  static FuncMap functions;
public:
  // Operation which will be used often, so it is promoted to method, in case if  
  // mechanism is changed.
  static bool isFunctionDefined(std::string identifier);
  // Inserting new function
  static bool insertFunc(std::string identifier, FuncDecl f);
  // Initialize basic functions. Filling FuncMap with functions. 
  // NOTE: Similar mechanism can be used for including another .hs file.
  static bool initBaseFunctions();
  // Reaching for function from map.
  static FuncDecl getFunc(std::string identifier) throw();
private:
  std::string _identifier;
  std::vector<Expression> _arguments;
public:
  Functor(std::string id, std::initializer_list<Expression> list);
  
  void addToArguments(Expression t){
    _arguments.push_back(t);
  }
  
  void changeArgument(int index, Expression t){
	if(index > _arguments.size()){
	  throw SaliraException("There is no arguments with given index");
	}
	_arguments[index] = t;
  }
  // Check functions
  inline virtual bool isToken() const { return false; }
  inline virtual bool isConstant() const { return true; }
  virtual Expression eval(const std::vector<Expression>& values) const;
};


#endif // FUNCTOR_H__