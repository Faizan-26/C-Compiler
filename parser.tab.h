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

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT_LITERAL = 258,             /* INT_LITERAL  */
    FLOAT_LITERAL = 259,           /* FLOAT_LITERAL  */
    BOOL_LITERAL = 260,            /* BOOL_LITERAL  */
    STRING_LITERAL = 261,          /* STRING_LITERAL  */
    IDENTIFIER = 262,              /* IDENTIFIER  */
    INT = 263,                     /* INT  */
    FLOAT = 264,                   /* FLOAT  */
    BOOL = 265,                    /* BOOL  */
    VOID = 266,                    /* VOID  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    WHILE = 269,                   /* WHILE  */
    FOR = 270,                     /* FOR  */
    RETURN = 271,                  /* RETURN  */
    BREAK = 272,                   /* BREAK  */
    CONTINUE = 273,                /* CONTINUE  */
    SWITCH = 274,                  /* SWITCH  */
    CASE = 275,                    /* CASE  */
    DEFAULT = 276,                 /* DEFAULT  */
    PRINT = 277,                   /* PRINT  */
    READ = 278,                    /* READ  */
    EQ = 279,                      /* EQ  */
    NEQ = 280,                     /* NEQ  */
    LE = 281,                      /* LE  */
    GE = 282,                      /* GE  */
    AND = 283,                     /* AND  */
    OR = 284,                      /* OR  */
    UMINUS = 285,                  /* UMINUS  */
    THEN = 286                     /* THEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "parser.y"

    int int_val;
    float float_val;
    bool bool_val;
    char* string_val;
    DataType type_val;
    ASTNode* node_val;

#line 104 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
