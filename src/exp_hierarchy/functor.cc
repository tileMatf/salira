#include "functor.hh"
#include "salira_utility.hh"

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
  
FuncDecl Functor::getFunc(std::string identifier, std::vector<Expression> args)  
throw(){
    // Basic check if function is defined.0
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
	// TODO: Define $Prog functor;
  if(Functor::functions.size() != 0)
    return true;
  
  // Initializing G code
  out.write("BEGIN; \nPUSHGLOBAL $Prog; \nEVAL; \nPRINT; \nEND;\n");
  // plus
  FuncDecl plus = [](const SaliraWritter& out, std::vector<Expression> values){
		values[0]->generateGCode(out, values);
		values[1]->generateGCode(out, values);
		out.write("PUSHGLOBAL $ADD; \n");
	};
  std::vector<Expression> tempp;
  tempp.push_back(new Token(0, ExpressionBase::T_INT));
  tempp.push_back(new Token(1, ExpressionBase::T_INT));
  Functor::insertFunc("$ADD", plus, tempp);
  // minus
  FuncDecl minus = [](const SaliraWritter& out,std::vector<Expression> values){
		values[0]->generateGCode(out, values);
		values[1]->generateGCode(out, values);
		out.write("PUSHGLOBAL $SUB; \n");
	};
  std::vector<Expression> tempm;
  tempm.push_back(new Token(0, ExpressionBase::T_INT));
  tempm.push_back(new Token(1, ExpressionBase::T_INT));
  Functor::insertFunc("$SUB", minus, tempm);
  // Multiplication
  FuncDecl mult = [](const SaliraWritter& out, std::vector<Expression> values){
		values[0]->generateGCode(out, values);
		values[1]->generateGCode(out, values);
		out.write("PUSHGLOBAL $MUL; \n");
	};
  std::vector<Expression> tempmu;
  tempmu.push_back(new Token(0, ExpressionBase::T_INT));
  tempmu.push_back(new Token(1, ExpressionBase::T_INT));
  Functor::insertFunc("$MUL", mult, tempmu);
  // Division
  FuncDecl div = [](const SaliraWritter& out, std::vector<Expression> values){ 
	
		values[0]->generateGCode(out, values);
		values[1]->generateGCode(out, values);
		out.write("PUSHGLOBAL $DIV; \n");
	};
  std::vector<Expression> tempd;
  tempd.push_back(new Token(0, ExpressionBase::T_INT));
  tempd.push_back(new Token(1, ExpressionBase::T_INT));  
  Functor::insertFunc("$DIV", div, tempd);
  
	FuncDecl neg = [](const SaliraWritter& out, std::vector<Expression> values){ 
	
		values[0]->generateGCode(out, values);
		out.write("PUSHGLOBAL $NEG; \n");
	};
  std::vector<Expression> tempn;
  tempd.push_back(new Token(0, ExpressionBase::T_INT));
  Functor::insertFunc("$NEG", neg, tempn);
	
}

// Printing on console functor, at least, identifier for now.
std::string Functor::print() const {
  return std::string("Functor: ") + _identifier;
}

void Functor::generateGCodeStart(const SaliraWritter& out, 
std::vector<Expression> 
values, std::string name){
	// There is definition in map pool
		out.write("GLOBSTART "+name + ", " + std::to_string(values.size()) + 
";\n");
		Functor::getFunc(_identifier, _arguments)(out, _arguments);
		out.write("UPDATE "+std::to_string(values.size()+1) +";\n");
		out.write("POP "+std::to_string(values.size()) +";\n");
		out.write("UNWIND;\n");
		
}

// Generating G code
void Functor::generateGCode(const SaliraWritter &out,std::vector<Expression>
values){
		std::string temp = "";
		std::vector<Expression>::reverse_iterator iter = _arguments.rbegin();
		while(iter != _arguments.rend()){
			(*iter)->generateGCode(out, values);
			++iter;
		}
		out.write("PUSHGLOBAL "+_identifier+";\n");
		out.write("MKAP; \n");
}

// API
// Problem: Need to check if arguments need to evaluate
Expression Functor::eval(const std::vector<Expression>& values)const { 
    /*
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
		*/
		Functor* ret = new Functor("dummy", std::vector<Expression>());
    return ret;
  }