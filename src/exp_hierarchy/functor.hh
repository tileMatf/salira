#ifndef FUNCTOR_H__
#define FUNCTOR_H__

#include "expression.hh"
#include "salira_types.hh"
#include "metafunc.hh"
#include "salira_log.hh"

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
 * NOTE: Need to enhance mechanism so it can support pattern matching, polymorphism and type conversion.
 * Central func pool need to have more  informations and think way how can pattern matching be realized easily. 
 * And also most critical part, how to ensure that newly made Expressions will be part of that. 
 * 
 */
// 
using FuncMap = std::unordered_map<std::string, MetaFunc>;

class Functor : public ExpressionBase {
friend class SalirDev;
public:
  static FuncMap functions;
public:
  
  // Operation which will be used often, so it is promoted to method, in case if  
  // mechanism is changed.
  static bool isFunctionDefined(std::string identifier);
  // Inserting new function
  static bool insertFunc(std::string identifier, FuncDecl f, std::vector<Expression> args);
  // Initialize basic functions. Filling FuncMap with functions. 
  // NOTE: Similar mechanism can be used for including another .hs file.
  static bool initBaseFunctions();
  // Reaching for function from map.
  static FuncDecl getFunc(std::string identifier, std::vector<Expression> args) throw();
private:
  std::string _identifier;
  std::vector<Expression> _arguments;
public:
  Functor(std::string id, std::initializer_list<Expression> list);
  Functor(std::string id, std::vector<Expression> args);
  
  // Adding additional argument to arguments
  // Intention: So functor can be modified through parsing expression, translation for parsing purposes
  inline void addToArguments(Expression t){ _arguments.push_back(t); }
  
  // Setter and getter for identifier
  inline void setIdentifier(std::string s) {_identifier = s;}
  inline std::string identifier() {return _identifier;}
  
  void changeArgument(int index, Expression t){
	if(index > _arguments.size()){
	  throw SaliraException("There is no arguments with given index");
	}
	_arguments[index] = t;
  }
  
  
  virtual std::string print() const;
  // Check functions
  inline virtual bool isToken() const { return false; }
  inline virtual bool isConstant() const { return true; }
  virtual Expression eval(const std::vector<Expression>& values) const;
  virtual Type getType() const {return S_FUNCTOR;};
  virtual ~Functor() {
    // Deleting memory from arguments
    for (auto item : _arguments){
      delete item;
    }
  }
};


#endif // FUNCTOR_H__