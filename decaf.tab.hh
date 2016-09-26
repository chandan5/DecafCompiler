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
     CLASS = 265,
     IF = 266,
     ELSE = 267,
     FOR = 268,
     CONTINUE = 269,
     BREAK = 270,
     CALLOUT = 271,
     RETURN = 272,
     VOID = 273,
     FALSE = 274,
     INT = 275,
     BOOLEAN = 276,
     TRUE = 277,
     EQUAL = 278,
     PLUS = 279,
     MINUS = 280,
     MULTIPLY = 281,
     DIVIDE = 282,
     MODULO = 283,
     IDENTIFIER = 284,
     INT_VALUE = 285
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
#define CLASS 265
#define IF 266
#define ELSE 267
#define FOR 268
#define CONTINUE 269
#define BREAK 270
#define CALLOUT 271
#define RETURN 272
#define VOID 273
#define FALSE 274
#define INT 275
#define BOOLEAN 276
#define TRUE 277
#define EQUAL 278
#define PLUS 279
#define MINUS 280
#define MULTIPLY 281
#define DIVIDE 282
#define MODULO 283
#define IDENTIFIER 284
#define INT_VALUE 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "decaf.y"
{
    int ival;
    char *sval;
}
/* Line 1529 of yacc.c.  */
#line 114 "decaf.tab.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

