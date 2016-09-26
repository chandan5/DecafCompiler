%{
#include<cstdio>
#include<iostream>
#include <fstream>
    using namespace std;
#define YY_DECL extern "C" int yylex()
#include "decaf.tab.hh"

int error_count = 0;
%}

%option yylineno

DIGIT [0-9]
ALPHA [a-zA-Z]
HEXADECIMAL [0-9a-fA-F]
CHAR ([\40-\176]{-}['"\\])|\\n|\\t|\\\\|\\\"|\\\'

%%
[ \t\n]  {

};
\/\/(.*?)\n {

}
{DIGIT}+ {
    yylval.ival = atoi(yytext);
    return INT_VALUE;
}
class {
    return CLASS;
}
int {
    return INT;
}
boolean {
    return BOOLEAN;
}
callout {
    return CALLOUT;
}
if {
    return IF;
}
else {
    return ELSE;
}
for {
    return FOR;
}
continue {
    return CONTINUE;
}
break {
    return BREAK;
}
return {
    return RETURN;
}
void {
    return VOID;
}
true {
    return TRUE;
}
false {
    return FALSE;
}
{ALPHA}({ALPHA}|{DIGIT})* {
    yylval.sval = strdup(yytext);
    return IDENTIFIER;
}
0x{HEXADECIMAL}+ {
	yylval.ival = atoi(yytext);
	return INT_VALUE;
}
\"{CHAR}*\" {
    yytext[strlen(yytext)-1] = '\0';
    yylval.sval = strdup(yytext+1);
	return STRING_VALUE;
}

\'{CHAR}\' {
	yylval.cval = yytext[1];
	return CHAR_VALUE;
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
\!\= {
	return NOTEQUAL;
}

\! {
	return NOT;
}

\<\= {
	return LESSEQUAL;
}

\< {
	return LESSTHAN;
}

\>\= {
	return GREATEREQUAL;
}

\> {
	return GREATERTHAN;
}

\=\= {
	return EQUALEQUAL;
}
\= {
    return EQUAL;
}
\+\= {
    return PLUSEQUAL;
}
\-\= {
    return MINUSEQUAL;
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
\&\& {
    return AND;
}
\|\| {
    return OR;
}
, {
    return COMMA;
}
; {
    return SEMICOLON;
}
. {++error_count;}
%%
