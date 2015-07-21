#ifndef TOKEN__H_
#define TOKEN__H_

/*
 * Token represents input arguments of functions. Basically
 * they are placeholders where our input values will be when 
 * function call happen.
 */

#include "exp.hh"

class Token : public ExpressionBase{
private:
	int _placement;
	/*
	 * Static data to store number of all arguments.
	 * Reason for this implementation (hack) is bad side of yacc
	 * parser, which doesn't know how many arguments there are when
	 * creating each token.
	 */
	static int _size;
public:
	Token(int place);
	virtual std::string print() const;
  virtual ExpressionBase::Type getType() const;
	virtual void generateGCode();
	static void changeSize(int);
	static int size() {return _size;}
#ifdef DEBUG
	virtual void tree(int lvl) const;
#endif
};

#endif // TOKEN__H_