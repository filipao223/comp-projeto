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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    INTLIT = 258,
    REALLIT = 259,
    ID = 260,
    FUNC = 261,
    LPAR = 262,
    RPAR = 263,
    OR = 264,
    AND = 265,
    LT = 266,
    GT = 267,
    EQ = 268,
    NE = 269,
    LE = 270,
    GE = 271,
    SEMICOLON = 272,
    BLANKID = 273,
    PACKAGE = 274,
    RETURN = 275,
    ASSIGN = 276,
    STAR = 277,
    COMMA = 278,
    DIV = 279,
    MINUS = 280,
    MOD = 281,
    NOT = 282,
    PLUS = 283,
    RBRACE = 284,
    RSQ = 285,
    ELSE = 286,
    FOR = 287,
    IF = 288,
    VAR = 289,
    INT = 290,
    FLOAT32 = 291,
    BOOL = 292,
    STRINGVAR = 293,
    PRINT = 294,
    PARSEINT = 295,
    CMDARGS = 296,
    RESERVED = 297,
    LSQ = 298,
    LBRACE = 299,
    STRLIT = 300,
    ADD = 301,
    SUB = 302,
    MUL = 303
  };
#endif
/* Tokens.  */
#define INTLIT 258
#define REALLIT 259
#define ID 260
#define FUNC 261
#define LPAR 262
#define RPAR 263
#define OR 264
#define AND 265
#define LT 266
#define GT 267
#define EQ 268
#define NE 269
#define LE 270
#define GE 271
#define SEMICOLON 272
#define BLANKID 273
#define PACKAGE 274
#define RETURN 275
#define ASSIGN 276
#define STAR 277
#define COMMA 278
#define DIV 279
#define MINUS 280
#define MOD 281
#define NOT 282
#define PLUS 283
#define RBRACE 284
#define RSQ 285
#define ELSE 286
#define FOR 287
#define IF 288
#define VAR 289
#define INT 290
#define FLOAT32 291
#define BOOL 292
#define STRINGVAR 293
#define PRINT 294
#define PARSEINT 295
#define CMDARGS 296
#define RESERVED 297
#define LSQ 298
#define LBRACE 299
#define STRLIT 300
#define ADD 301
#define SUB 302
#define MUL 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 96 "gocompiler.y" /* yacc.c:1909  */

    char *str;
    int int_value;
    double float_value;
    struct ast_node *node;

#line 157 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
