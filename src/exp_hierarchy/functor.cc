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
      throw SaliraException("Function doesn't exist! Id: = " + identifier);
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
  // NOTE: Think about moving this into type's class, it should definetly make more sense and be
  // more readable.
  
  // plus
  FuncDecl plus = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0])->value() + ((SaliraInt*)values[1])->value()
							    )
							);};
  Functor::insertFunc("plus", plus);
  // minus
  FuncDecl minus = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0])->value() - ((SaliraInt*)values[1])->value()
							    )
							);};
  Functor::insertFunc("minus", minus);
  // Multiplication
  FuncDecl mult = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0])->value() * ((SaliraInt*)values[1])->value()
							    )
							);};
  Functor::insertFunc("mult", mult);
  // Division
  FuncDecl div = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0])->value() / ((SaliraInt*)values[1])->value()
							    )
							);};
  Functor::insertFunc("div", mult);
  
}


// API
// Problem: Need to check if arguments need to evaluate
Expression Functor::eval(const std::vector<Expression>& values)const { 
    std::vector<Expression> mid_result;
    for(auto item : _arguments){
      mid_result.push_back(item->eval(values));
    }
    return Functor::getFunc(_identifier)(mid_result);
  }