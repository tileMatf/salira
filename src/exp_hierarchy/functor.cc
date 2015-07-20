#include "functor.hh"

//////////////////////////////// Constructors //////////////////////////////////

	Functor::Functor(std::string id, std::initializer_list<Expression> list, int 
num)
		: ExpressionBase(), _identifier(id), _num_of_args(num)
	{
		for(Expression item  : list)
			_args.push_back(item);
	}
	Functor::Functor(std::string id, std::vector<Expression>& arr, int num)
		: ExpressionBase(), _identifier(id), _args(arr), _num_of_args(num) {}
	
////////////////////////////////////////////////////////////////////////////////
	
/////////////////////////////// Static Map API /////////////////////////////////

// Variables
	FMap Functor::_map = FMap();
	FMap Functor::_base_functions = FMap();

void Functor::insertInMap(std::string id) throw() {
	if(_map.find(id) == _map.end()){
		_map.insert(std::pair<std::string,bool>(id,true));
	}
	else{
		throw SaliraException(
			std::string(" There is already defined function with given") +
			std::string(" id : ") + id);
	}
}

////////////////////////////////////////////////////////////////////////////////

///////////////////////////// Static Init API //////////////////////////////////

void Functor::initBaseFunctions(){
	// Initialize base functions
	_base_functions.insert(std::pair<std::string,bool>("$ADD",true));
	_base_functions.insert(std::pair<std::string,bool>("$SUB",true));
	_base_functions.insert(std::pair<std::string,bool>("$DIV",true));
	_base_functions.insert(std::pair<std::string,bool>("$MUL",true));
	_base_functions.insert(std::pair<std::string,bool>("$NEG",true));
	
	
	_map.insert(std::pair<std::string,bool>("$ADD",true));
	_map.insert(std::pair<std::string,bool>("$SUB",true));
	_map.insert(std::pair<std::string,bool>("$DIV",true));
	_map.insert(std::pair<std::string,bool>("$MUL",true));
	_map.insert(std::pair<std::string,bool>("$NEG",true));
}

void Functor::gCodeBegin() {
	SaliraWriter& out = SaliraWriter::getInstance();
	out.write("BEGIN");
	out.write("PUSHGLOBAL $PROG");
	out.write("EVAL");
	out.write("PRINT");
	out.write("END");
}
void Functor::gCodeEnd(Expression f) {
	SaliraWriter& out = SaliraWriter::getInstance();
	out.write("GLOBSTART $PROG, 0");
	f->generateGCode();
	out.write("EVAL");
	out.write("UPDATE 1");
	out.write("UNWIND");
	

}
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////// GCode API ////////////////////////////////////

void Functor::baseGcode(bool run) const{
	SaliraWriter& out = SaliraWriter::getInstance();
	// NOTE: Is always same order of calling? Is there need for forward one?
	//run = !run;
	if (run == true) {
		std::vector<Expression>::const_reverse_iterator iter = _args.rbegin();
		std::vector<Expression>::const_reverse_iterator itere = _args.rend();
		while(iter != itere){
			(*iter)->generateGCode();
			++iter;
		}
	}
	else {
		std::vector<Expression>::const_iterator iter = _args.begin();
		std::vector<Expression>::const_iterator itere = _args.end();
		while(iter != itere){
			(*iter)->generateGCode();
			++iter;
		}
	}
	out.write(std::string("PUSHGLOBAL ") + _identifier);
	out.write("MKAP");
}

void Functor::gCodeDeclaration() const{
	SaliraWriter& out = SaliraWriter::getInstance();
	out.write("GLOBSTART " + _identifier + ", " + std::to_string(_num_of_args));
	/*
		* NOTE: Heavy assumption that parser would insert correct tokens on right
		* place.
		*/
	for(int i = 0,size = _args.size(); i < size; ++i){
		_args[i]->generateGCode();
	}
	out.write("UPDATE "+std::to_string(_num_of_args+1));
	out.write("POP "+std::to_string(_num_of_args));
	out.write("UNWIND");
}
	
void Functor::gCodeCall() const{
	SaliraWriter& out = SaliraWriter::getInstance();
	std::vector<Expression>::const_reverse_iterator iter = _args.rbegin();
	while(iter != _args.rend()){
		(*iter)->generateGCode();
		++iter;
	}
	out.write("PUSHGLOBAL "+_identifier);
	out.write("MKAP");
}

void Functor::generateGCode() {
	std::cout << "--------------------" << std::endl;
	SaliraWriter& out = SaliraWriter::getInstance();	
	if(isDefined()){
		if(isBase()){
			baseGcode();
		}
		else{
			gCodeCall();
		}
	}
	else{
		if(_num_of_args > 0)
		Token:: changeSize(_num_of_args);
		gCodeDeclaration();
		Functor::insertInMap(_identifier);
		Token:: changeSize(0);
	}
}

////////////////////////////////////////////////////////////////////////////////

bool Functor::isDefined() const {
	if(Functor::_map.find(_identifier) == Functor::_map.end()){
		return false;
	}
	else{
		return true;
	}
}

bool Functor::isBase() const {
	if(Functor::_base_functions.find(_identifier) == 
Functor::_base_functions.end()){
		return false;
	}
	else{
		return true;
	}
}