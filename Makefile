DECAF:
	bison -d --verbose decaf.y -o decaf.tab.cc
	flex -o lex.yy.cc decaf.l
	g++ decaf.tab.cc lex.yy.cc -ll -o decaf
clean:
	rm decaf.tab.* lex.yy.cc decaf.output
