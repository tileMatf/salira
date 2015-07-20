all:
	bison -v -d lambda.y
	flex lambda.l
	g++ -std=c++11 lex.yy.cc main.cpp lambda.tab.c ../exp_hierarchy/functor.cc ../exp_hierarchy/token.cc -o proba


