%{
#include<cstdio>
#include<iostream>
#include <fstream>
    using namespace std;
#define YY_DECL extern "C" int yylex()
#include "decaf.tab.hh"

int error_count = 0;
//ofstream flexoutfile;
%}

%option yylineno

DIGIT [0-9]
ALPHA [a-zA-Z]

%%
[ \t\n]  {

};
\/\/(.*?)\n {

}
[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/] {

}

{DIGIT}+ {
    yylval.ival = atoi(yytext);
    return INT_VALUE;
}
int {
    return INT;
}
bool {
    return BOOLEAN;
}
true {
    return TRUE;
}
false {
    return FALSE;
}
main {
    return MAIN;
}
{ALPHA}({ALPHA}|{DIGIT})* {
    yylval.sval = strdup(yytext);
    return IDENTIFIER;
}
\[ {
    return OPEN_SQUAREBRACKET;
}
\] {
    return CLOSE_SQUAREBRACKET;
}
\{ {
    return OPEN_CURLYBRACE;
}
\} {
    return CLOSE_CURLYBRACE;
}
\( {
    return OPEN_PARANTHESIS;
}
\) {
    return CLOSE_PARANTHESIS;
}
\= {
    return EQUAL;
}
\+ {
    return PLUS;
}
\- {
    return MINUS;
}
\* {
    return MULTIPLY;
}
\/ {
    return DIVIDE;
}
\% {
    return MODULO;
}
; {
    return SEMICOLON;
}
. {++error_count;}
%%
