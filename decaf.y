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
    char cval;
}

%token SEMICOLON
%token COMMA
%token OPEN_PARANTHESIS
%token CLOSE_PARANTHESIS
%token OPEN_SQUAREBRACKET
%token CLOSE_SQUAREBRACKET
%token OPEN_CURLYBRACE
%token CLOSE_CURLYBRACE

%token CLASS
%token IF
%token ELSE
%token FOR
%token CONTINUE
%token BREAK
%token CALLOUT
%token RETURN
%token VOID
%token FALSE
%token INT
%token BOOLEAN
%token TRUE
%token NOT AND OR
%token EQUALEQUAL NOTEQUAL LESSEQUAL LESSTHAN GREATEREQUAL GREATERTHAN

%token PLUS MINUS
%token MULTIPLY DIVIDE MODULO

// TODO prescedence
%token <sval> IDENTIFIER
%token <sval> STRING_VALUE
%token <cval> CHAR_VALUE
%token <ival> INT_VALUE

%left OR
%left AND
%token EQUAL PLUSEQUAL MINUSEQUAL
%left EQUALEQUAL NOTEQUAL
%nonassoc LESSEQUAL LESSTHAN GREATEREQUAL GREATERTHAN
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO


%%
    program: CLASS IDENTIFIER OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_CURLYBRACE
               field_decls method_decls CLOSE_CURLYBRACE
                {
                   // Check if Identifier is Program
                    cout << "Program encountered" << endl;
                }
    field_decls :  field_decl
                |   field_decl field_decls
    field_decl :   type IDENTIFIER SEMICOLON {cout << "Id=" << $2 << endl;}
               |   type IDENTIFIER OPEN_SQUAREBRACKET INT_VALUE CLOSE_SQUAREBRACKET SEMICOLON {cout << "Id=" << $2 << endl << "Size=" << $4 << endl;}
    method_decls : method_decl
                | method_decl method_decls
    method_decl : method_type IDENTIFIER OPEN_PARANTHESIS params CLOSE_PARANTHESIS block
    method_type : type
                | VOID
    params : param
           | params COMMA param
    param : type IDENTIFIER
    block : OPEN_CURLYBRACE var_decls statements CLOSE_CURLYBRACE
    var_decls : var_decl
            |   var_decl var_decls
    var_decl : type identifiers SEMICOLON
    identifiers : IDENTIFIER
                | identifiers COMMA IDENTIFIER
    statements :    statement
                |   statement statements
    statement : location assign_op expr SEMICOLON
            |   method_call SEMICOLON
            // |   IF OPEN_PARANTHESIS expr CLOSE_PARANTHESIS block ELSE block
            |   IF OPEN_PARANTHESIS expr CLOSE_PARANTHESIS block
            |   FOR IDENTIFIER EQUAL expr COMMA expr block
            |   RETURN expr SEMICOLON
            |   RETURN SEMICOLON
            |   BREAK SEMICOLON
            |   CONTINUE SEMICOLON
            |   block

    method_call : method_name OPEN_PARANTHESIS exprs CLOSE_PARANTHESIS
            |     CALLOUT OPEN_PARANTHESIS STRING_VALUE callout_args CLOSE_PARANTHESIS
    exprs : expr
        |   exprs COMMA expr
    method_name : IDENTIFIER
    location :  IDENTIFIER
            |   IDENTIFIER OPEN_SQUAREBRACKET expr CLOSE_SQUAREBRACKET
    expr :  location
        |   method_call
        |   literal
        |   expr bin_op expr
        |   MINUS expr
        |   NOT expr
        |   OPEN_PARANTHESIS expr CLOSE_PARANTHESIS
    callout_args : callout_arg
                |   callout_args COMMA callout_arg
    callout_arg : expr | STRING_VALUE
    bin_op : arith_op | rel_op | eq_op | cond_op
    arith_op : PLUS | MINUS | MULTIPLY | DIVIDE | MODULO
    rel_op :LESSTHAN
        |   LESSEQUAL
        |   GREATERTHAN
        |   GREATEREQUAL
    eq_op : EQUALEQUAL
        |   NOTEQUAL
    cond_op : AND
            | OR
    assign_op : EQUAL
            |   PLUSEQUAL
            |   MINUSEQUAL
    literal : INT_VALUE {cout << "Integer literal encountered\nValue=" << $1 << endl;}
            | bool_value
            | CHAR_VALUE
    bool_value  :TRUE {cout << "Boolean literal encountered\nValue=" << "true" << endl;}
                |FALSE {cout << "Boolean literal encountered\nValue=" << "false" << endl;}
    type :  INT {cout << "Int field_decl encountered" << endl;}
        |   BOOLEAN {cout << "Boolean field_decl encountered" << endl;}
    // str: STRING_VALUE  { cout << "String literal : "  << $1 << endl; }

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
// statement : SEMICOLON
//         |   IDENTIFIER EQUAL expression SEMICOLON {cout << "Assignment operation encountered" << endl;}
//         |   IDENTIFIER OPEN_SQUAREBRACKET expression CLOSE_SQUAREBRACKET EQUAL expression SEMICOLON {cout << "Assignment operation encountered" << endl;}
//
// expression : term
//         |   term PLUS term {cout << "Addition expression encountered" << endl;}
//         |   term MINUS term {cout << "Subtraction expression encountered" << endl;}
// term :  factor
//     |   factor MULTIPLY factor {cout << "Multiplication expression encountered" << endl;}
//     |   factor DIVIDE factor {cout << "Division expression encountered" << endl;}
//     |   factor MODULO factor {cout << "Modulus expression encountered" << endl;}
// use test for debugging
//test:  IDENTIFIER {cout << "found Identifier" << endl;}

// factor :  IDENTIFIER
//     |   IDENTIFIER OPEN_SQUAREBRACKET expression CLOSE_SQUAREBRACKET
//     |   literal
//     |   OPEN_PARANTHESIS expression CLOSE_PARANTHESIS
