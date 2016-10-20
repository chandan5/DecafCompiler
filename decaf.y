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

%type<type> type;
%type<assign_op> assign_op;
%type<literal> literal;
%type<field_decls> field_decls;
%type<field_decl> field_decl;
%type<var_decls> var_decls;
%type<var_decl> var_decl;
%type<method_decls> method_decls;
%type<method_decl> method_decl;
%type<identifier_opt_arrs> identifier_opt_arrs;
%type<identifier_opt_arr> identifier_opt_arr;
%type<identifiers> identifiers;
%type<callout_args> callout_args;
%type<callout_arg> callout_arg;
%type<method_call> method_call;
%type<exprs> exprs;
%type<expr> expr;
%type<location> location;
%type<params> params;
%type<param> param;
%type<statements> statements;
%type<statement> statement;
%type<block> block;
%type<program> program;


%%
    program: CLASS IDENTIFIER OPEN_CURLYBRACE field_decls method_decls CLOSE_CURLYBRACE {$$ = new ASTProgram($4,$5); astRoot = $$;}
        |    CLASS IDENTIFIER OPEN_CURLYBRACE field_decls CLOSE_CURLYBRACE {$$ = new ASTProgram($4,NULL); astRoot = $$;}
        |    CLASS IDENTIFIER OPEN_CURLYBRACE method_decls CLOSE_CURLYBRACE {$$ = new ASTProgram(NULL,$4); astRoot = $$;}
        |    CLASS IDENTIFIER OPEN_CURLYBRACE CLOSE_CURLYBRACE {$$ = new ASTProgram(NULL,NULL); astRoot = $$;}
                // {
                   // Check if Identifier is Program
                //    if($2 == "Program")
                        // cout << "Program encountered" << endl;
                // }

    // When first field_decl is constructed from rule : "field_decl : type identifier_opt_arrs SEMICOLON"
    // It makes a filed_decls using rule : "field_decls :  field_decl".
    // When next field_decl is constructed field_decls is updated using "field_decls : field_decls field_decl"
    field_decls :  field_decl {$$ = new vector<ASTFieldDeclaration *>(); $$->push_back($1);}
               |   field_decls field_decl {$1->push_back($2); $$ = $1;}
    field_decl :    type identifier_opt_arrs SEMICOLON {$$ = new ASTFieldDeclaration($1,$2);}

    identifier_opt_arrs : identifier_opt_arr {$$ = new vector<ASTIdentifier *>(); $$->push_back($1);}
                    |     identifier_opt_arrs COMMA identifier_opt_arr {$1->push_back($3); $$ = $1;}
    identifier_opt_arr : IDENTIFIER {$$ = new ASTNormalIdentifier(string($1));}
                    |   IDENTIFIER OPEN_SQUAREBRACKET INT_VALUE CLOSE_SQUAREBRACKET {$$ = new ASTArrayIdentifier($1,$3);}
    method_decls : method_decl {$$ = new vector<ASTMethodDeclaration *>(); $$->push_back($1);}
                | method_decls method_decl {$1->push_back($2); $$ = $1;}
    method_decl : type IDENTIFIER OPEN_PARANTHESIS params CLOSE_PARANTHESIS block {$$ = new ASTMethodDeclaration($1,string($2),$4,$6);}
                | VOID IDENTIFIER OPEN_PARANTHESIS params CLOSE_PARANTHESIS block {$$ = new ASTMethodDeclaration(DataType::void_type,string($2),$4,$6);}
                | type IDENTIFIER OPEN_PARANTHESIS CLOSE_PARANTHESIS block {$$ = new ASTMethodDeclaration($1,string($2),NULL,$5);}
                | VOID IDENTIFIER OPEN_PARANTHESIS CLOSE_PARANTHESIS block {$$ = new ASTMethodDeclaration(DataType::void_type,string($2),NULL,$5);}

    params : param {$$ = new vector<ASTParam *>(); $$->push_back($1);}
           | params COMMA param {$1->push_back($3); $$ = $1;}
    param : type IDENTIFIER {$$ = new ASTParam($1,string($2));}
    block : OPEN_CURLYBRACE var_decls statements CLOSE_CURLYBRACE {$$ = new ASTBlockStatement($2,$3);}
        |   OPEN_CURLYBRACE var_decls CLOSE_CURLYBRACE {$$ = new ASTBlockStatement($2,NULL);}
        |   OPEN_CURLYBRACE statements CLOSE_CURLYBRACE {$$ = new ASTBlockStatement(NULL,$2);}
        |   OPEN_CURLYBRACE CLOSE_CURLYBRACE {$$ = new ASTBlockStatement(NULL,NULL);}
    var_decls : var_decl {$$ = new vector<ASTVarDeclaration *>(); $$->push_back($1);}
            |   var_decls var_decl {$1->push_back($2); $$ = $1;}
    var_decl : type identifiers SEMICOLON {$$ = new ASTVarDeclaration($1,$2);}
    identifiers : IDENTIFIER {$$ = new vector<ASTVarLocation *>(); $$->push_back(new ASTVarLocation(string($1)));}
                | identifiers COMMA IDENTIFIER {$1->push_back(new ASTVarLocation(string($3))); $$ = $1;}
    statements :    statement {$$ = new vector<ASTStatement *>(); $$->push_back($1);}
                |   statements statement {$1->push_back($2); $$ = $1;}
    statement : location assign_op expr SEMICOLON {$$ = new ASTAssignmentStatement($1,$3,$2);}
            |   method_call SEMICOLON {$$ = new ASTMethodCallStatement($1);}
            |   IF OPEN_PARANTHESIS expr CLOSE_PARANTHESIS block ELSE block {$$ = new ASTIfStatement($3,$5,$7);}
            |   IF OPEN_PARANTHESIS expr CLOSE_PARANTHESIS block {$$ = new ASTIfStatement($3,$5,NULL);}
            |   FOR IDENTIFIER EQUAL expr COMMA expr block {$$ = new ASTForStatement(string($2),$4,$6,$7);}
            |   RETURN expr SEMICOLON {$$ = new ASTReturnStatement($2);}
            |   RETURN SEMICOLON {$$ = new ASTReturnStatement(NULL);}
            |   BREAK SEMICOLON {$$ = new ASTBreakStatement();}
            |   CONTINUE SEMICOLON {$$ = new ASTContinueStatement();}
            |   block {$$ = $1;}
            |   SEMICOLON {$$ = NULL;}

    method_call : IDENTIFIER OPEN_PARANTHESIS CLOSE_PARANTHESIS {$$ = new ASTSimpleMethodCall($1,NULL);}
            |     IDENTIFIER OPEN_PARANTHESIS exprs CLOSE_PARANTHESIS {$$ = new ASTSimpleMethodCall($1,$3);}
            |     CALLOUT OPEN_PARANTHESIS STRING_VALUE CLOSE_PARANTHESIS {$$ = new ASTCalloutMethodCall(string($3),NULL);}
            |     CALLOUT OPEN_PARANTHESIS STRING_VALUE callout_args CLOSE_PARANTHESIS {$$ = new ASTCalloutMethodCall(string($3),$4);}
    exprs : expr {$$ = new vector<ASTExpression *>(); $$->push_back($1);}
        |   exprs COMMA expr {$1->push_back($3); $$ = $1;}
    location :  IDENTIFIER {$$ = new ASTVarLocation($1);}
            |   IDENTIFIER OPEN_SQUAREBRACKET expr CLOSE_SQUAREBRACKET {$$ = new ASTArrayLocation($1,$3);}
    expr :  location {$$ = $1;}
        |   method_call {$$ = new ASTMethodCallExpression($1);}
        |   literal {$$ = $1;}
        |   expr OR expr {$$ = new ASTBinaryExpression($1,$3,BinOp::or_op);}
        |   expr AND expr {$$ = new ASTBinaryExpression($1,$3,BinOp::and_op);}
        |   expr EQUALEQUAL expr {$$ = new ASTBinaryExpression($1,$3,BinOp::equalequal_op);}
        |   expr NOTEQUAL expr {$$ = new ASTBinaryExpression($1,$3,BinOp::notequal_op);}
        |   expr LESSTHAN expr {$$ = new ASTBinaryExpression($1,$3,BinOp::lessthan_op);}
        |   expr LESSEQUAL expr {$$ = new ASTBinaryExpression($1,$3,BinOp::lessequal_op);}
        |   expr GREATERTHAN expr {$$ = new ASTBinaryExpression($1,$3,BinOp::greaterthan_op);}
        |   expr GREATEREQUAL expr {$$ = new ASTBinaryExpression($1,$3,BinOp::greaterequal_op);}
        |   expr PLUS expr {$$ = new ASTBinaryExpression($1,$3,BinOp::plus_op);}
        |   expr MINUS expr {$$ = new ASTBinaryExpression($1,$3,BinOp::sub_op);}
        |   expr MULTIPLY expr {$$ = new ASTBinaryExpression($1,$3,BinOp::multiply_op);}
        |   expr DIVIDE expr {$$ = new ASTBinaryExpression($1,$3,BinOp::divide_op);}
        |   expr MODULO expr {$$ = new ASTBinaryExpression($1,$3,BinOp::modulo_op);}
        |   MINUS expr {$$ = new ASTUnaryExpression($2,UnOp::minus_op);}
        |   NOT expr {$$ = new ASTUnaryExpression($2,UnOp::not_op);}
        |   OPEN_PARANTHESIS expr CLOSE_PARANTHESIS {$$ = $2;}
    callout_args : COMMA callout_arg {$$ = new vector<ASTCalloutArg *>(); $$->push_back($2);}
                |  callout_args COMMA callout_arg {$1->push_back($3); $$ = $1;}
    callout_arg : expr {$$ = new ASTExpressionCalloutArg($1);}
                | STRING_VALUE {$$ = new ASTStringCalloutArg($1);}
    assign_op : EQUAL {$$ = AssignOp::equal;}
            |   PLUSEQUAL {$$ = AssignOp::plus_equal;}
            |   MINUSEQUAL {$$ = AssignOp::minus_equal;}
    literal :   INT_VALUE {$$ = new ASTIntegerLiteralExpression($1);}
            |   CHAR_VALUE {$$ = new ASTCharLiteralExpression($1);}
            |   TRUE {$$ = new ASTBooleanLiteralExpression(true);}
            |   FALSE {$$ = new ASTBooleanLiteralExpression(false);}
    type :  INT {$$ = DataType::int_type;}
        |   BOOLEAN {$$ = DataType::bool_type;}
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
