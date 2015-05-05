all:
	bison -v -d lambda.y
	flex lambda.l
	g++ -std=c++11 lex.yy.cc main.cpp lambda.tab.c -o lambda


