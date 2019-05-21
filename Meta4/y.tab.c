/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "gocompiler.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    #include "structs.h"
    #include "semantic.h"
    #include "ast.h"
    #include "gen_code.h"


    #define NSYMS 100
    #define YYDEBUG 0

    #define _id_ "Id"
    #define _func_params_ "FuncParams"

    int yydebug=1;
    int i;


    int yylex(void);
    extern int print_tokens;
    extern void yyerror(const char *s);
    extern int total_lines, total_columns;
    extern char *yytext;

    char temp[MAX_TEMP];

    //AST root node
    ast_node *root = NULL;
    //AST current node
    ast_node *current = NULL;

    //Helper list (to store params, ...)
    List *util_list = NULL;

    //Symbol table head node
    Symbol_table *head = NULL;

#line 108 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 102 "gocompiler.y" /* yacc.c:355  */

    char *str;
    int int_value;
    double float_value;
    struct ast_node *node;

#line 251 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 268 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   403

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   113,   113,   119,   120,   123,   127,   130,   131,   134,
     137,   140,   190,   191,   197,   198,   199,   200,   203,   214,
     226,   239,   250,   281,   282,   288,   316,   319,   320,   321,
     322,   327,   339,   342,   347,   412,   478,   543,   609,   610,
     611,   620,   621,   622,   623,   626,   627,   641,   642,   706,
     710,   713,   714,   722,   725,   726,   731,   737,   743,   744,
     750,   756,   762,   768,   774,   780,   786,   792,   798,   804,
     810,   811,   812,   813,   814,   815,   824,   825
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTLIT", "REALLIT", "ID", "FUNC",
  "LPAR", "RPAR", "OR", "AND", "LT", "GT", "EQ", "NE", "LE", "GE",
  "SEMICOLON", "BLANKID", "PACKAGE", "RETURN", "ASSIGN", "STAR", "COMMA",
  "DIV", "MINUS", "MOD", "NOT", "PLUS", "RBRACE", "RSQ", "ELSE", "FOR",
  "IF", "VAR", "INT", "FLOAT32", "BOOL", "STRINGVAR", "PRINT", "PARSEINT",
  "CMDARGS", "RESERVED", "LSQ", "LBRACE", "STRLIT", "ADD", "SUB", "MUL",
  "$accept", "Program", "Declarations", "DeclarationsRep",
  "VarDeclaration", "VarSpec", "VarSpecRep", "Type", "FuncDeclaration",
  "Parameters", "ParametersRep", "FuncBody", "VarsAndStatements",
  "Statement", "StatementRep", "ElseCond", "ParseArgs", "FuncInvocation",
  "FuncInvocationExpr", "Expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -73

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-73)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,    17,    27,    26,   -73,     8,    23,    31,   -73,     8,
      28,    29,    37,   -73,    44,   -73,    50,    52,   -73,   -73,
      11,   160,    53,   -73,   -73,   166,   229,    65,    76,   -73,
     -73,   -73,   -73,   -73,    75,   -73,    67,    41,   -73,   229,
     -73,   -73,    70,   -73,    14,   -73,   211,   -73,   111,   211,
      87,   -73,    80,    90,    81,   -73,   -73,   -73,    41,   -73,
      97,   244,   211,    85,   -73,   -73,   101,   252,   211,   211,
     211,   -73,   356,   -73,   197,   218,     6,   108,   -73,   -73,
     -73,   100,   103,   -73,   -73,   166,   117,   -73,   119,   336,
     356,   110,   124,   295,   267,    64,   267,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     125,   -73,   -73,   127,   316,   -73,   116,   -73,   -73,   -73,
     -73,   -73,   211,   109,   -73,   -73,   375,    64,   267,   267,
     267,   267,   267,   267,   -73,   -73,   267,   -73,   267,   -73,
     141,   143,   -73,   -73,   -73,   -73,   136,   -73,   120,     7,
     106,   -73,   145,   113,   -73,   -73,   211,   161,   272,   -73,
     151,   -73
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     2,     4,
       0,     0,     0,    12,     0,     9,     0,     0,     7,     8,
       0,     0,     0,     5,     6,     0,     0,     0,     0,    14,
      15,    16,    17,    11,     0,    23,     0,     0,    21,     0,
      13,    10,    22,    44,     0,    32,    39,    26,     0,     0,
       0,    45,     0,     0,     0,    41,    40,    18,     0,    19,
       0,     0,     0,     0,    72,    73,    74,     0,     0,     0,
       0,    75,    38,    45,     0,     0,     0,     0,    27,    29,
      25,     0,     0,    28,    20,     0,     0,    51,     0,    54,
      33,     0,     0,     0,    71,    58,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    45,    45,     0,     0,    34,     0,    30,    31,    24,
      53,    52,     0,     0,    77,    76,    56,    57,    59,    60,
      61,    62,    63,    64,    67,    68,    66,    69,    65,    36,
       0,     0,    43,    42,    46,    55,     0,    37,    47,     0,
       0,    35,     0,     0,    45,    50,     0,     0,     0,    48,
       0,    49
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -73,   -73,   -73,   -73,    -6,   146,   -73,   -19,   156,   -73,
     -73,    13,   -73,   -24,   -72,   -73,   -73,   -36,    45,   -44
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,     9,    10,    15,    21,    33,    11,    27,
      42,    38,    53,   116,    77,   151,    55,    71,    88,    89
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      56,   110,    72,    16,    74,    75,    35,    37,   152,    64,
      65,    66,    54,    67,     6,     1,    25,    56,    90,    26,
      58,    61,     3,    93,    94,    95,    96,     4,    12,    82,
      52,    68,   114,    69,    70,    62,    13,    63,    14,   140,
     141,    56,     7,     5,    20,    18,    19,    81,   153,    13,
      57,   113,    59,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   119,    23,    43,    24,
      34,    84,    44,    39,    56,    99,   100,   101,   102,   103,
     104,    40,   157,    41,    45,    36,   105,    46,   106,   107,
     108,    43,   109,    60,    76,    44,    47,    78,    83,    48,
      49,     7,    85,    91,    56,    56,    50,    79,    61,    43,
      46,    51,   158,    44,    64,    65,    66,   117,    67,    80,
     118,    56,    48,    49,     7,   120,    43,   121,    46,    50,
      44,   123,   124,   144,    51,   142,    68,   115,    69,    70,
      48,    49,    43,   149,    43,    46,    44,    50,    44,   146,
     154,   150,    51,   155,   139,    73,   156,    48,    49,   161,
      22,    46,    43,    46,    50,    17,    44,   145,     0,    51,
     147,     0,   148,    48,    49,    48,    49,     0,     0,     0,
      50,    46,    50,    28,     0,    51,     0,    51,     0,     0,
     159,     0,     0,    48,    49,    29,    30,    31,    32,     0,
      50,    29,    30,    31,    32,    51,    97,    98,    99,   100,
     101,   102,   103,   104,    64,    65,    66,     0,    67,   105,
       0,   106,   107,   108,     0,   109,     0,    97,    98,    99,
     100,   101,   102,   103,   104,     0,    68,     0,    69,    70,
     105,   111,   106,   107,   108,    86,   109,    64,    65,    66,
       0,    67,    87,    92,     0,    64,    65,    66,     0,    67,
       0,     0,   112,     0,    29,    30,    31,    32,     0,    68,
       0,    69,    70,    36,     0,     0,     0,    68,     0,    69,
      70,    97,    98,    99,   100,   101,   102,   103,   104,   105,
       0,   106,   107,   108,   105,   109,   106,   107,   108,     0,
     109,     0,   160,   125,    97,    98,    99,   100,   101,   102,
     103,   104,     0,     0,     0,     0,     0,   105,     0,   106,
     107,   108,     0,   109,   143,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,     0,     0,     0,   105,     0,
     106,   107,   108,     0,   109,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,     0,     0,     0,   105,   122,
     106,   107,   108,     0,   109,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,     0,     0,     0,   105,     0,
     106,   107,   108,     0,   109,    98,    99,   100,   101,   102,
     103,   104,     0,     0,     0,     0,     0,   105,     0,   106,
     107,   108,     0,   109
};

static const yytype_int16 yycheck[] =
{
      36,    73,    46,     9,    48,    49,    25,    26,     1,     3,
       4,     5,    36,     7,     6,    19,     5,    53,    62,     8,
      39,     7,     5,    67,    68,    69,    70,     0,     5,    53,
      36,    25,    76,    27,    28,    21,     5,    23,     7,   111,
     112,    77,    34,    17,     7,    17,    17,    53,    41,     5,
      37,    45,    39,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,    85,    17,     1,    17,
      17,    58,     5,     8,   110,    11,    12,    13,    14,    15,
      16,     5,   154,     8,    17,    44,    22,    20,    24,    25,
      26,     1,    28,    23,     7,     5,    29,    17,    17,    32,
      33,    34,     5,    18,   140,   141,    39,    17,     7,     1,
      20,    44,   156,     5,     3,     4,     5,    17,     7,    29,
      17,   157,    32,    33,    34,     8,     1,     8,    20,    39,
       5,    21,     8,    17,    44,     8,    25,    29,    27,    28,
      32,    33,     1,     7,     1,    20,     5,    39,     5,    40,
      44,    31,    44,     8,    29,    44,    43,    32,    33,     8,
      14,    20,     1,    20,    39,     9,     5,   122,    -1,    44,
      29,    -1,    29,    32,    33,    32,    33,    -1,    -1,    -1,
      39,    20,    39,    23,    -1,    44,    -1,    44,    -1,    -1,
      29,    -1,    -1,    32,    33,    35,    36,    37,    38,    -1,
      39,    35,    36,    37,    38,    44,     9,    10,    11,    12,
      13,    14,    15,    16,     3,     4,     5,    -1,     7,    22,
      -1,    24,    25,    26,    -1,    28,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    25,    -1,    27,    28,
      22,    44,    24,    25,    26,     1,    28,     3,     4,     5,
      -1,     7,     8,     1,    -1,     3,     4,     5,    -1,     7,
      -1,    -1,    44,    -1,    35,    36,    37,    38,    -1,    25,
      -1,    27,    28,    44,    -1,    -1,    -1,    25,    -1,    27,
      28,     9,    10,    11,    12,    13,    14,    15,    16,    22,
      -1,    24,    25,    26,    22,    28,    24,    25,    26,    -1,
      28,    -1,    30,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    24,
      25,    26,    -1,    28,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      24,    25,    26,    -1,    28,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    -1,    28,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,
      24,    25,    26,    -1,    28,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    24,
      25,    26,    -1,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    50,     5,     0,    17,     6,    34,    51,    52,
      53,    57,     5,     5,     7,    54,    53,    57,    17,    17,
       7,    55,    54,    17,    17,     5,     8,    58,    23,    35,
      36,    37,    38,    56,    17,    56,    44,    56,    60,     8,
       5,     8,    59,     1,     5,    17,    20,    29,    32,    33,
      39,    44,    53,    61,    62,    65,    66,    60,    56,    60,
      23,     7,    21,    23,     3,     4,     5,     7,    25,    27,
      28,    66,    68,    44,    68,    68,     7,    63,    17,    17,
      29,    53,    62,    17,    60,     5,     1,     8,    67,    68,
      68,    18,     1,    68,    68,    68,    68,     9,    10,    11,
      12,    13,    14,    15,    16,    22,    24,    25,    26,    28,
      63,    44,    44,    45,    68,    29,    62,    17,    17,    56,
       8,     8,    23,    21,     8,     8,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    29,
      63,    63,     8,     8,    17,    67,    40,    29,    29,     7,
      31,    64,     1,    41,    44,     8,    43,    63,    68,    29,
      30,     8
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    53,
      53,    54,    55,    55,    56,    56,    56,    56,    57,    57,
      57,    57,    58,    59,    59,    60,    60,    61,    61,    61,
      61,    61,    61,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    66,    67,    67,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     1,     3,     3,     2,     2,     2,
       5,     3,     0,     3,     1,     1,     1,     1,     6,     6,
       7,     5,     3,     0,     4,     3,     2,     2,     2,     2,
       3,     3,     1,     3,     3,     6,     4,     5,     2,     1,
       1,     1,     4,     4,     1,     0,     3,     0,     4,    11,
       8,     3,     4,     4,     1,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     1,     1,     1,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 113 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                root = append_list(create_new_node("Program", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[0].node));
                                                                root = root==NULL ? create_new_node("Program", NULL, total_lines, total_columns-strlen(yytext)):root;
                                                            }
#line 1505 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 119 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 120 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 123 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                (yyval.node) = append_list((yyvsp[-2].node), (yyvsp[-1].node));

                                                            }
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 127 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                (yyval.node) = append_list((yyvsp[-2].node), (yyvsp[-1].node));
                                                            }
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 130 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 131 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 134 "gocompiler.y" /* yacc.c:1646  */
    {   
                                                                (yyval.node) = (yyvsp[0].node);
                                                            }
#line 1554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 137 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-2].node);}
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 140 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node* id_node = create_new_node("Id", (yyvsp[-2].str), total_lines, total_columns-strlen(yytext));
                                                                ast_node *type_node = create_new_node((yyvsp[0].str), NULL, total_lines, total_columns-strlen(yytext));
                                                                //Get list of vars
                                                                ast_node *list = (yyvsp[-1].node);
                                                                //printf("LIST:\n\n");
                                                                //print_ast_tree(list, 0);
                                                                //printf("\n\n");
                                                                ast_node *current;
                                                                ast_node *list_ids = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node *vardecl = create_new_node("VarDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(vardecl, type_node); add_ast_node(vardecl, id_node);
                                                                add_ast_node(list_ids, vardecl);
                                                                int i=0;
                                                                ast_node *parent = NULL;
                                                                for (current = list; current != NULL;){
                                                                    if (strcmp(current->name, "empty")==0) continue;
                                                                    //Create VarDecl node
                                                                    vardecl = create_new_node("VarDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                    //Add id and type
                                                                    add_ast_node(vardecl, create_new_node((yyvsp[0].str), NULL, total_lines, total_columns-strlen(yytext)));
                                                                    vardecl->children[vardecl->num_children] = create_new_node("empty", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(vardecl->children[vardecl->num_children], current);
                                                                    vardecl->num_children += 1;
                                                                    //Add to the list
                                                                    list_ids->children[list_ids->num_children] = vardecl;
                                                                    list_ids->num_children+=1;
                                                                    
                                                                    /*Next iteration*/
                                                                    if (current->children[0]!=NULL)
                                                                    {
                                                                        parent = current;
                                                                        current = current->children[0];
                                                                    }
                                                                    else if (parent!=NULL)
                                                                    {
                                                                        if (parent->num_children<=1) break;
                                                                        else 
                                                                        {
                                                                            current = parent->children[i+1];
                                                                            i+=1;
                                                                        }
                                                                    }
                                                                    else break;
                                                                    
                                                                }
                                                                (yyval.node) = list_ids;
                                                            }
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 190 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 191 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                if ((yyvsp[-2].node)==NULL) (yyval.node) = create_new_node("Id", (yyvsp[0].str), total_lines, total_columns-strlen(yytext));
                                                                else (yyval.node) = add_ast_node((yyvsp[-2].node), create_new_node("Id", (yyvsp[0].str), total_lines, total_columns-strlen(yytext)));
                                                            }
#line 1628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 197 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.str) = "Int";}
#line 1634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 198 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.str) = "Float32";}
#line 1640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 199 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.str) = "Bool";}
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 200 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.str) = "String";}
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 203 "gocompiler.y" /* yacc.c:1646  */
    { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node *funcheader = create_new_node("FuncHeader", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcParams = create_new_node("FuncParams", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(funcheader, create_new_node("Id", (yyvsp[-4].str), total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(funcheader, create_new_node((yyvsp[-1].str), NULL, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(funcheader, funcParams);
                                                                add_ast_node(new_node, funcheader);
                                                                add_ast_node(new_node, (yyvsp[0].node));
                                                                (yyval.node) = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), new_node);
                                                            }
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 214 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcParams = create_new_node("FuncParams", NULL, total_lines, total_columns-strlen(yytext));

                                                                add_ast_node(funcHeader, create_new_node("Id", (yyvsp[-4].str), total_lines, total_columns-strlen(yytext)));
                                                                append_list(funcParams, (yyvsp[-2].node));
                                                                add_ast_node(funcHeader, funcParams);
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, (yyvsp[0].node));
                                                                (yyval.node) = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), new_node);
                                                            }
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 226 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcParams = create_new_node("FuncParams", NULL, total_lines, total_columns-strlen(yytext));

                                                                add_ast_node(funcHeader, create_new_node("Id", (yyvsp[-5].str), total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(funcHeader, create_new_node((yyvsp[-1].str), NULL, total_lines, total_columns-strlen(yytext)));
                                                                append_list(funcParams, (yyvsp[-3].node));
                                                                add_ast_node(funcHeader, funcParams);
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, (yyvsp[0].node));
                                                                (yyval.node) = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), new_node);
                                                            }
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 239 "gocompiler.y" /* yacc.c:1646  */
    { 
                                                                ast_node* new_node = create_new_node("FuncDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* funcHeader =  create_new_node("FuncHeader", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(funcHeader, create_new_node("Id", (yyvsp[-3].str), total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(funcHeader, create_new_node("FuncParams", NULL, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(new_node, funcHeader);
                                                                add_ast_node(new_node, (yyvsp[0].node));
                                                                (yyval.node) = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), new_node);
                                                            }
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 250 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                //Build first parameter
                                                                ast_node *first = create_new_node("ParamDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(first, create_new_node((yyvsp[-1].str), NULL, total_lines, total_columns-strlen(yytext)));
                                                                add_ast_node(first, create_new_node("Id", (yyvsp[-2].str), total_lines, total_columns-strlen(yytext)));

                                                                //Append the other parameters
                                                                ast_node *root = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(root, first);
                                                                for (List* current = util_list->next; current !=NULL; current = current->next){
                                                                    ast_node *new_node = create_new_node("ParamDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                    add_ast_node(new_node, create_new_node(current->type, NULL, total_lines, total_columns-strlen(yytext)));
                                                                    add_ast_node(new_node, create_new_node("Id", current->name, total_lines, total_columns-strlen(yytext)));
                                                                    add_ast_node(root, new_node);
                                                                }

                                                                /*Free the list*/
                                                                List *next = util_list->next;
                                                                for (List *current = util_list->next; current != NULL; current = next){
                                                                    next = current->next;
                                                                    free(current);
                                                                }

                                                                /*Reinit, for next FuncDecl*/
                                                                util_list = malloc(sizeof(struct list));
                                                                util_list->next = NULL;

                                                                (yyval.node) = root;
                                                            }
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 281 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 282 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                //Store this param's name and type
                                                                insert_paramdecl(util_list, (yyvsp[-1].str), (yyvsp[0].str));
                                                            }
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 288 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node* vars_stmt = (yyvsp[-1].node);
                                                                ast_node* node;
                                                                /*Check if list starts with a statement or vardecl node*/
                                                                if (vars_stmt != NULL
                                                                    && (strcmp(vars_stmt->name, "If")==0
                                                                        || strcmp(vars_stmt->name, "For")==0
                                                                        || strcmp(vars_stmt->name, "Return")==0
                                                                        || strcmp(vars_stmt->name, "Id")==0
                                                                        || strcmp(vars_stmt->name, "Call")==0
                                                                        || strcmp(vars_stmt->name, "ParseArgs")==0
                                                                        || strcmp(vars_stmt->name, "Print")==0
                                                                        || strcmp(vars_stmt->name, "Assign")==0
                                                                        || strcmp(vars_stmt->name, "Block")==0
                                                                        || strcmp(vars_stmt->name,"VarDecl")==0
                                                                        )
                                                                    )
                                                                {
                                                                    //printf("Not a list\n");
                                                                    node = add_ast_node(create_new_node("FuncBody", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node));
                                                                }
                                                                else{
                                                                    //printf("It's a list\n");
                                                                    //printf("List contains:\n");
                                                                    //print_ast_tree($2, 0);
                                                                    node = append_list(create_new_node("FuncBody", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node));
                                                                }
                                                                (yyval.node) = node;}
#line 1799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 316 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = create_new_node("FuncBody", NULL, total_lines, total_columns-strlen(yytext));}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 319 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 320 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 321 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 322 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *root = create_new_node("VarDecl", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(root, (yyvsp[-2].node));
                                                                (yyval.node) = root;
                                                            }
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 327 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *root = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                ast_node* list = (yyvsp[-2].node);
                                                                if (list != NULL && strcmp(list->name, "root")==0){
                                                                    append_list(root, (yyvsp[-2].node));
                                                                }
                                                                else add_ast_node(root, list);
                                                                if ((yyvsp[-1].node) == NULL) (yyval.node) = NULL;
                                                                else (yyval.node) = add_ast_node(root, (yyvsp[-1].node));
                                                                
                                                                //$$ = root;
                                                            }
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 339 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 342 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Assign", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, create_new_node("Id", (yyvsp[-2].str), total_lines, total_columns-strlen(yytext)));
                                                                (yyval.node) = add_ast_node(node, (yyvsp[0].node));
                                                            }
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 347 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node));
                                                                if ((yyvsp[-1].node)!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        if (new_list->children[0] != NULL && new_list->num_children>1){
                                                                            ast_node* block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);
                                                                            (yyval.node) = block;
                                                                        }
                                                                        else (yyval.node) = new_list;
                                                                    }
                                                                    else{
                                                                        if (list->children[0] != NULL && list->children[0]->num_children>1){
                                                                            ast_node* block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                            (yyval.node) = block;
                                                                        }
                                                                        else (yyval.node) = list;
                                                                    }
                                                                }
                                                                else (yyval.node) = NULL;
                                                                
                                                            }
#line 1936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 412 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *if_node = create_new_node("If", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(if_node, (yyvsp[-4].node));
                                                                
                                                                ast_node *block = NULL;
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-2].node));
                                                                
                                                                if ((yyvsp[-2].node)!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);

                                                                    }
                                                                    else {
                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-2].node)));
                                                                    }
                                                                }

                                                                if (block==NULL) block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-2].node)));
                                                                add_ast_node(if_node, block);
                                                                add_ast_node(if_node, (yyvsp[0].node));
                                                                (yyval.node) = if_node;
                                                            }
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 478 "gocompiler.y" /* yacc.c:1646  */
    {   
                                                                ast_node *for_node = create_new_node("For", NULL, total_lines, total_columns-strlen(yytext));

                                                                ast_node *block = NULL;
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node));
                                                                //printf("Reached 2\n");
                                                                
                                                                if ((yyvsp[-1].node)!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);

                                                                    }
                                                                    else {
                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node)));
                                                                    }
                                                                }

                                                                if (block==NULL) block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node)));
                                                                add_ast_node(for_node, block);
                                                                (yyval.node) = for_node;
                                                            }
#line 2077 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 543 "gocompiler.y" /* yacc.c:1646  */
    {   ast_node *for_node = create_new_node("For", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(for_node, (yyvsp[-3].node));
                                                                
                                                                ast_node *block = NULL;
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node));
                                                                //printf("Reached 2\n");
                                                                
                                                                if ((yyvsp[-1].node)!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);

                                                                    }
                                                                    else {
                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node)));
                                                                    }
                                                                }

                                                                if (block==NULL) block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node)));

                                                                add_ast_node(for_node, block);
                                                                (yyval.node) = for_node;
                                                            }
#line 2148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 609 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = add_ast_node(create_new_node("Return", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[0].node));}
#line 2154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 610 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = create_new_node("Return", NULL, total_lines, total_columns-strlen(yytext));}
#line 2160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 611 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *list = (yyvsp[0].node);
                                                                ast_node* node;
                                                                if (list != NULL && strcmp(list->name, "root")==0){
                                                                    node = append_list(create_new_node("Call", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                }
                                                                else node = add_ast_node(create_new_node("Call", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                (yyval.node) = node;
                                                            }
#line 2174 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 620 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = add_ast_list(create_new_node("ParseArgs", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[0].node));}
#line 2180 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 621 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = add_ast_node(create_new_node("Print", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node));}
#line 2186 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 622 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = add_ast_node(create_new_node("Print", NULL, total_lines, total_columns-strlen(yytext)), create_new_node("StrLit", (yyvsp[-1].str), total_lines, total_columns-strlen(yytext)));}
#line 2192 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 623 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = create_new_node("error", NULL, total_lines, total_columns-strlen(yytext));}
#line 2198 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 626 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = NULL;}
#line 2204 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 627 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                if ((yyvsp[-2].node)==NULL) (yyval.node) = (yyvsp[-1].node);
                                                                else{
                                                                    /*If node doesn't yet have a 'next' node*/
                                                                    if ((yyvsp[-2].node)->has_next_node!=1){
                                                                        add_ast_node((yyvsp[-2].node), create_new_node("next", NULL, total_lines, total_columns-strlen(yytext)));
                                                                        (yyvsp[-2].node)->has_next_node=1;
                                                                    }
                                                                    (yyval.node) = add_ast_node((yyvsp[-2].node), (yyvsp[-1].node));
                                                                }
                                                                
                                                            }
#line 2221 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 641 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext));}
#line 2227 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 642 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *block = NULL;
                                                                ast_node *list = add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node));
                                                                //printf("Reached 2\n");
                                                                
                                                                if ((yyvsp[-1].node)!=NULL){
                                                                    /*List is in format: child1
                                                                                     ..child1_child1
                                                                                     ..next
                                                                                     ..child2
                                                                                     ....chiild2_child1
                                                                                     ..child3
                                                                                     ....child3_child1
                                                                    Fix this, set children after 'next' as children of parent node*/
                                                                    ast_node* new_list = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                    ast_node *current = list->children[0]->children[0];
                                                                    i=0;

                                                                    //Copy first children of the list
                                                                    ast_node *first_child = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                    copy_ast_data(first_child, list->children[0]);

                                                                    /*Find 'next' node*/
                                                                    for (i=0; current!=NULL ;){
                                                                        if (strcmp(current->name, "next")==0){
                                                                            break;
                                                                        }

                                                                        ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                        copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                        add_ast_node(first_child, new_node);

                                                                        i+=1;
                                                                        current = list->children[0]->children[i];
                                                                    }

                                                                    add_ast_node(new_list, first_child);

                                                                    /*If next was found*/
                                                                    if (current!=NULL && strcmp(current->name, "next")==0){
                                                                        current = list->children[0]->children[i+1]; //Node after 'next'
                                                                        for (; current!=NULL; ){

                                                                            ast_node *new_node = create_new_node("new", NULL, total_lines, total_columns-strlen(yytext));
                                                                            copy_ast_data(new_node, current); copy_ast_children(new_node, current);
                                                                            add_ast_node(new_list, new_node);

                                                                            i+=1;
                                                                            current=list->children[0]->children[i+1];
                                                                        }

                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), new_list);

                                                                    }
                                                                    else {
                                                                        block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node)));
                                                                    }
                                                                }

                                                                if (block==NULL) block = append_list(create_new_node("Block", NULL, total_lines, total_columns-strlen(yytext)), add_ast_node(create_new_node("root", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[-1].node)));
                                                                (yyval.node) = block;
                                                            }
#line 2294 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 706 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                                ast_node *id = create_new_node("Id", (yyvsp[-10].str), total_lines, total_columns-strlen(yytext));                                                                                
                                                                                (yyval.node) = add_ast_node(id, (yyvsp[-2].node));
                                                                            }
#line 2303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 710 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = create_new_node("error", NULL, total_lines, total_columns-strlen(yytext));}
#line 2309 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 713 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = create_new_node("Id", (yyvsp[-2].str), total_lines, total_columns-strlen(yytext));}
#line 2315 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 714 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *id = create_new_node("Id", (yyvsp[-3].str), total_lines, total_columns-strlen(yytext));
                                                                ast_node *root = create_new_node("root", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(root, id);
                                                                add_ast_node(root, (yyvsp[-1].node));

                                                                (yyval.node) = root;
                                                            }
#line 2328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 722 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = create_new_node("error", NULL, total_lines, total_columns-strlen(yytext));}
#line 2334 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 725 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2340 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 726 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                (yyval.node) = add_ast_node((yyvsp[-2].node), (yyvsp[0].node));
                                                            }
#line 2348 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 731 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Or", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2359 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 737 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("And", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2370 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 743 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = add_ast_node(create_new_node("Not", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[0].node));}
#line 2376 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 744 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Lt", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 750 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Gt", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2398 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 756 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Eq", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 762 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Ne", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2420 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 768 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Le", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 774 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Ge", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 780 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Add", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 786 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Sub", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2464 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 792 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Mul", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2475 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 798 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Div", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 804 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *node = create_new_node("Mod", NULL, total_lines, total_columns-strlen(yytext));
                                                                add_ast_node(node, (yyvsp[-2].node));
                                                                add_ast_node(node, (yyvsp[0].node));
                                                                (yyval.node) = node;
                                                            }
#line 2497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 810 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = add_ast_node(create_new_node("Plus", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[0].node));}
#line 2503 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 811 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = add_ast_node(create_new_node("Minus", NULL, total_lines, total_columns-strlen(yytext)), (yyvsp[0].node));}
#line 2509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 812 "gocompiler.y" /* yacc.c:1646  */
    {sprintf(temp, "%d", (yyvsp[0].int_value)); (yyval.node) = create_new_node("IntLit", temp, total_lines, total_columns-strlen(yytext));}
#line 2515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 813 "gocompiler.y" /* yacc.c:1646  */
    {sprintf(temp, "%f", (yyvsp[0].float_value)); (yyval.node) = create_new_node("RealLit", temp, total_lines, total_columns-strlen(yytext));}
#line 2521 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 814 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = create_new_node("Id", (yyvsp[0].str), total_lines, total_columns-strlen(yytext));}
#line 2527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 815 "gocompiler.y" /* yacc.c:1646  */
    {
                                                                ast_node *list = (yyvsp[0].node);
                                                                ast_node* node;
                                                                if (list != NULL && strcmp(list->name, "root")==0){
                                                                    node = append_list(create_new_node("Call", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                }
                                                                else node = add_ast_node(create_new_node("Call", NULL, total_lines, total_columns-strlen(yytext)), list);
                                                                (yyval.node) = node;
                                                            }
#line 2541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 824 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 2547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 825 "gocompiler.y" /* yacc.c:1646  */
    {(yyval.node) = create_new_node("error", NULL, total_lines, total_columns-strlen(yytext));}
#line 2553 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2557 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 828 "gocompiler.y" /* yacc.c:1906  */
   


int main(int argc, char** argv) {
    //int yydebug;
    #if YYDEBUG
        yydebug = 1;
    #endif

    int lex_only = 0;
    int print_tree = 0;
    int print_symbols = 0;

    if (argc!=1){
        if (strcmp(argv[1], "-l")==0) lex_only = 1;
        if (strcmp(argv[1], "-t")==0) print_tree = 1;
        if (strcmp(argv[1], "-s")==0) print_symbols = 1;
        if (argc == 3 && strcmp(argv[2], "-d")==0) print_tokens=0; //For debugging only
    }

    if (lex_only==1){
        while(yylex()){} //Print only lex output
    }
    else{
        print_tokens=0; //Dont print lex output | Set lex file print_tokens flag as 0
        /*Create a new symbol table*/
        head = malloc(sizeof (struct symbol_table));
        strcpy(head->name, "global");
        head->next_table = NULL; head->child = NULL;

        /*Initialize list to hold ParamDecl*/
        util_list = malloc(sizeof(struct list));
        util_list->next = NULL;

        /*Parse*/
        yyparse();

        /*Semantic analysis*/
        if (print_symbols==1) check_program(head, root);

        if (print_tree==1) print_ast_tree(root, 0);
        if (print_symbols==1){
            print_symbol_table(head);
            print_ast_tree(root, 0);
        }

        generate_code(root);

        free_ast_tree(root);
        free_symbol_table(head);
    }
    return 0;
} 
