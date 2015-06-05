#include "metafunc.hh"

FuncDecl MetaFunc::find(std::vector<Expression> args) throw(){
    // Main strategy return first fitted, not most fitted
    bool jump_break = false;
    int match = -1;
    // In case ther is only one declarations
    if (_declarations.size() == 1){
      return _declarations[0].f;
    }
    // Searching
    for (auto item : _declarations){
      jump_break = false;
      if(item.args.size() != args.size()){
	throw SaliraException("Not enough arguments!");
      }
      int i = 0;
      for (i = 0; i < args.size(); ++i){
	Expression valued = args[i]->eval(args);
	// If token is one of arguments of declarations, then we have definite match
	if (item.args[i]->isToken()){
	  if(item.args[i]->getType() == valued->getType()){
	  // NOTE: Possible checking of type mismatch (example: int input arg, doulbe omnivalue Token)
	    continue;
	  }
	}
	// if not token
	else{
	  // check if args have same type
	  if(item.args[i]->getType() == valued->getType()){
	    // check value
	    // Check for type (double or int), it could be more minimalistic but
	    // for starters it should do...
	    if(item.args[i]->getType() == ExpressionBase::S_INT){
	      if(((SaliraInt*)item.args[i])->value() == ((SaliraInt*)valued)->value()){
		continue;
	      }
	    }
	    else {
	      if(((SaliraDouble*)item.args[i])->value() == ((SaliraDouble*)valued)->value()){
		continue;
	      }
	    }
	  }
	}
	jump_break = true;
	break;
      }
      // Handling  for loop results, if breaked or not.
      // If for loop is breaked than continue searching through other iteration
      if(jump_break){
	jump_break = false;
	continue;
      }
      // or return targeted functor declaration.
      else{
	SaliraLog::log("Matched!");
	for(auto item : args){
	  SaliraLog::log("\t" + item->print());
	}
	return item.f;
      }
    }
    throw SaliraException("No suitable functor declaration!");
}


void MetaFunc::addDeclaration(std::vector<Expression> args, FuncDecl f){
    FuncTypes t(f, args);
    _declarations.push_back(t);
}  