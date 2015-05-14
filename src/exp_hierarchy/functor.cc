#include "functor.hh"

// Constructor
Functor::Functor(std::string id, std::initializer_list<Expression> list) 
    : _identifier(id), ExpressionBase(false) {
      for(Expression item  : list){
	_arguments.push_back(item);
      }
}

// Static interface

  // vars
FuncMap Functor::functions = FuncMap();
  
  // API
bool Functor::isFunctionDefined(std::string identifier){
    return Functor::functions.find(identifier) == Functor::functions.end() ? false : true; 
  }
  
FuncDecl Functor::getFunc(std::string identifier) throw(){
    // Basic check if function is defined.
    if(!Functor::isFunctionDefined(identifier)){
      throw SaliraException("Function doesn't exist!");
    }
    else{
      return Functor::functions[identifier];
    }
}

bool Functor::insertFunc(std::string identifier, FuncDecl f){
    if(Functor::isFunctionDefined(identifier)){
      // Possibility to throw exception.
      return false;
    }
    else {
      Functor::functions.insert(std::pair<std::string, FuncDecl>(identifier, f));
      return true;
    }
}
  
bool Functor::initBaseFunctions(){  
  // plus
  FuncDecl plus = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0].get())->value() + ((SaliraInt*)values[1].get())->value()
							    )
							);};
  Functor::insertFunc("plus", plus);
  // minus
  FuncDecl minus = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0].get())->value() - ((SaliraInt*)values[1].get())->value()
							    )
							);};
  Functor::insertFunc("minus", minus);
}


// API
// Problem: Need to check if arguments need to evaluate
Expression Functor::eval(const std::vector<Expression>& values) { 
    std::cout << _identifier << std::endl;
    std::vector<Expression> mid_result;
    for(auto item : _arguments){
      mid_result.push_back(item->eval(values));
    }
    return Functor::getFunc(_identifier)(mid_result);
  }