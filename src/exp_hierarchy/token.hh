#ifndef TOKEN__H_
#define TOKEN__H_

#include "exp.hh"

class Token : public ExpressionBase{
private:
	int _placement;
	// Hack to test if mergin with parser is correct
	static int _size;
public:
	Token(int place);
	virtual std::string print() const;
  virtual ExpressionBase::Type getType() const;
	virtual void generateGCode();
	static void changeSize(int);
	static int size() {return _size;}
};

#endif // TOKEN__H_