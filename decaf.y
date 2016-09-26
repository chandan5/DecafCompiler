%{
#include <cstdio>
#include <iostream>
#include <fstream>
using namespace std;

    extern "C" int yylex();
	extern "C" int yyparse();
	extern "C" FILE * yyin;
	extern int yylineno;
	void yyerror(const char *s);
%}

%union {
    int ival;
    char *sval;
}

%token SEMICOLON
%token OPEN_PARANTHESIS
%token CLOSE_PARANTHESIS
%token OPEN_SQUAREBRACKET
%token CLOSE_SQUAREBRACKET
%token OPEN_CURLYBRACE
%token CLOSE_CURLYBRACE

%token MAIN
%token FALSE
%token INT
%token BOOLEAN
%token TRUE
%token EQUAL
%token PLUS MINUS
%token MULTIPLY DIVIDE MODULO

// TODO prescedence
%token <sval> IDENTIFIER
%token <ival> INT_VALUE

%%
    program: INT MAIN OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_CURLYBRACE
                declarations statements CLOSE_CURLYBRACE {cout << "Program encountered" << endl;}
    declarations :  declaration
                |   declaration declarations
    statements :    statement
                |   statement statements
    declaration :   type IDENTIFIER SEMICOLON {cout << "Id=" << $2 << endl;}
                |   type IDENTIFIER OPEN_SQUAREBRACKET INT_VALUE CLOSE_SQUAREBRACKET SEMICOLON {cout << "Id=" << $2 << endl << "Size=" << $4 << endl;}
    statement : SEMICOLON
            |   IDENTIFIER EQUAL expression SEMICOLON {cout << "Assignment operation encountered" << endl;}
            |   IDENTIFIER OPEN_SQUAREBRACKET expression CLOSE_SQUAREBRACKET EQUAL expression SEMICOLON {cout << "Assignment operation encountered" << endl;}
    expression : term
            |   term PLUS term {cout << "Addition expression encountered" << endl;}
            |   term MINUS term {cout << "Subtraction expression encountered" << endl;}
    term :  factor
        |   factor MULTIPLY factor {cout << "Multiplication expression encountered" << endl;}
        |   factor DIVIDE factor {cout << "Division expression encountered" << endl;}
        |   factor MODULO factor {cout << "Modulus expression encountered" << endl;}
    // use test for debugging
    //test:  IDENTIFIER {cout << "found Identifier" << endl;}
    factor :  IDENTIFIER
        |   IDENTIFIER OPEN_SQUAREBRACKET expression CLOSE_SQUAREBRACKET
        |   literal
        |   OPEN_PARANTHESIS expression CLOSE_PARANTHESIS
    literal :INT_VALUE {cout << "Integer literal encountered\nValue=" << $1 << endl;}
            |bool_value
    bool_value  :TRUE {cout << "Boolean literal encountered\nValue=" << "true" << endl;}
                |FALSE {cout << "Boolean literal encountered\nValue=" << "false" << endl;}
    type :  INT {cout << "Int declaration encountered" << endl;}
        |   BOOLEAN {cout << "Boolean declaration encountered" << endl;}


%%

void yyerror (const char *s) {
    cout << "Syntax error" << endl;
	// std::cerr << "Parse Error on Line : " << yylineno << std::endl << "Message : " << s << std::endl;
	exit(-1);
}

int main(int argc, char*argv[]) {
     if ( argc != 2 ) /* argc should be 2 for correct execution */
     {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
        return -1;
     }
     ofstream out("bison_output.txt");
     streambuf *coutbuf = std::cout.rdbuf(); //save old buf
     cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    // We assume argv[1] is a filename to open
        FILE *myfile = fopen( argv[1], "r" );
        if (!myfile) {
            cout << "Can't open file: " << argv[1] << endl;
            return -1;
        }

        // set lex to read from it instead of defaulting to STDIN:
        yyin = myfile;

    do {
        yyparse();
    } while (!feof(yyin));
    cout.rdbuf(coutbuf); //reset to standard output again
    cout << "Success" << endl;
    return 0;
}
