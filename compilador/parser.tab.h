/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
<<<<<<< Updated upstream
=======
/* "%code requires" blocks.  */
#line 10 "parser/parser.y"

#include "ast.h"
#include "tipos.h"

/* Valor semantico de uma expressao: no da AST + tipo inferido. */
typedef struct {
    NoAST *no;
    TipoDado tipo;
} Expr;

#line 60 "parser.tab.h"
>>>>>>> Stashed changes

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    ATRIBUES = 259,                /* ATRIBUES  */
    NUMBER = 260,                  /* NUMBER  */
<<<<<<< Updated upstream
    FLOAT = 261,                   /* FLOAT  */
    STRING = 262,                  /* STRING  */
    BOOLEAN = 263,                 /* BOOLEAN  */
    PRINT = 264,                   /* PRINT  */
    IF = 265,                      /* IF  */
    ELSE = 266,                    /* ELSE  */
    WHILE = 267,                   /* WHILE  */
    COLON = 268,                   /* COLON  */
    NEWLINE = 269,                 /* NEWLINE  */
    LPAREN = 270,                  /* LPAREN  */
    RPAREN = 271,                  /* RPAREN  */
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    PLUS = 274,                    /* PLUS  */
    MINUS = 275,                   /* MINUS  */
    TIMES = 276,                   /* TIMES  */
    DIVIDE = 277,                  /* DIVIDE  */
    EQ = 278,                      /* EQ  */
    NEQ = 279,                     /* NEQ  */
    LEQ = 280,                     /* LEQ  */
    GEQ = 281,                     /* GEQ  */
    LT = 282,                      /* LT  */
    GT = 283,                      /* GT  */
=======
    BOOLEAN = 261,                 /* BOOLEAN  */
    FLOAT = 262,                   /* FLOAT  */
    PRINT = 263,                   /* PRINT  */
    IF = 264,                      /* IF  */
    ELSE = 265,                    /* ELSE  */
    WHILE = 266,                   /* WHILE  */
    COLON = 267,                   /* COLON  */
    NEWLINE = 268,                 /* NEWLINE  */
    LPAREN = 269,                  /* LPAREN  */
    RPAREN = 270,                  /* RPAREN  */
    LBRACE = 271,                  /* LBRACE  */
    RBRACE = 272,                  /* RBRACE  */
    PLUS = 273,                    /* PLUS  */
    MINUS = 274,                   /* MINUS  */
    TIMES = 275,                   /* TIMES  */
    DIVIDE = 276,                  /* DIVIDE  */
    EQ = 277,                      /* EQ  */
    NEQ = 278,                     /* NEQ  */
    LEQ = 279,                     /* LEQ  */
    GEQ = 280,                     /* GEQ  */
    LT = 281,                      /* LT  */
    GT = 282,                      /* GT  */
    ATRIBUES = 283,                /* ATRIBUES  */
>>>>>>> Stashed changes
    LOWER_THAN_ELSE = 284          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
<<<<<<< Updated upstream
typedef int YYSTYPE;
=======
union YYSTYPE
{
#line 21 "parser/parser.y"

    int inteiro;
    double real;
    char *texto;
    NoAST *no;
    Expr expr;

#line 114 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
>>>>>>> Stashed changes
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
