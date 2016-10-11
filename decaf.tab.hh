/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_DECAF_TAB_HH_INCLUDED
# define YY_YY_DECAF_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    COMMA = 259,
    OPEN_PARANTHESIS = 260,
    CLOSE_PARANTHESIS = 261,
    OPEN_SQUAREBRACKET = 262,
    CLOSE_SQUAREBRACKET = 263,
    OPEN_CURLYBRACE = 264,
    CLOSE_CURLYBRACE = 265,
    CLASS = 266,
    IF = 267,
    ELSE = 268,
    FOR = 269,
    CONTINUE = 270,
    BREAK = 271,
    CALLOUT = 272,
    RETURN = 273,
    VOID = 274,
    FALSE = 275,
    INT = 276,
    BOOLEAN = 277,
    TRUE = 278,
    IDENTIFIER = 279,
    STRING_VALUE = 280,
    CHAR_VALUE = 281,
    INT_VALUE = 282,
    OR = 283,
    AND = 284,
    EQUAL = 285,
    PLUSEQUAL = 286,
    MINUSEQUAL = 287,
    EQUALEQUAL = 288,
    NOTEQUAL = 289,
    LESSEQUAL = 290,
    LESSTHAN = 291,
    GREATEREQUAL = 292,
    GREATERTHAN = 293,
    PLUS = 294,
    MINUS = 295,
    MULTIPLY = 296,
    DIVIDE = 297,
    MODULO = 298,
    NOT = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "decaf.y" /* yacc.c:1915  */

    int ival;
    char *sval;
    char cval;

#line 105 "decaf.tab.hh" /* yacc.c:1915  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_DECAF_TAB_HH_INCLUDED  */
