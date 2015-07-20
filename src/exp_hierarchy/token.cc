#include "token.hh"

int Token::_size = 0;
	Token::Token(int place) 
		: _placement(place), ExpressionBase(){}
	std::string Token::print() const {return std::string("SaliraToken");}
  ExpressionBase::Type Token::getType() const {return ExpressionBase::S_TOKEN;}
	void Token::generateGCode() {
		SaliraWriter& out = SaliraWriter::getInstance();
		// TODO:  Check if calculating "index" of token is correct
		out.write("PUSH "+std::to_string(Token::size() - _placement - 1));
	} 
	void Token::changeSize(int size){
		Token::_size = size;
	}