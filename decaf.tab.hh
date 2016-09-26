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
     NOT = 279,
     AND = 280,
     OR = 281,
     EQUALEQUAL = 282,
     NOTEQUAL = 283,
     LESSEQUAL = 284,
     LESSTHAN = 285,
     GREATEREQUAL = 286,
     GREATERTHAN = 287,
     PLUS = 288,
     MINUS = 289,
     MULTIPLY = 290,
     DIVIDE = 291,
     MODULO = 292,
     IDENTIFIER = 293,
     STRING_VALUE = 294,
     CHAR_VALUE = 295,
     INT_VALUE = 296,
     EQUAL = 297,
     PLUSEQUAL = 298,
     MINUSEQUAL = 299
   };
#endif
/* Tokens.  */
#define SEMICOLON 258
#define COMMA 259
#define OPEN_PARANTHESIS 260
#define CLOSE_PARANTHESIS 261
#define OPEN_SQUAREBRACKET 262
#define CLOSE_SQUAREBRACKET 263
#define OPEN_CURLYBRACE 264
#define CLOSE_CURLYBRACE 265
#define CLASS 266
#define IF 267
#define ELSE 268
#define FOR 269
#define CONTINUE 270
#define BREAK 271
#define CALLOUT 272
#define RETURN 273
#define VOID 274
#define FALSE 275
#define INT 276
#define BOOLEAN 277
#define TRUE 278
#define NOT 279
#define AND 280
#define OR 281
#define EQUALEQUAL 282
#define NOTEQUAL 283
#define LESSEQUAL 284
#define LESSTHAN 285
#define GREATEREQUAL 286
#define GREATERTHAN 287
#define PLUS 288
#define MINUS 289
#define MULTIPLY 290
#define DIVIDE 291
#define MODULO 292
#define IDENTIFIER 293
#define STRING_VALUE 294
#define CHAR_VALUE 295
#define INT_VALUE 296
#define EQUAL 297
#define PLUSEQUAL 298
#define MINUSEQUAL 299




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 14 "decaf.y"
{
    int ival;
    char *sval;
    char cval;
}
/* Line 1529 of yacc.c.  */
#line 143 "decaf.tab.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

