#include <iostream>
#include <cstdio>
#include <fstream>
#include "PrintVisitor.cpp"
extern "C" FILE *yyin;
extern "C" int yyparse();

ASTProgram * astRoot;
int error_count = 0;

using namespace std;

int main(int argc, char*argv[]) {
     if ( argc != 2 ) /* argc should be 2 for correct execution */
     {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
        return -1;
     }

    // We assume argv[1] is a filename to open
        FILE *myfile = fopen( argv[1], "r" );
        if (!myfile) {
            cout << "Can't open file: " << argv[1] << endl;
            return -1;
        }
        // set lex to read from given file (argv[1]) instead of defaulting to STDIN:
        yyin = myfile;
    // parsing till we find EOF
    do {
        yyparse();
    } while (!feof(yyin));
    // if some string(s) were encountered which could not be recognised as a terminal then there was a syntax error
    if(error_count) {
        cout << "Syntax error" << endl;
    }
    else {
        cout << "Success" << endl;
        ofstream out("XML_visitor.txt");
        streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        cout.rdbuf(out.rdbuf()); //redirect std::cout to XML_visitor.txt!

        PrintVisitor * printVisitor = new PrintVisitor(astRoot);
        printVisitor->print();

        cout.rdbuf(coutbuf); //reset to standard output again
    }
    return 0;
}
