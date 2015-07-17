#include "functor.hh"

// Constructor
Functor::Functor(std::string id, std::initializer_list<Expression> list) 
    : _identifier(id), ExpressionBase(false) {
      for(Expression item  : list){
	_arguments.push_back(item);
      }
}
Functor::Functor(std::string id, std::vector<Expression> args)
: _identifier(id), ExpressionBase(false),  _arguments(args) {}

// Static interface

  // vars
FuncMap Functor::functions = FuncMap();
  
  // API
bool Functor::isFunctionDefined(std::string identifier){
    return Functor::functions.find(identifier) == Functor::functions.end() ? false : true; 
  }
  
FuncDecl Functor::getFunc(std::string identifier, std::vector<Expression> args) throw(){
    // Basic check if function is defined.
    if(!Functor::isFunctionDefined(identifier)){
      throw SaliraException("Function doesn't exist! Id: = " + identifier);
    }
    else{
      return Functor::functions[identifier].find(args);
    }
}

bool Functor::insertFunc(std::string identifier, FuncDecl f, std::vector<Expression> args){
    if(Functor::isFunctionDefined(identifier)){
      Functor::functions[identifier].addDeclaration(args,f);
      return false;
    }
    else {
      MetaFunc t{};
      t.addDeclaration(args, f);
      Functor::functions.insert(std::pair<std::string, MetaFunc>(identifier, t));
      return true;
    }
}
  
bool Functor::initBaseFunctions(const SaliraWritter &out){  
  // NOTE: Think about moving this into type's class, it should definetly make more sense and be
  // more readable.
  if(Functor::functions.size() != 0)
    return true;
  
  // Initializing G code
  out.write("BEGIN; \nPUSHGLOBAL $Prog; \nEVAL; \nPRINT; \nEND;\n");
  // plus
  FuncDecl plus = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0])->value() + ((SaliraInt*)values[1])->value()
							    )
							);};
  std::vector<Expression> tempp;
  tempp.push_back(new Token(0, ExpressionBase::T_INT));
  tempp.push_back(new Token(1, ExpressionBase::T_INT));
  Functor::insertFunc("plus", plus, tempp);
  // minus
  FuncDecl minus = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0])->value() - ((SaliraInt*)values[1])->value()
							    )
							);};
  std::vector<Expression> tempm;
  tempm.push_back(new Token(0, ExpressionBase::T_INT));
  tempm.push_back(new Token(1, ExpressionBase::T_INT));
  Functor::insertFunc("minus", minus, tempm);
  // Multiplication
  FuncDecl mult = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0])->value() * ((SaliraInt*)values[1])->value()
							    )
							);};
  std::vector<Expression> tempmu;
  tempmu.push_back(new Token(0, ExpressionBase::T_INT));
  tempmu.push_back(new Token(1, ExpressionBase::T_INT));
  Functor::insertFunc("mult", mult, tempmu);
  // Division
  FuncDecl div = [](std::vector<Expression> values){ return Expression(
							new SaliraInt(
							  ((SaliraInt*)values[0])->value() / ((SaliraInt*)values[1])->value()
							    )
							);};
  std::vector<Expression> tempd;
  tempd.push_back(new Token(0, ExpressionBase::T_INT));
  tempd.push_back(new Token(1, ExpressionBase::T_INT));  
  Functor::insertFunc("div", mult, tempd);
  
}

// Printing on console functor, at least, identifier for now.
std::string Functor::print() const {
  return std::string("Functor: ") + _identifier;
}

// Generating G code
void Functor::generateGCode(const SaliraWritter &out) const
{
  out.write("GLOBSTART " + _identifier + ", " + std::to_string(_arguments.size()) + ";\n" );
  R(out);
}

void Functor::R(const SaliraWritter &out) const
{
  C(out, _arguments);
  out.write("UPDATE " + std::to_string(_arguments.size()+1) + ";\nPOP " + std::to_string(_arguments.size()) + ";\nUNWIND;\n");
}

void Functor::C(const SaliraWritter &out, const std::vector<Expression> &values) const
{
  for(auto i = 0 ; i < values.size(); i++)
    switch(values[i]->getType())
    {
      case S_TOKEN: 
      {
	out.write("PUSH " + std::to_string(((SaliraInt*)values[i])->value()) + ";\n");
      }
      
    }
    
}
// API
// Problem: Need to check if arguments need to evaluate
Expression Functor::eval(const std::vector<Expression>& values)const { 
    std::vector<Expression> mid_result;
    for(auto item : _arguments){
      mid_result.push_back(item->eval(values));
    }
    SaliraLog::log(_identifier);
    SaliraLog::log("Evaluated args: ");
    for (auto item : mid_result){
      SaliraLog::log("\t" + item->print());
    }
    SaliraLog::log("Name " + _identifier);
    return Functor::getFunc(_identifier, mid_result)(mid_result);
  }