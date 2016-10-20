%{
#include <cstdio>
#include <iostream>
#include <fstream>
#include "AST.h"
using namespace std;

    extern "C" int yylex();
	extern "C" int yyparse();
	extern "C" FILE * yyin;
	extern int yylineno;
    extern ASTProgram * astRoot;
	void yyerror(const char *s);
%}

// yylval is sort of a struct with all the fileds in union
// yylval is used to pass values from lexical analyser to parser

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

%token <sval> IDENTIFIER
%token <sval> STRING_VALUE
%token <cval> CHAR_VALUE
%token <ival> INT_VALUE

%left OR
%left AND
%token EQUAL PLUSEQUAL MINUSEQUAL

// handling precedence
// left indicates left associativity
%left EQUALEQUAL NOTEQUAL
%nonassoc LESSEQUAL LESSTHAN GREATEREQUAL GREATERTHAN
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO
%precedence NOT

%%
    program: CLASS IDENTIFIER OPEN_CURLYBRACE field_decls method_decls CLOSE_CURLYBRACE
        |    CLASS IDENTIFIER OPEN_CURLYBRACE field_decls CLOSE_CURLYBRACE
        |    CLASS IDENTIFIER OPEN_CURLYBRACE method_decls CLOSE_CURLYBRACE
        |    CLASS IDENTIFIER OPEN_CURLYBRACE CLOSE_CURLYBRACE
                {
                   // Check if Identifier is Program
                //    if($2 == "Program")
                        cout << "Program encountered" << endl;
                }

    // When first field_decl is constructed from rule : "field_decl : type identifier_opt_arrs SEMICOLON"
    // It makes a filed_decls using rule : "field_decls :  field_decl".
    // When next field_decl is constructed field_decls is updated using "field_decls : field_decls field_decl"
    field_decls :  field_decl
               |   field_decls field_decl
    field_decl :    type identifier_opt_arrs SEMICOLON

    identifier_opt_arrs : identifier_opt_arr
                    |     identifier_opt_arrs COMMA identifier_opt_arr
    identifier_opt_arr : IDENTIFIER
                    |   IDENTIFIER OPEN_SQUAREBRACKET INT_VALUE CLOSE_SQUAREBRACKET
    method_decls : method_decl
                | method_decls method_decl
    method_decl : type IDENTIFIER OPEN_PARANTHESIS params CLOSE_PARANTHESIS block
                | VOID IDENTIFIER OPEN_PARANTHESIS params CLOSE_PARANTHESIS block
                | type IDENTIFIER OPEN_PARANTHESIS CLOSE_PARANTHESIS block
                | VOID IDENTIFIER OPEN_PARANTHESIS CLOSE_PARANTHESIS block

    params : param
           | params COMMA param
    param : type IDENTIFIER
    block : OPEN_CURLYBRACE var_decls statements CLOSE_CURLYBRACE
        |   OPEN_CURLYBRACE var_decls CLOSE_CURLYBRACE
        |   OPEN_CURLYBRACE statements CLOSE_CURLYBRACE
        |   OPEN_CURLYBRACE CLOSE_CURLYBRACE
    var_decls : var_decl
            |   var_decls var_decl
    var_decl : type identifiers SEMICOLON
    identifiers : IDENTIFIER
                | identifiers COMMA IDENTIFIER
    statements :    statement
                |   statements statement
    statement : location assign_op expr SEMICOLON
            |   method_call SEMICOLON
            |   IF OPEN_PARANTHESIS expr CLOSE_PARANTHESIS block ELSE block
            |   IF OPEN_PARANTHESIS expr CLOSE_PARANTHESIS block
            |   FOR IDENTIFIER EQUAL expr COMMA expr block
            |   RETURN expr SEMICOLON
            |   RETURN SEMICOLON
            |   BREAK SEMICOLON
            |   CONTINUE SEMICOLON
            |   block
            |   SEMICOLON

    method_call : IDENTIFIER OPEN_PARANTHESIS CLOSE_PARANTHESIS
            |     IDENTIFIER OPEN_PARANTHESIS exprs CLOSE_PARANTHESIS {cout << "ye wala " << endl;}
            |     CALLOUT OPEN_PARANTHESIS STRING_VALUE CLOSE_PARANTHESIS
            |     CALLOUT OPEN_PARANTHESIS STRING_VALUE callout_args CLOSE_PARANTHESIS
    exprs : expr
        |   exprs COMMA expr
    location :  IDENTIFIER {cout << "location with identifier " << $1 << endl;}
            |   IDENTIFIER OPEN_SQUAREBRACKET expr CLOSE_SQUAREBRACKET {cout << "location with identifier and expr" << $1 << endl;}
    expr :  location {cout << "It was a location" << endl;}
        |   method_call
        |   literal {cout << "It was a literal" << endl;}
        |   expr OR expr
        |   expr AND expr
        |   expr EQUALEQUAL expr
        |   expr NOTEQUAL expr
        |   expr LESSTHAN expr
        |   expr LESSEQUAL expr
        |   expr GREATERTHAN expr
        |   expr GREATEREQUAL expr
        |   expr PLUS expr
        |   expr MINUS expr
        |   expr MULTIPLY expr
        |   expr DIVIDE expr
        |   expr MODULO expr
        |   MINUS expr
        |   NOT expr
        |   OPEN_PARANTHESIS expr CLOSE_PARANTHESIS
    callout_args : COMMA callout_arg
                |  callout_args COMMA callout_arg
    callout_arg : expr | STRING_VALUE
    assign_op : EQUAL
            |   PLUSEQUAL
            |   MINUSEQUAL
    literal : INT_VALUE {cout << "Integer literal encountered\nValue=" << $1 << endl;}
            | bool_value
            | CHAR_VALUE {cout << "Char literal encoutered\nValue=" << $1 << endl;}
    bool_value  :TRUE {cout << "Boolean literal encountered\nValue=" << "true" << endl;}
                |FALSE {cout << "Boolean literal encountered\nValue=" << "false" << endl;}
    type :  INT {cout << "Int field_decl encountered" << endl;}
        |   BOOLEAN {cout << "Boolean field_decl encountered" << endl;}
    // str: STRING_VALUE  { cout << "String literal : "  << $1 << endl; }

%%

void yyerror (const char *s) {
    // TODO print exactly where syntax error occured
    // yyerror is called when a terminal us not able to fit into grammar.
    // That is when given program does not hold true to the grammar.
    cout << "Syntax error" << endl;
	// std::cerr << "Parse Error on Line : " << yylineno << std::endl << "Message : " << s << std::endl;
    // TODO Check if you can keep parsing even if yyerror is called.
    exit(-1);
}
