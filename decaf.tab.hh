/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SEMICOLON = 258,
     OPEN_PARANTHESIS = 259,
     CLOSE_PARANTHESIS = 260,
     OPEN_SQUAREBRACKET = 261,
     CLOSE_SQUAREBRACKET = 262,
     OPEN_CURLYBRACE = 263,
     CLOSE_CURLYBRACE = 264,
     MAIN = 265,
     FALSE = 266,
     INT = 267,
     BOOLEAN = 268,
     TRUE = 269,
     EQUAL = 270,
     PLUS = 271,
     MINUS = 272,
     MULTIPLY = 273,
     DIVIDE = 274,
     MODULO = 275,
     IDENTIFIER = 276,
     INT_VALUE = 277
   };
#endif
/* Tokens.  */
#define SEMICOLON 258
#define OPEN_PARANTHESIS 259
#define CLOSE_PARANTHESIS 260
#define OPEN_SQUAREBRACKET 261
#define CLOSE_SQUAREBRACKET 262
#define OPEN_CURLYBRACE 263
#define CLOSE_CURLYBRACE 264
#define MAIN 265
#define FALSE 266
#define INT 267
#define BOOLEAN 268
#define TRUE 269
#define EQUAL 270
#define PLUS 271
#define MINUS 272
#define MULTIPLY 273
#define DIVIDE 274
#define MODULO 275
#define IDENTIFIER 276
#define INT_VALUE 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "decaf.y"
{
    int ival;
    char *sval;
}
/* Line 1529 of yacc.c.  */
#line 98 "decaf.tab.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

