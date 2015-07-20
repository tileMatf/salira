#ifndef FUNCTOR_H__
#define FUNCTOR_H__

#include "exp.hh"
#include <vector>
#include <initializer_list>

using FMap = std::unordered_map<std::string,bool>;

class Functor : public ExpressionBase{
private:
	static FMap _map;
	static FMap _base_functions;
	std::vector<Expression> _args;
	std::string _identifier;
	int _num_of_args;
public:
	Functor(std::string, std::initializer_list<Expression>, int = 0);
	Functor(std::string, std::vector<Expression>& , int = 0);
	
	static void insertInMap(std::string ) throw();	
	static void initBaseFunctions();
	
	static void gCodeBegin();
	static void gCodeEnd(Expression);
	
	virtual std::string print() const {return std::string("Functor")+_identifier;}
	virtual Type getType() const {return ExpressionBase::S_FUNCTOR;};
  virtual void generateGCode() const;

private:
	// NOTE: Find better place for this;
	
	
	bool isDefined() const;
	bool isBase() const;
	// GCode
	void gCodeDeclaration() const;
	void gCodeCall() const;
	void baseGcode(bool = true) const;
};

#endif // FUNCTOR_H__