DECAF:
	bison -d --verbose decaf.y -o decaf.tab.cc
	flex -o lex.yy.cc decaf.l
	g++  decaf.tab.cc lex.yy.cc main.cpp -o decaf -flto -ll --std=c++11 `llvm-config --cppflags --libs all --ldflags`

clean:
	rm decaf.tab.* lex.yy.cc decaf.output
