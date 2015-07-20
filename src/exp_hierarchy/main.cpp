#include <iostream>
#include "exp.hh"
#include "functor.hh"

int main(int argc, char **argv) {
		SaliraWriter& out = SaliraWriter::getInstance();
    Functor::gCodeBegin();
		Functor::initBaseFunctions();

		Expression tokenX = new Token(0);
		Expression tokenY = new Token(1);
		
		Expression ten = new SaliraInt(10);
		Expression mul = new Functor("$MUL", {ten,tokenX});
		Expression plus = new Functor("$ADD",{mul, tokenY});
		Expression g = new Functor("$G",{plus}, 2);
		Token::changeSize(2);
		g->generateGCode();
		Functor::insertInMap("$G");
		
		Expression one = new SaliraInt(1);
		Expression my = new Functor("$SUB", {tokenX,one});
		Expression mx = new Functor("$SUB", {tokenY, one});
		Expression gm = new Functor("$G", {mx,my});
		Expression gd = new Functor("$G", {tokenX, tokenY});
		Expression fplus = new Functor("$ADD", {gd, gm});
		Expression f = new Functor("$F", {fplus}, 2);
		f->generateGCode();
		Functor::insertInMap("$F");
		
		Expression three = new SaliraInt(3);
		Expression four = new SaliraInt(4);
		
		Expression ff = new Functor("$F", {three, four});
		
		Functor::gCodeEnd(ff);
    return 0;
}
