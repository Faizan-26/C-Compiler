/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

/* Global variables */
ASTNode* ast_root = NULL;
SymbolTable* global_symbol_table = NULL;

/* Function declarations */
void yyerror(const char* s);

#line 85 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_LITERAL = 3,                /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 4,              /* FLOAT_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 5,               /* BOOL_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_IDENTIFIER = 7,                 /* IDENTIFIER  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_FLOAT = 9,                      /* FLOAT  */
  YYSYMBOL_BOOL = 10,                      /* BOOL  */
  YYSYMBOL_VOID = 11,                      /* VOID  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_WHILE = 14,                     /* WHILE  */
  YYSYMBOL_FOR = 15,                       /* FOR  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_BREAK = 17,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 18,                  /* CONTINUE  */
  YYSYMBOL_SWITCH = 19,                    /* SWITCH  */
  YYSYMBOL_CASE = 20,                      /* CASE  */
  YYSYMBOL_DEFAULT = 21,                   /* DEFAULT  */
  YYSYMBOL_PRINT = 22,                     /* PRINT  */
  YYSYMBOL_READ = 23,                      /* READ  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_NEQ = 25,                       /* NEQ  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_GE = 27,                        /* GE  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_30_ = 30,                       /* '='  */
  YYSYMBOL_31_ = 31,                       /* '<'  */
  YYSYMBOL_32_ = 32,                       /* '>'  */
  YYSYMBOL_33_ = 33,                       /* '+'  */
  YYSYMBOL_34_ = 34,                       /* '-'  */
  YYSYMBOL_35_ = 35,                       /* '*'  */
  YYSYMBOL_36_ = 36,                       /* '/'  */
  YYSYMBOL_37_ = 37,                       /* '%'  */
  YYSYMBOL_38_ = 38,                       /* '!'  */
  YYSYMBOL_UMINUS = 39,                    /* UMINUS  */
  YYSYMBOL_THEN = 40,                      /* THEN  */
  YYSYMBOL_41_ = 41,                       /* ';'  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* ','  */
  YYSYMBOL_45_ = 45,                       /* '{'  */
  YYSYMBOL_46_ = 46,                       /* '}'  */
  YYSYMBOL_47_ = 47,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_declaration_list = 50,          /* declaration_list  */
  YYSYMBOL_declaration = 51,               /* declaration  */
  YYSYMBOL_var_declaration = 52,           /* var_declaration  */
  YYSYMBOL_type_specifier = 53,            /* type_specifier  */
  YYSYMBOL_func_declaration = 54,          /* func_declaration  */
  YYSYMBOL_params = 55,                    /* params  */
  YYSYMBOL_param_list = 56,                /* param_list  */
  YYSYMBOL_param = 57,                     /* param  */
  YYSYMBOL_compound_stmt = 58,             /* compound_stmt  */
  YYSYMBOL_stmt_list = 59,                 /* stmt_list  */
  YYSYMBOL_statement = 60,                 /* statement  */
  YYSYMBOL_expr_stmt = 61,                 /* expr_stmt  */
  YYSYMBOL_selection_stmt = 62,            /* selection_stmt  */
  YYSYMBOL_iteration_stmt = 63,            /* iteration_stmt  */
  YYSYMBOL_switch_stmt = 64,               /* switch_stmt  */
  YYSYMBOL_case_list = 65,                 /* case_list  */
  YYSYMBOL_case_stmt = 66,                 /* case_stmt  */
  YYSYMBOL_return_stmt = 67,               /* return_stmt  */
  YYSYMBOL_break_stmt = 68,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 69,             /* continue_stmt  */
  YYSYMBOL_io_stmt = 70,                   /* io_stmt  */
  YYSYMBOL_expression = 71,                /* expression  */
  YYSYMBOL_assignment_expr = 72,           /* assignment_expr  */
  YYSYMBOL_var = 73,                       /* var  */
  YYSYMBOL_simple_expr = 74,               /* simple_expr  */
  YYSYMBOL_additive_expr = 75,             /* additive_expr  */
  YYSYMBOL_term = 76,                      /* term  */
  YYSYMBOL_factor = 77,                    /* factor  */
  YYSYMBOL_call = 78,                      /* call  */
  YYSYMBOL_args = 79,                      /* args  */
  YYSYMBOL_arg_list = 80                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   224

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,     2,     2,    37,     2,     2,
      42,    43,    35,    33,    44,    34,     2,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    41,
      31,    30,    32,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    71,    71,    98,   100,   113,   115,   120,   128,   139,
     141,   143,   145,   150,   162,   164,   167,   171,   178,   186,
     196,   205,   210,   220,   222,   224,   226,   228,   230,   232,
     234,   236,   238,   243,   249,   254,   262,   273,   280,   289,
     301,   311,   318,   326,   333,   343,   349,   358,   367,   376,
     386,   399,   401,   406,   416,   425,   427,   435,   443,   451,
     459,   467,   475,   483,   494,   496,   504,   515,   517,   525,
     533,   544,   546,   548,   550,   556,   562,   568,   574,   581,
     591,   612,   615,   619,   624
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT_LITERAL",
  "FLOAT_LITERAL", "BOOL_LITERAL", "STRING_LITERAL", "IDENTIFIER", "INT",
  "FLOAT", "BOOL", "VOID", "IF", "ELSE", "WHILE", "FOR", "RETURN", "BREAK",
  "CONTINUE", "SWITCH", "CASE", "DEFAULT", "PRINT", "READ", "EQ", "NEQ",
  "LE", "GE", "AND", "OR", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'",
  "'%'", "'!'", "UMINUS", "THEN", "';'", "'('", "')'", "','", "'{'", "'}'",
  "':'", "$accept", "program", "declaration_list", "declaration",
  "var_declaration", "type_specifier", "func_declaration", "params",
  "param_list", "param", "compound_stmt", "stmt_list", "statement",
  "expr_stmt", "selection_stmt", "iteration_stmt", "switch_stmt",
  "case_list", "case_stmt", "return_stmt", "break_stmt", "continue_stmt",
  "io_stmt", "expression", "assignment_expr", "var", "simple_expr",
  "additive_expr", "term", "factor", "call", "args", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-143)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-16)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,  -143,  -143,  -143,  -143,    13,    18,  -143,  -143,    16,
    -143,  -143,  -143,   -21,   174,  -143,    91,  -143,  -143,  -143,
    -143,    28,   174,   174,   174,    38,  -143,    50,   171,   -18,
      70,  -143,  -143,    41,    74,    68,    48,  -143,   174,  -143,
    -143,  -143,    69,  -143,   174,   174,   174,   174,   174,   174,
     174,   174,   174,   174,   174,   174,   174,   174,  -143,    64,
      18,  -143,    71,    72,  -143,  -143,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,   -18,    70,    70,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,   174,    49,  -143,    51,    73,    75,    44,
      77,    78,    82,    83,    85,  -143,  -143,  -143,   121,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,    88,
     174,   174,   152,  -143,    89,  -143,  -143,   174,   174,   124,
      -8,  -143,   101,   108,   174,   111,  -143,   123,   125,  -143,
     127,   131,   131,   126,   174,    87,   130,   133,   151,  -143,
     174,   134,    53,  -143,  -143,   131,   139,   174,   180,   137,
     -15,  -143,  -143,   131,   142,   140,  -143,  -143,  -143,  -143,
     131,  -143,   131,  -143,   131
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,    11,    12,     0,     2,     3,     5,     0,
       6,     1,     4,     0,     0,     7,    16,    74,    75,    76,
      77,    54,     0,     0,     0,     0,    51,    72,    52,    55,
      64,    67,    73,    12,     0,     0,    14,    17,    82,    72,
      78,    79,     0,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
       0,    83,     0,    81,    71,    53,    60,    61,    58,    59,
      62,    63,    56,    57,    65,    66,    68,    69,    70,    21,
      13,    18,    80,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    20,    31,     0,    24,
      22,    23,    25,    26,    27,    28,    29,    30,    32,     0,
       0,     0,     0,    45,     0,    47,    48,     0,     0,     0,
       0,    33,     0,     0,     0,     0,    46,     0,     0,    54,
       0,     0,     0,     0,     0,     0,     0,     0,    35,    37,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,    41,    36,     0,     0,     0,    21,    40,    42,    39,
       0,    21,    44,    38,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -143,  -143,  -143,   182,     1,     2,  -143,  -143,  -143,   129,
     132,  -142,  -128,  -143,  -143,  -143,  -143,  -143,    42,  -143,
    -143,  -143,  -143,   -14,  -143,   -11,  -143,   172,    23,    66,
    -143,  -143,  -143
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,    97,    98,    10,    35,    36,    37,
      99,    84,   100,   101,   102,   103,   104,   150,   151,   105,
     106,   107,   108,   109,    26,    27,    28,    29,    30,    31,
      32,    62,    63
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      25,     8,     9,   138,   139,   148,   149,     8,     9,    14,
      42,    39,    39,    11,   162,    53,    54,   152,    34,   164,
      15,    16,    14,    13,    61,   159,     1,     2,     3,     4,
      65,   157,   163,    15,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    39,    39,    17,    18,    19,
      20,    21,    17,    18,    19,    20,    21,     1,     2,     3,
       4,    86,    34,    87,    88,    89,    90,    91,    92,    85,
      38,    93,    94,   148,   149,   114,    74,    75,    22,    43,
      44,    58,    23,    22,   -15,   113,    24,    23,    40,    41,
      95,    24,    60,   110,    79,    96,   122,   123,   125,     1,
       2,     3,    33,   127,   128,    55,    56,    57,   130,    79,
     133,    59,    64,   124,    82,   111,    83,   112,   115,   116,
     141,    76,    77,    78,   117,   118,   146,   119,   120,   121,
     126,   129,   142,   154,    17,    18,    19,    20,    21,     1,
       2,     3,     4,    86,   131,    87,    88,    89,    90,    91,
      92,   132,   134,    93,    94,    17,    18,    19,    20,    21,
       1,     2,     3,     4,   145,    22,   135,   140,   136,    23,
     137,   143,    95,    24,   144,   147,    79,    17,    18,    19,
      20,    21,   153,   155,   156,   160,    22,   161,    12,    81,
      23,    80,   158,     0,    24,    45,    46,    47,    48,    49,
      50,     0,    51,    52,     0,     0,     0,     0,    22,     0,
       0,     0,    23,     0,     0,     0,    24,    66,    67,    68,
      69,    70,    71,    72,    73
};

static const yytype_int16 yycheck[] =
{
      14,     0,     0,   131,   132,    20,    21,     6,     6,    30,
      24,    22,    23,     0,   156,    33,    34,   145,    16,   161,
      41,    42,    30,     7,    38,   153,     8,     9,    10,    11,
      44,    46,   160,    41,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    60,    14,    15,    16,    17,    18,    19,    83,
      42,    22,    23,    20,    21,    89,    53,    54,    34,    41,
      30,     7,    38,    34,    43,    41,    42,    38,    22,    23,
      41,    42,    44,    42,    45,    46,   110,   111,   112,     8,
       9,    10,    11,   117,   118,    35,    36,    37,   119,    45,
     124,    43,    43,   112,    43,    42,    44,    42,    41,    41,
     134,    55,    56,    57,    42,    42,   140,    42,     7,    41,
      41,     7,    45,   147,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    43,    14,    15,    16,    17,    18,
      19,    43,    41,    22,    23,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    13,    34,    43,    41,    43,    38,
      43,    41,    41,    42,    41,    41,    45,     3,     4,     5,
       6,     7,    43,     3,    47,    43,    34,    47,     6,    60,
      38,    59,   150,    -1,    42,    24,    25,    26,    27,    28,
      29,    -1,    31,    32,    -1,    -1,    -1,    -1,    34,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    42,    45,    46,    47,
      48,    49,    50,    51,    52
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,     9,    10,    11,    49,    50,    51,    52,    53,
      54,     0,    51,     7,    30,    41,    42,     3,     4,     5,
       6,     7,    34,    38,    42,    71,    72,    73,    74,    75,
      76,    77,    78,    11,    53,    55,    56,    57,    42,    73,
      77,    77,    71,    41,    30,    24,    25,    26,    27,    28,
      29,    31,    32,    33,    34,    35,    36,    37,     7,    43,
      44,    71,    79,    80,    43,    71,    75,    75,    75,    75,
      75,    75,    75,    75,    76,    76,    77,    77,    77,    45,
      58,    57,    43,    44,    59,    71,    12,    14,    15,    16,
      17,    18,    19,    22,    23,    41,    46,    52,    53,    58,
      60,    61,    62,    63,    64,    67,    68,    69,    70,    71,
      42,    42,    42,    41,    71,    41,    41,    42,    42,    42,
       7,    41,    71,    71,    52,    71,    41,    71,    71,     7,
      73,    43,    43,    71,    41,    43,    43,    43,    60,    60,
      41,    71,    45,    41,    41,    13,    71,    41,    20,    21,
      65,    66,    60,    43,    71,     3,    47,    46,    66,    60,
      43,    47,    59,    60,    59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    52,    52,    53,
      53,    53,    53,    54,    55,    55,    55,    56,    56,    57,
      58,    59,    59,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    62,    62,    63,    63,    63,
      64,    65,    65,    66,    66,    67,    67,    68,    69,    70,
      70,    71,    71,    72,    73,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    75,    75,    75,    76,    76,    76,
      76,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      78,    79,    79,    80,    80
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     5,     1,
       1,     1,     1,     6,     1,     1,     0,     1,     3,     2,
       3,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     5,     7,     5,     9,     8,
       7,     1,     2,     4,     3,     2,     3,     2,     2,     5,
       5,     1,     1,     3,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     1,     2,     2,
       4,     1,     0,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declaration_list  */
#line 72 "parser.y"
        {
            ast_root = create_node(NODE_PROGRAM);
            ast_root->as.program.declarations = malloc(sizeof(ASTNode*) * 1000);
            ast_root->as.program.declaration_count = 0;
            
            // Collect all declarations
            ASTNode* curr = (yyvsp[0].node_val);
            while (curr != NULL) {
                if (curr->type == NODE_BLOCK) {
                    for (int i = 0; i < curr->as.block.statement_count; i++) {
                        ast_root->as.program.declarations[ast_root->as.program.declaration_count++] = 
                            curr->as.block.statements[i];
                    }
                    free(curr->as.block.statements);
                    free(curr);
                } else {
                    ast_root->as.program.declarations[ast_root->as.program.declaration_count++] = curr;
                }
                curr = NULL;
            }
            
            (yyval.node_val) = ast_root;
        }
#line 1296 "parser.tab.c"
    break;

  case 3: /* declaration_list: declaration  */
#line 99 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1302 "parser.tab.c"
    break;

  case 4: /* declaration_list: declaration_list declaration  */
#line 101 "parser.y"
        {
            // Create a new block node to hold both declarations
            ASTNode* block = create_node(NODE_BLOCK);
            block->as.block.statements = malloc(sizeof(ASTNode*) * 2);
            block->as.block.statement_count = 2;
            block->as.block.statements[0] = (yyvsp[-1].node_val);
            block->as.block.statements[1] = (yyvsp[0].node_val);
            (yyval.node_val) = block;
        }
#line 1316 "parser.tab.c"
    break;

  case 5: /* declaration: var_declaration  */
#line 114 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1322 "parser.tab.c"
    break;

  case 6: /* declaration: func_declaration  */
#line 116 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1328 "parser.tab.c"
    break;

  case 7: /* var_declaration: type_specifier IDENTIFIER ';'  */
#line 121 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_VAR_DECL);
            (yyval.node_val)->as.var_decl.name = (yyvsp[-1].string_val);
            (yyval.node_val)->as.var_decl.type = (yyvsp[-2].type_val);
            (yyval.node_val)->as.var_decl.init_expr = NULL;
            (yyval.node_val)->line_number = yylineno;
        }
#line 1340 "parser.tab.c"
    break;

  case 8: /* var_declaration: type_specifier IDENTIFIER '=' expression ';'  */
#line 129 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_VAR_DECL);
            (yyval.node_val)->as.var_decl.name = (yyvsp[-3].string_val);
            (yyval.node_val)->as.var_decl.type = (yyvsp[-4].type_val);
            (yyval.node_val)->as.var_decl.init_expr = (yyvsp[-1].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1352 "parser.tab.c"
    break;

  case 9: /* type_specifier: INT  */
#line 140 "parser.y"
        { (yyval.type_val) = TYPE_INT; }
#line 1358 "parser.tab.c"
    break;

  case 10: /* type_specifier: FLOAT  */
#line 142 "parser.y"
        { (yyval.type_val) = TYPE_FLOAT; }
#line 1364 "parser.tab.c"
    break;

  case 11: /* type_specifier: BOOL  */
#line 144 "parser.y"
        { (yyval.type_val) = TYPE_BOOL; }
#line 1370 "parser.tab.c"
    break;

  case 12: /* type_specifier: VOID  */
#line 146 "parser.y"
        { (yyval.type_val) = TYPE_VOID; }
#line 1376 "parser.tab.c"
    break;

  case 13: /* func_declaration: type_specifier IDENTIFIER '(' params ')' compound_stmt  */
#line 151 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_FUNCTION_DECL);
            (yyval.node_val)->as.function_decl.name = (yyvsp[-4].string_val);
            (yyval.node_val)->as.function_decl.return_type = (yyvsp[-5].type_val);
            (yyval.node_val)->as.function_decl.params = (yyvsp[-2].node_val);
            (yyval.node_val)->as.function_decl.body = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1389 "parser.tab.c"
    break;

  case 14: /* params: param_list  */
#line 163 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1395 "parser.tab.c"
    break;

  case 15: /* params: VOID  */
#line 165 "parser.y"
        { (yyval.node_val) = NULL; }
#line 1401 "parser.tab.c"
    break;

  case 16: /* params: %empty  */
#line 167 "parser.y"
        { (yyval.node_val) = NULL; }
#line 1407 "parser.tab.c"
    break;

  case 17: /* param_list: param  */
#line 172 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_PARAM_LIST);
            (yyval.node_val)->as.param_list.params = malloc(sizeof(ASTNode*) * 100); // Arbitrary limit
            (yyval.node_val)->as.param_list.param_count = 1;
            (yyval.node_val)->as.param_list.params[0] = (yyvsp[0].node_val);
        }
#line 1418 "parser.tab.c"
    break;

  case 18: /* param_list: param_list ',' param  */
#line 179 "parser.y"
        {
            (yyval.node_val) = (yyvsp[-2].node_val);
            (yyval.node_val)->as.param_list.params[(yyval.node_val)->as.param_list.param_count++] = (yyvsp[0].node_val);
        }
#line 1427 "parser.tab.c"
    break;

  case 19: /* param: type_specifier IDENTIFIER  */
#line 187 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_PARAM);
            (yyval.node_val)->as.param.name = (yyvsp[0].string_val);
            (yyval.node_val)->as.param.type = (yyvsp[-1].type_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1438 "parser.tab.c"
    break;

  case 20: /* compound_stmt: '{' stmt_list '}'  */
#line 197 "parser.y"
        {
            (yyval.node_val) = (yyvsp[-1].node_val); // Stmt_list now already returns a NODE_BLOCK node
            (yyval.node_val)->line_number = yylineno;
        }
#line 1447 "parser.tab.c"
    break;

  case 21: /* stmt_list: %empty  */
#line 205 "parser.y"
        { 
            (yyval.node_val) = create_node(NODE_BLOCK);
            (yyval.node_val)->as.block.statements = NULL;
            (yyval.node_val)->as.block.statement_count = 0;
        }
#line 1457 "parser.tab.c"
    break;

  case 22: /* stmt_list: stmt_list statement  */
#line 211 "parser.y"
        { 
            (yyval.node_val) = (yyvsp[-1].node_val);
            (yyval.node_val)->as.block.statements = realloc((yyval.node_val)->as.block.statements, 
                sizeof(ASTNode*) * ((yyval.node_val)->as.block.statement_count + 1));
            (yyval.node_val)->as.block.statements[(yyval.node_val)->as.block.statement_count++] = (yyvsp[0].node_val);
        }
#line 1468 "parser.tab.c"
    break;

  case 23: /* statement: expr_stmt  */
#line 221 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1474 "parser.tab.c"
    break;

  case 24: /* statement: compound_stmt  */
#line 223 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1480 "parser.tab.c"
    break;

  case 25: /* statement: selection_stmt  */
#line 225 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1486 "parser.tab.c"
    break;

  case 26: /* statement: iteration_stmt  */
#line 227 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1492 "parser.tab.c"
    break;

  case 27: /* statement: switch_stmt  */
#line 229 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1498 "parser.tab.c"
    break;

  case 28: /* statement: return_stmt  */
#line 231 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1504 "parser.tab.c"
    break;

  case 29: /* statement: break_stmt  */
#line 233 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1510 "parser.tab.c"
    break;

  case 30: /* statement: continue_stmt  */
#line 235 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1516 "parser.tab.c"
    break;

  case 31: /* statement: var_declaration  */
#line 237 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1522 "parser.tab.c"
    break;

  case 32: /* statement: io_stmt  */
#line 239 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1528 "parser.tab.c"
    break;

  case 33: /* expr_stmt: expression ';'  */
#line 244 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_EXPR_STMT);
            (yyval.node_val)->as.expr_stmt.expr = (yyvsp[-1].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1538 "parser.tab.c"
    break;

  case 34: /* expr_stmt: ';'  */
#line 250 "parser.y"
        { (yyval.node_val) = NULL; }
#line 1544 "parser.tab.c"
    break;

  case 35: /* selection_stmt: IF '(' expression ')' statement  */
#line 255 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_IF_STMT);
            (yyval.node_val)->as.if_stmt.condition = (yyvsp[-2].node_val);
            (yyval.node_val)->as.if_stmt.then_branch = (yyvsp[0].node_val);
            (yyval.node_val)->as.if_stmt.else_branch = NULL;
            (yyval.node_val)->line_number = yylineno;
        }
#line 1556 "parser.tab.c"
    break;

  case 36: /* selection_stmt: IF '(' expression ')' statement ELSE statement  */
#line 263 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_IF_STMT);
            (yyval.node_val)->as.if_stmt.condition = (yyvsp[-4].node_val);
            (yyval.node_val)->as.if_stmt.then_branch = (yyvsp[-2].node_val);
            (yyval.node_val)->as.if_stmt.else_branch = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1568 "parser.tab.c"
    break;

  case 37: /* iteration_stmt: WHILE '(' expression ')' statement  */
#line 274 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_WHILE_STMT);
            (yyval.node_val)->as.while_stmt.condition = (yyvsp[-2].node_val);
            (yyval.node_val)->as.while_stmt.body = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1579 "parser.tab.c"
    break;

  case 38: /* iteration_stmt: FOR '(' expression ';' expression ';' expression ')' statement  */
#line 281 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_FOR_STMT);
            (yyval.node_val)->as.for_stmt.init = (yyvsp[-6].node_val);
            (yyval.node_val)->as.for_stmt.condition = (yyvsp[-4].node_val);
            (yyval.node_val)->as.for_stmt.update = (yyvsp[-2].node_val);
            (yyval.node_val)->as.for_stmt.body = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1592 "parser.tab.c"
    break;

  case 39: /* iteration_stmt: FOR '(' var_declaration expression ';' expression ')' statement  */
#line 290 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_FOR_STMT);
            (yyval.node_val)->as.for_stmt.init = (yyvsp[-5].node_val);
            (yyval.node_val)->as.for_stmt.condition = (yyvsp[-4].node_val);
            (yyval.node_val)->as.for_stmt.update = (yyvsp[-2].node_val);
            (yyval.node_val)->as.for_stmt.body = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1605 "parser.tab.c"
    break;

  case 40: /* switch_stmt: SWITCH '(' expression ')' '{' case_list '}'  */
#line 302 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_SWITCH_STMT);
            (yyval.node_val)->as.switch_stmt.expr = (yyvsp[-4].node_val);
            (yyval.node_val)->as.switch_stmt.cases = (yyvsp[-1].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1616 "parser.tab.c"
    break;

  case 41: /* case_list: case_stmt  */
#line 312 "parser.y"
        { 
            (yyval.node_val) = create_node(NODE_CASE_LIST);
            (yyval.node_val)->as.case_list.cases = malloc(sizeof(ASTNode*) * 100); // Arbitrary limit
            (yyval.node_val)->as.case_list.case_count = 1;
            (yyval.node_val)->as.case_list.cases[0] = (yyvsp[0].node_val);
        }
#line 1627 "parser.tab.c"
    break;

  case 42: /* case_list: case_list case_stmt  */
#line 319 "parser.y"
        { 
            (yyval.node_val) = (yyvsp[-1].node_val);
            (yyval.node_val)->as.case_list.cases[(yyval.node_val)->as.case_list.case_count++] = (yyvsp[0].node_val);
        }
#line 1636 "parser.tab.c"
    break;

  case 43: /* case_stmt: CASE INT_LITERAL ':' stmt_list  */
#line 327 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_CASE_STMT);
            (yyval.node_val)->as.case_stmt.value = (yyvsp[-2].int_val);
            (yyval.node_val)->as.case_stmt.body = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1647 "parser.tab.c"
    break;

  case 44: /* case_stmt: DEFAULT ':' stmt_list  */
#line 334 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_CASE_STMT);
            (yyval.node_val)->as.case_stmt.value = -1; // Special value for default
            (yyval.node_val)->as.case_stmt.body = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1658 "parser.tab.c"
    break;

  case 45: /* return_stmt: RETURN ';'  */
#line 344 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_RETURN_STMT);
            (yyval.node_val)->as.return_stmt.expr = NULL;
            (yyval.node_val)->line_number = yylineno;
        }
#line 1668 "parser.tab.c"
    break;

  case 46: /* return_stmt: RETURN expression ';'  */
#line 350 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_RETURN_STMT);
            (yyval.node_val)->as.return_stmt.expr = (yyvsp[-1].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1678 "parser.tab.c"
    break;

  case 47: /* break_stmt: BREAK ';'  */
#line 359 "parser.y"
        {
            // For simplicity, we'll use expr_stmt for break
            (yyval.node_val) = create_node(NODE_EXPR_STMT);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1688 "parser.tab.c"
    break;

  case 48: /* continue_stmt: CONTINUE ';'  */
#line 368 "parser.y"
        {
            // For simplicity, we'll use expr_stmt for continue
            (yyval.node_val) = create_node(NODE_EXPR_STMT);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1698 "parser.tab.c"
    break;

  case 49: /* io_stmt: PRINT '(' expression ')' ';'  */
#line 377 "parser.y"
        {
            // For simplicity, we'll use function call for print
            (yyval.node_val) = create_node(NODE_FUNC_CALL);
            (yyval.node_val)->as.func_call.name = strdup("print");
            (yyval.node_val)->as.func_call.args = malloc(sizeof(ASTNode*));
            (yyval.node_val)->as.func_call.args[0] = (yyvsp[-2].node_val);
            (yyval.node_val)->as.func_call.arg_count = 1;
            (yyval.node_val)->line_number = yylineno;
        }
#line 1712 "parser.tab.c"
    break;

  case 50: /* io_stmt: READ '(' var ')' ';'  */
#line 387 "parser.y"
        {
            // For simplicity, we'll use function call for read
            (yyval.node_val) = create_node(NODE_FUNC_CALL);
            (yyval.node_val)->as.func_call.name = strdup("read");
            (yyval.node_val)->as.func_call.args = malloc(sizeof(ASTNode*));
            (yyval.node_val)->as.func_call.args[0] = (yyvsp[-2].node_val);
            (yyval.node_val)->as.func_call.arg_count = 1;
            (yyval.node_val)->line_number = yylineno;
        }
#line 1726 "parser.tab.c"
    break;

  case 51: /* expression: assignment_expr  */
#line 400 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1732 "parser.tab.c"
    break;

  case 52: /* expression: simple_expr  */
#line 402 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1738 "parser.tab.c"
    break;

  case 53: /* assignment_expr: var '=' expression  */
#line 407 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_ASSIGN_EXPR);
            (yyval.node_val)->as.assign_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.assign_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1749 "parser.tab.c"
    break;

  case 54: /* var: IDENTIFIER  */
#line 417 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_VAR_REF);
            (yyval.node_val)->as.var_ref.name = (yyvsp[0].string_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1759 "parser.tab.c"
    break;

  case 55: /* simple_expr: additive_expr  */
#line 426 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1765 "parser.tab.c"
    break;

  case 56: /* simple_expr: simple_expr '<' additive_expr  */
#line 428 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_LT;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1777 "parser.tab.c"
    break;

  case 57: /* simple_expr: simple_expr '>' additive_expr  */
#line 436 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_GT;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1789 "parser.tab.c"
    break;

  case 58: /* simple_expr: simple_expr LE additive_expr  */
#line 444 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_LE;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1801 "parser.tab.c"
    break;

  case 59: /* simple_expr: simple_expr GE additive_expr  */
#line 452 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_GE;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1813 "parser.tab.c"
    break;

  case 60: /* simple_expr: simple_expr EQ additive_expr  */
#line 460 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_EQ;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1825 "parser.tab.c"
    break;

  case 61: /* simple_expr: simple_expr NEQ additive_expr  */
#line 468 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_NEQ;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1837 "parser.tab.c"
    break;

  case 62: /* simple_expr: simple_expr AND additive_expr  */
#line 476 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_AND;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1849 "parser.tab.c"
    break;

  case 63: /* simple_expr: simple_expr OR additive_expr  */
#line 484 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_OR;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1861 "parser.tab.c"
    break;

  case 64: /* additive_expr: term  */
#line 495 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1867 "parser.tab.c"
    break;

  case 65: /* additive_expr: additive_expr '+' term  */
#line 497 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_ADD;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1879 "parser.tab.c"
    break;

  case 66: /* additive_expr: additive_expr '-' term  */
#line 505 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_SUB;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1891 "parser.tab.c"
    break;

  case 67: /* term: factor  */
#line 516 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1897 "parser.tab.c"
    break;

  case 68: /* term: term '*' factor  */
#line 518 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_MUL;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1909 "parser.tab.c"
    break;

  case 69: /* term: term '/' factor  */
#line 526 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_DIV;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1921 "parser.tab.c"
    break;

  case 70: /* term: term '%' factor  */
#line 534 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BINARY_EXPR);
            (yyval.node_val)->as.binary_expr.op = OP_MOD;
            (yyval.node_val)->as.binary_expr.left = (yyvsp[-2].node_val);
            (yyval.node_val)->as.binary_expr.right = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1933 "parser.tab.c"
    break;

  case 71: /* factor: '(' expression ')'  */
#line 545 "parser.y"
        { (yyval.node_val) = (yyvsp[-1].node_val); }
#line 1939 "parser.tab.c"
    break;

  case 72: /* factor: var  */
#line 547 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1945 "parser.tab.c"
    break;

  case 73: /* factor: call  */
#line 549 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 1951 "parser.tab.c"
    break;

  case 74: /* factor: INT_LITERAL  */
#line 551 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_INT_LITERAL);
            (yyval.node_val)->as.int_literal.value = (yyvsp[0].int_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1961 "parser.tab.c"
    break;

  case 75: /* factor: FLOAT_LITERAL  */
#line 557 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_FLOAT_LITERAL);
            (yyval.node_val)->as.float_literal.value = (yyvsp[0].float_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1971 "parser.tab.c"
    break;

  case 76: /* factor: BOOL_LITERAL  */
#line 563 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_BOOL_LITERAL);
            (yyval.node_val)->as.bool_literal.value = (yyvsp[0].bool_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1981 "parser.tab.c"
    break;

  case 77: /* factor: STRING_LITERAL  */
#line 569 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_STRING_LITERAL);
            (yyval.node_val)->as.string_literal.value = (yyvsp[0].string_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 1991 "parser.tab.c"
    break;

  case 78: /* factor: '-' factor  */
#line 575 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_UNARY_EXPR);
            (yyval.node_val)->as.unary_expr.op = OP_SUB;
            (yyval.node_val)->as.unary_expr.expr = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 2002 "parser.tab.c"
    break;

  case 79: /* factor: '!' factor  */
#line 582 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_UNARY_EXPR);
            (yyval.node_val)->as.unary_expr.op = OP_NOT;
            (yyval.node_val)->as.unary_expr.expr = (yyvsp[0].node_val);
            (yyval.node_val)->line_number = yylineno;
        }
#line 2013 "parser.tab.c"
    break;

  case 80: /* call: IDENTIFIER '(' args ')'  */
#line 592 "parser.y"
        {
            (yyval.node_val) = create_node(NODE_FUNC_CALL);
            (yyval.node_val)->as.func_call.name = (yyvsp[-3].string_val);
            if ((yyvsp[-1].node_val) != NULL) {
                (yyval.node_val)->as.func_call.args = malloc(sizeof(ASTNode*) * 100); // Arbitrary limit
                (yyval.node_val)->as.func_call.arg_count = 0;
                ASTNode* curr = (yyvsp[-1].node_val);
                while (curr != NULL) {
                    (yyval.node_val)->as.func_call.args[(yyval.node_val)->as.func_call.arg_count++] = curr;
                    curr = curr->next;
                }
            } else {
                (yyval.node_val)->as.func_call.args = NULL;
                (yyval.node_val)->as.func_call.arg_count = 0;
            }
            (yyval.node_val)->line_number = yylineno;
        }
#line 2035 "parser.tab.c"
    break;

  case 81: /* args: arg_list  */
#line 613 "parser.y"
        { (yyval.node_val) = (yyvsp[0].node_val); }
#line 2041 "parser.tab.c"
    break;

  case 82: /* args: %empty  */
#line 615 "parser.y"
        { (yyval.node_val) = NULL; }
#line 2047 "parser.tab.c"
    break;

  case 83: /* arg_list: expression  */
#line 620 "parser.y"
        { 
            (yyval.node_val) = (yyvsp[0].node_val);
            (yyval.node_val)->next = NULL;
        }
#line 2056 "parser.tab.c"
    break;

  case 84: /* arg_list: arg_list ',' expression  */
#line 625 "parser.y"
        {
            ASTNode* curr = (yyvsp[-2].node_val);
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = (yyvsp[0].node_val);
            (yyvsp[0].node_val)->next = NULL;
            (yyval.node_val) = (yyvsp[-2].node_val);
        }
#line 2070 "parser.tab.c"
    break;


#line 2074 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 636 "parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Line %d: %s\n", yylineno, s);
}

int main(int argc, char* argv[]) {
    // Parse command line options
    bool emit_ir = false;
    bool optimize = false;
    char* input_file = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--emit-ir") == 0) {
            emit_ir = true;
        } else if (strcmp(argv[i], "--optimize") == 0) {
            optimize = true;
        } else {
            input_file = argv[i];
        }
    }
    
    // Initialize global symbols table
    global_symbol_table = create_symbol_table(100);
    
    // Parse from file if specified, otherwise from stdin
    if (input_file) {
        FILE* file = fopen(input_file, "r");
        if (!file) {
            fprintf(stderr, "Cannot open file %s\n", input_file);
            return 1;
        }
        yyin = file;
    }
    
    // Parse input
    yyparse();
    
    // Perform semantic analysis
    if (ast_root != NULL) {
        semantic_analysis(ast_root, global_symbol_table);
        
        // Print AST in text format
        printf("Abstract Syntax Tree (Text Format):\n");
        print_ast(ast_root, 0);
        
        // Generate Graphviz visualization
        printf("\nGenerating AST visualization...\n");
        print_ast_graphviz(ast_root, "ast.dot");
        printf("AST visualization saved to ast.dot\n");
        printf("To view the AST, run: dot -Tpng ast.dot -o ast.png\n");
        
        // Generate LLVM IR if requested
        if (emit_ir) {
            printf("\nGenerating LLVM IR...\n");
            
            // Get base filename without extension
            char* base_name = strdup(input_file);
            char* dot = strrchr(base_name, '.');
            if (dot) *dot = '\0';
            
            // Generate unoptimized IR
            LLVMModuleRef module = generate_ir(ast_root, base_name);
            
            if (module) {
                // Save unoptimized IR
                char unopt_filename[256];
                sprintf(unopt_filename, "%s.ll", base_name);
                dump_ir(module, unopt_filename);
                printf("Unoptimized IR saved to %s\n", unopt_filename);
                
                // Apply optimizations if requested
                if (optimize) {
                    printf("\nApplying optimizations...\n");
                    
                    // Apply optimizations
                    apply_optimizations(module, OPT_AGGRESSIVE);
                    
                    // Save optimized IR
                    char opt_filename[256];
                    sprintf(opt_filename, "%s.opt.ll", base_name);
                    dump_ir(module, opt_filename);
                    printf("Optimized IR saved to %s\n", opt_filename);
                    
                    // Generate optimization report
                    generate_optimization_report(unopt_filename, opt_filename, "optimization_report.txt");
                }
                
                // Clean up LLVM module
                LLVMDisposeModule(module);
            }
            
            free(base_name);
        }
    }
    
    // Clean up
    if (ast_root != NULL) {
        free_ast(ast_root);
    }
    
    free_symbol_table(global_symbol_table);
    
    return 0;
}
