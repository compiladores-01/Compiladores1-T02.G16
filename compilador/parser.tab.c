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
#line 1 "parser/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ast.h"
#include "tipos.h"
#include "tabela.h"
#include "geracao.h"

extern FILE *yyin;
extern int yylineno;
char arquivo_saida[256] = "saida.c";

#line 86 "parser.tab.c"

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
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_BOOLEAN = 6,                    /* BOOLEAN  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_PRINT = 8,                      /* PRINT  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_DEF = 12,                       /* DEF  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_COLON = 14,                     /* COLON  */
  YYSYMBOL_NEWLINE = 15,                   /* NEWLINE  */
  YYSYMBOL_COMMA = 16,                     /* COMMA  */
  YYSYMBOL_INDENT = 17,                    /* INDENT  */
  YYSYMBOL_DEDENT = 18,                    /* DEDENT  */
  YYSYMBOL_LPAREN = 19,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 20,                    /* RPAREN  */
  YYSYMBOL_PLUS = 21,                      /* PLUS  */
  YYSYMBOL_MINUS = 22,                     /* MINUS  */
  YYSYMBOL_TIMES = 23,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 24,                    /* DIVIDE  */
  YYSYMBOL_EQ = 25,                        /* EQ  */
  YYSYMBOL_NEQ = 26,                       /* NEQ  */
  YYSYMBOL_LEQ = 27,                       /* LEQ  */
  YYSYMBOL_GEQ = 28,                       /* GEQ  */
  YYSYMBOL_LT = 29,                        /* LT  */
  YYSYMBOL_GT = 30,                        /* GT  */
  YYSYMBOL_ATRIBUES = 31,                  /* ATRIBUES  */
  YYSYMBOL_MENOR_QUE_ELSE = 32,            /* MENOR_QUE_ELSE  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_programa = 34,                  /* programa  */
  YYSYMBOL_lista_comandos = 35,            /* lista_comandos  */
  YYSYMBOL_comando = 36,                   /* comando  */
  YYSYMBOL_atribuicao = 37,                /* atribuicao  */
  YYSYMBOL_comando_print = 38,             /* comando_print  */
  YYSYMBOL_comando_return = 39,            /* comando_return  */
  YYSYMBOL_comando_if = 40,                /* comando_if  */
  YYSYMBOL_comando_while = 41,             /* comando_while  */
  YYSYMBOL_bloco = 42,                     /* bloco  */
  YYSYMBOL_definicao_funcao = 43,          /* definicao_funcao  */
  YYSYMBOL_44_1 = 44,                      /* $@1  */
  YYSYMBOL_lista_parametros = 45,          /* lista_parametros  */
  YYSYMBOL_parametros = 46,                /* parametros  */
  YYSYMBOL_lista_argumentos = 47,          /* lista_argumentos  */
  YYSYMBOL_argumentos = 48,                /* argumentos  */
  YYSYMBOL_expressao = 49                  /* expressao  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 35 "parser/parser.y"

int yylex(void);
void yyerror(const char *s);

int erros_semanticos = 0;
static int nivel_funcao = 0;

static void erroSemantico(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Erro semantico: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    erros_semanticos++;
}

static const char *nomeTipo(TipoDado t) {
    switch (t) {
        case TIPO_INTEIRO: return "inteiro";
        case TIPO_FLOAT:   return "float";
        case TIPO_STRING:  return "string";
        case TIPO_BOOLEAN: return "boolean";
        case TIPO_FUNCAO:  return "funcao";
        default:           return "desconhecido";
    }
}

static int ehNumerico(TipoDado t) {
    return t == TIPO_INTEIRO || t == TIPO_FLOAT;
}

static Expr novaExpr(NoAST *no, TipoDado tipo) {
    Expr e;
    e.no = no;
    e.tipo = tipo;
    return e;
}

/* Operadores aritmeticos. Se algum operando ja e invalido, nao gera
   erro em cascata. */
static TipoDado tipoAritmetico(char op, TipoDado a, TipoDado b) {
    if (a == TIPO_DESCONHECIDO || b == TIPO_DESCONHECIDO)
        return TIPO_DESCONHECIDO;

    if (op == '+' && a == TIPO_STRING && b == TIPO_STRING)
        return TIPO_STRING;

    if (ehNumerico(a) && ehNumerico(b)) {
        if (op == '/') return TIPO_FLOAT;   /* '/' de Python e divisao real */
        return (a == TIPO_FLOAT || b == TIPO_FLOAT) ? TIPO_FLOAT : TIPO_INTEIRO;
    }

    erroSemantico("operador '%c' invalido entre %s e %s", op, nomeTipo(a), nomeTipo(b));
    return TIPO_DESCONHECIDO;
}

/* Comparacoes: numero com numero, ou dois operandos do mesmo tipo. */
static TipoDado tipoComparacao(const char *op, TipoDado a, TipoDado b) {
    if (a == TIPO_DESCONHECIDO || b == TIPO_DESCONHECIDO)
        return TIPO_DESCONHECIDO;

    if ((ehNumerico(a) && ehNumerico(b)) || a == b)
        return TIPO_BOOLEAN;

    erroSemantico("comparacao '%s' invalida entre %s e %s", op, nomeTipo(a), nomeTipo(b));
    return TIPO_DESCONHECIDO;
}

static void verificarCondicao(const char *estrutura, TipoDado t) {
    if (t != TIPO_BOOLEAN && t != TIPO_DESCONHECIDO)
        erroSemantico("condicao do '%s' deve ser boolean, mas e %s", estrutura, nomeTipo(t));
}

static void atribuir(const char *nome, TipoDado t) {
    Simbolo *s = buscarSimbolo(nome);

    if (s == NULL) {
        if (!inserirSimbolo(nome, t))
            erroSemantico("nao foi possivel registrar a variavel '%s'", nome);
        return;
    }

    if (s->tipo == TIPO_FUNCAO) {
        erroSemantico("nao e possivel atribuir a funcao '%s'", nome);
        return;
    }

    if (s->tipo == t || t == TIPO_DESCONHECIDO)
        return;

    if (s->tipo == TIPO_FLOAT && t == TIPO_INTEIRO)
        return;

    erroSemantico("variavel '%s' e %s e nao pode receber %s",
                  nome, nomeTipo(s->tipo), nomeTipo(t));
}

static void adicionarComando(NoAST **lista, NoAST *comando) {
    if (!comando) return;
    NoAST *item = criarNoListaCmd(comando);
    if (!item) return;
    if (!*lista) {
        *lista = item;
        return;
    }
    NoAST *ultimo = *lista;
    while (ultimo->proximo) ultimo = ultimo->proximo;
    ultimo->proximo = item;
}

static NoAST *montarChamada(char *nome, NoAST *argumentos) {
    Simbolo *s = buscarSimbolo(nome);
    if (s == NULL)
        erroSemantico("funcao '%s' nao foi definida", nome);
    else if (s->tipo != TIPO_FUNCAO)
        erroSemantico("'%s' nao e uma funcao", nome);
    NoAST *no = criarNoChamada(nome, argumentos);
    free(nome);
    return no;
}

#line 293 "parser.tab.c"

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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   130

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  47
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  91

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   184,   184,   198,   202,   209,   210,   211,   212,   215,
     216,   217,   218,   222,   230,   234,   239,   247,   251,   258,
     265,   269,   269,   286,   287,   291,   298,   308,   309,   313,
     317,   324,   325,   326,   330,   331,   343,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "STRING",
  "NUMBER", "BOOLEAN", "FLOAT", "PRINT", "IF", "ELSE", "WHILE", "DEF",
  "RETURN", "COLON", "NEWLINE", "COMMA", "INDENT", "DEDENT", "LPAREN",
  "RPAREN", "PLUS", "MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LEQ", "GEQ",
  "LT", "GT", "ATRIBUES", "MENOR_QUE_ELSE", "$accept", "programa",
  "lista_comandos", "comando", "atribuicao", "comando_print",
  "comando_return", "comando_if", "comando_while", "bloco",
  "definicao_funcao", "$@1", "lista_parametros", "parametros",
  "lista_argumentos", "argumentos", "expressao", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      82,    -5,    -4,     2,     2,    15,     2,   -51,    20,    82,
     -51,     7,    17,    22,   -51,   -51,   -51,     2,     2,     2,
      11,   -51,   -51,   -51,   -51,     2,    37,    54,    21,    99,
     -51,   -51,   -51,   -51,   -51,    19,    36,    99,    99,    78,
       2,    89,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,   -51,    40,     2,   -51,    49,   -51,
      39,    47,    12,    12,   -51,   -51,   -11,   -11,   -11,   -11,
     -11,   -11,   -51,    67,   -51,    99,   -51,    82,    57,   -51,
      52,    58,    16,    38,    72,    84,   -51,   -51,    38,   -51,
     -51
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    16,    12,     0,     2,
       3,     0,     0,     0,     9,    10,    11,    27,     0,     0,
      35,    33,    31,    34,    32,     0,     0,     0,     0,    15,
       1,     4,     5,     6,     7,     0,    28,    29,    13,     0,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,    14,     0,    47,
       0,    17,    37,    38,    39,    40,    41,    42,    45,    46,
      43,    44,    19,    23,     8,    30,    36,     0,     0,    25,
       0,    24,     0,     0,     0,     0,    20,    18,     0,    26,
      22
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -51,   -51,    53,    -9,   -51,   -51,   -51,   -51,   -51,   -50,
     -51,   -51,   -51,   -51,    48,   -51,    -2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     8,     9,    10,    11,    12,    13,    14,    15,    61,
      16,    73,    80,    81,    35,    36,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      31,    26,    27,    72,    29,    20,    21,    22,    23,    24,
      43,    44,    45,    46,    17,    19,    38,    39,    28,     1,
      30,    25,    32,    41,     2,     3,    18,     4,     5,     6,
      40,     7,    33,    87,    86,    45,    46,    34,    90,    55,
      54,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    42,    56,    60,    75,    74,    77,    78,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    76,
      79,    83,    84,    31,    85,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,     1,    88,    89,    58,     0,
       2,     3,     0,     4,     5,     6,     0,     7,    57,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    59,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      82
};

static const yytype_int8 yycheck[] =
{
       9,     3,     4,    53,     6,     3,     4,     5,     6,     7,
      21,    22,    23,    24,    19,    19,    18,    19,     3,     3,
       0,    19,    15,    25,     8,     9,    31,    11,    12,    13,
      19,    15,    15,    83,    18,    23,    24,    15,    88,    20,
      19,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    14,    16,    15,    56,    15,    17,    10,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    14,    20,
       3,    14,    20,    82,    16,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     3,    14,     3,    40,    -1,
       8,     9,    -1,    11,    12,    13,    -1,    15,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     8,     9,    11,    12,    13,    15,    34,    35,
      36,    37,    38,    39,    40,    41,    43,    19,    31,    19,
       3,     4,     5,     6,     7,    19,    49,    49,     3,    49,
       0,    36,    15,    15,    15,    47,    48,    49,    49,    49,
      19,    49,    14,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    14,    19,    20,    16,    20,    47,    20,
      15,    42,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    42,    44,    15,    49,    20,    17,    10,     3,
      45,    46,    35,    14,    20,    16,    18,    42,    14,     3,
      42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    36,
      36,    36,    36,    37,    38,    39,    39,    40,    40,    41,
      42,    44,    43,    45,    45,    46,    46,    47,    47,    48,
      48,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     2,     5,     1,
       1,     1,     1,     3,     4,     2,     1,     4,     7,     4,
       4,     0,     8,     0,     1,     1,     3,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3
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
  case 2: /* programa: lista_comandos  */
#line 184 "parser/parser.y"
                   {
        if (erros_semanticos == 0) {
            NoAST *raiz = criarNoPrograma((yyvsp[0].no));
            imprimirAST(raiz);
            if (gerarCodigoC(raiz, arquivo_saida) != 0)
                erros_semanticos++;
            liberarAST(raiz);
        } else {
            liberarAST((yyvsp[0].no));
        }
    }
#line 1320 "parser.tab.c"
    break;

  case 3: /* lista_comandos: comando  */
#line 198 "parser/parser.y"
            {
        (yyval.no) = NULL;
        adicionarComando(&(yyval.no), (yyvsp[0].no));
    }
#line 1329 "parser.tab.c"
    break;

  case 4: /* lista_comandos: lista_comandos comando  */
#line 202 "parser/parser.y"
                           {
        (yyval.no) = (yyvsp[-1].no);
        adicionarComando(&(yyval.no), (yyvsp[0].no));
    }
#line 1338 "parser.tab.c"
    break;

  case 5: /* comando: atribuicao NEWLINE  */
#line 209 "parser/parser.y"
                       { (yyval.no) = (yyvsp[-1].no); }
#line 1344 "parser.tab.c"
    break;

  case 6: /* comando: comando_print NEWLINE  */
#line 210 "parser/parser.y"
                          { (yyval.no) = (yyvsp[-1].no); }
#line 1350 "parser.tab.c"
    break;

  case 7: /* comando: comando_return NEWLINE  */
#line 211 "parser/parser.y"
                           { (yyval.no) = (yyvsp[-1].no); }
#line 1356 "parser.tab.c"
    break;

  case 8: /* comando: IDENTIFIER LPAREN lista_argumentos RPAREN NEWLINE  */
#line 212 "parser/parser.y"
                                                      {
        (yyval.no) = montarChamada((yyvsp[-4].texto), (yyvsp[-2].no));
    }
#line 1364 "parser.tab.c"
    break;

  case 9: /* comando: comando_if  */
#line 215 "parser/parser.y"
               { (yyval.no) = (yyvsp[0].no); }
#line 1370 "parser.tab.c"
    break;

  case 10: /* comando: comando_while  */
#line 216 "parser/parser.y"
                  { (yyval.no) = (yyvsp[0].no); }
#line 1376 "parser.tab.c"
    break;

  case 11: /* comando: definicao_funcao  */
#line 217 "parser/parser.y"
                     { (yyval.no) = (yyvsp[0].no); }
#line 1382 "parser.tab.c"
    break;

  case 12: /* comando: NEWLINE  */
#line 218 "parser/parser.y"
            { (yyval.no) = NULL; }
#line 1388 "parser.tab.c"
    break;

  case 13: /* atribuicao: IDENTIFIER ATRIBUES expressao  */
#line 222 "parser/parser.y"
                                  {
        atribuir((yyvsp[-2].texto), (yyvsp[0].expr).tipo);
        (yyval.no) = criarNoAtrib(criarNoId((yyvsp[-2].texto)), (yyvsp[0].expr).no);
        free((yyvsp[-2].texto));
    }
#line 1398 "parser.tab.c"
    break;

  case 14: /* comando_print: PRINT LPAREN expressao RPAREN  */
#line 230 "parser/parser.y"
                                  { (yyval.no) = criarNoPrint((yyvsp[-1].expr).no); }
#line 1404 "parser.tab.c"
    break;

  case 15: /* comando_return: RETURN expressao  */
#line 234 "parser/parser.y"
                     {
        if (nivel_funcao == 0)
            erroSemantico("'return' fora de funcao");
        (yyval.no) = criarNoReturn((yyvsp[0].expr).no);
    }
#line 1414 "parser.tab.c"
    break;

  case 16: /* comando_return: RETURN  */
#line 239 "parser/parser.y"
           {
        if (nivel_funcao == 0)
            erroSemantico("'return' fora de funcao");
        (yyval.no) = criarNoReturn(NULL);
    }
#line 1424 "parser.tab.c"
    break;

  case 17: /* comando_if: IF expressao COLON bloco  */
#line 247 "parser/parser.y"
                                                  {
        verificarCondicao("if", (yyvsp[-2].expr).tipo);
        (yyval.no) = criarNoIf((yyvsp[-2].expr).no, (yyvsp[0].no), NULL);
    }
#line 1433 "parser.tab.c"
    break;

  case 18: /* comando_if: IF expressao COLON bloco ELSE COLON bloco  */
#line 251 "parser/parser.y"
                                              {
        verificarCondicao("if", (yyvsp[-5].expr).tipo);
        (yyval.no) = criarNoIf((yyvsp[-5].expr).no, (yyvsp[-3].no), (yyvsp[0].no));
    }
#line 1442 "parser.tab.c"
    break;

  case 19: /* comando_while: WHILE expressao COLON bloco  */
#line 258 "parser/parser.y"
                                {
        verificarCondicao("while", (yyvsp[-2].expr).tipo);
        (yyval.no) = criarNoWhile((yyvsp[-2].expr).no, (yyvsp[0].no));
    }
#line 1451 "parser.tab.c"
    break;

  case 20: /* bloco: NEWLINE INDENT lista_comandos DEDENT  */
#line 265 "parser/parser.y"
                                         { (yyval.no) = (yyvsp[-1].no); }
#line 1457 "parser.tab.c"
    break;

  case 21: /* $@1: %empty  */
#line 269 "parser/parser.y"
                          {
        if (nivel_funcao > 0)
            erroSemantico("funcoes aninhadas nao sao suportadas");
        if (!inserirSimbolo((yyvsp[-1].texto), TIPO_FUNCAO))
            erroSemantico("nome '%s' ja foi declarado", (yyvsp[-1].texto));
        nivel_funcao++;
        entrarEscopo();
    }
#line 1470 "parser.tab.c"
    break;

  case 22: /* definicao_funcao: DEF IDENTIFIER LPAREN $@1 lista_parametros RPAREN COLON bloco  */
#line 277 "parser/parser.y"
                                        {
        nivel_funcao--;
        (yyval.no) = criarNoFunc((yyvsp[-6].texto), (yyvsp[-3].no), (yyvsp[0].no));
        sairEscopo();
        free((yyvsp[-6].texto));
    }
#line 1481 "parser.tab.c"
    break;

  case 23: /* lista_parametros: %empty  */
#line 286 "parser/parser.y"
                { (yyval.no) = NULL; }
#line 1487 "parser.tab.c"
    break;

  case 24: /* lista_parametros: parametros  */
#line 287 "parser/parser.y"
               { (yyval.no) = (yyvsp[0].no); }
#line 1493 "parser.tab.c"
    break;

  case 25: /* parametros: IDENTIFIER  */
#line 291 "parser/parser.y"
               {
        if (!inserirSimbolo((yyvsp[0].texto), TIPO_DESCONHECIDO))
            erroSemantico("parametro '%s' repetido", (yyvsp[0].texto));
        (yyval.no) = NULL;
        adicionarComando(&(yyval.no), criarNoId((yyvsp[0].texto)));
        free((yyvsp[0].texto));
    }
#line 1505 "parser.tab.c"
    break;

  case 26: /* parametros: parametros COMMA IDENTIFIER  */
#line 298 "parser/parser.y"
                                {
        if (!inserirSimbolo((yyvsp[0].texto), TIPO_DESCONHECIDO))
            erroSemantico("parametro '%s' repetido", (yyvsp[0].texto));
        (yyval.no) = (yyvsp[-2].no);
        adicionarComando(&(yyval.no), criarNoId((yyvsp[0].texto)));
        free((yyvsp[0].texto));
    }
#line 1517 "parser.tab.c"
    break;

  case 27: /* lista_argumentos: %empty  */
#line 308 "parser/parser.y"
                { (yyval.no) = NULL; }
#line 1523 "parser.tab.c"
    break;

  case 28: /* lista_argumentos: argumentos  */
#line 309 "parser/parser.y"
               { (yyval.no) = (yyvsp[0].no); }
#line 1529 "parser.tab.c"
    break;

  case 29: /* argumentos: expressao  */
#line 313 "parser/parser.y"
              {
        (yyval.no) = NULL;
        adicionarComando(&(yyval.no), (yyvsp[0].expr).no);
    }
#line 1538 "parser.tab.c"
    break;

  case 30: /* argumentos: argumentos COMMA expressao  */
#line 317 "parser/parser.y"
                               {
        (yyval.no) = (yyvsp[-2].no);
        adicionarComando(&(yyval.no), (yyvsp[0].expr).no);
    }
#line 1547 "parser.tab.c"
    break;

  case 31: /* expressao: NUMBER  */
#line 324 "parser/parser.y"
            { (yyval.expr) = novaExpr(criarNoNum((yyvsp[0].inteiro)), TIPO_INTEIRO); }
#line 1553 "parser.tab.c"
    break;

  case 32: /* expressao: FLOAT  */
#line 325 "parser/parser.y"
            { (yyval.expr) = novaExpr(criarNoFloat((yyvsp[0].real)), TIPO_FLOAT); }
#line 1559 "parser.tab.c"
    break;

  case 33: /* expressao: STRING  */
#line 326 "parser/parser.y"
            {
        (yyval.expr) = novaExpr(criarNoString((yyvsp[0].texto)), TIPO_STRING);
        free((yyvsp[0].texto));
    }
#line 1568 "parser.tab.c"
    break;

  case 34: /* expressao: BOOLEAN  */
#line 330 "parser/parser.y"
            { (yyval.expr) = novaExpr(criarNoBool((yyvsp[0].inteiro)), TIPO_BOOLEAN); }
#line 1574 "parser.tab.c"
    break;

  case 35: /* expressao: IDENTIFIER  */
#line 331 "parser/parser.y"
               {
        Simbolo *s = buscarSimbolo((yyvsp[0].texto));
        TipoDado t = TIPO_DESCONHECIDO;
        if (s == NULL)
            erroSemantico("variavel '%s' usada antes de ser definida", (yyvsp[0].texto));
        else if (s->tipo == TIPO_FUNCAO)
            erroSemantico("funcao '%s' usada sem chamada", (yyvsp[0].texto));
        else
            t = s->tipo;
        (yyval.expr) = novaExpr(criarNoId((yyvsp[0].texto)), t);
        free((yyvsp[0].texto));
    }
#line 1591 "parser.tab.c"
    break;

  case 36: /* expressao: IDENTIFIER LPAREN lista_argumentos RPAREN  */
#line 343 "parser/parser.y"
                                              {
        (yyval.expr) = novaExpr(montarChamada((yyvsp[-3].texto), (yyvsp[-1].no)), TIPO_INTEIRO);
    }
#line 1599 "parser.tab.c"
    break;

  case 37: /* expressao: expressao PLUS expressao  */
#line 346 "parser/parser.y"
                               { (yyval.expr) = novaExpr(criarNoOp('+', (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoAritmetico('+', (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1605 "parser.tab.c"
    break;

  case 38: /* expressao: expressao MINUS expressao  */
#line 347 "parser/parser.y"
                               { (yyval.expr) = novaExpr(criarNoOp('-', (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoAritmetico('-', (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1611 "parser.tab.c"
    break;

  case 39: /* expressao: expressao TIMES expressao  */
#line 348 "parser/parser.y"
                               { (yyval.expr) = novaExpr(criarNoOp('*', (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoAritmetico('*', (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1617 "parser.tab.c"
    break;

  case 40: /* expressao: expressao DIVIDE expressao  */
#line 349 "parser/parser.y"
                               { (yyval.expr) = novaExpr(criarNoOp('/', (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoAritmetico('/', (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1623 "parser.tab.c"
    break;

  case 41: /* expressao: expressao EQ expressao  */
#line 350 "parser/parser.y"
                           { (yyval.expr) = novaExpr(criarNoComp("==", (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoComparacao("==", (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1629 "parser.tab.c"
    break;

  case 42: /* expressao: expressao NEQ expressao  */
#line 351 "parser/parser.y"
                            { (yyval.expr) = novaExpr(criarNoComp("!=", (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoComparacao("!=", (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1635 "parser.tab.c"
    break;

  case 43: /* expressao: expressao LT expressao  */
#line 352 "parser/parser.y"
                           { (yyval.expr) = novaExpr(criarNoComp("<", (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoComparacao("<", (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1641 "parser.tab.c"
    break;

  case 44: /* expressao: expressao GT expressao  */
#line 353 "parser/parser.y"
                           { (yyval.expr) = novaExpr(criarNoComp(">", (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoComparacao(">", (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1647 "parser.tab.c"
    break;

  case 45: /* expressao: expressao LEQ expressao  */
#line 354 "parser/parser.y"
                            { (yyval.expr) = novaExpr(criarNoComp("<=", (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoComparacao("<=", (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1653 "parser.tab.c"
    break;

  case 46: /* expressao: expressao GEQ expressao  */
#line 355 "parser/parser.y"
                            { (yyval.expr) = novaExpr(criarNoComp(">=", (yyvsp[-2].expr).no, (yyvsp[0].expr).no), tipoComparacao(">=", (yyvsp[-2].expr).tipo, (yyvsp[0].expr).tipo)); }
#line 1659 "parser.tab.c"
    break;

  case 47: /* expressao: LPAREN expressao RPAREN  */
#line 356 "parser/parser.y"
                            { (yyval.expr) = (yyvsp[-1].expr); }
#line 1665 "parser.tab.c"
    break;


#line 1669 "parser.tab.c"

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

#line 359 "parser/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Erro sintatico na linha %d: %s\n", yylineno, s);
}

int main(int argc, char **argv) {
    inicializarTabela();

    if (argc >= 2) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            fprintf(stderr, "Erro: nao foi possivel abrir %s\n", argv[1]);
            return 1;
        }
    }
    if (argc >= 3) {
        strncpy(arquivo_saida, argv[2], sizeof(arquivo_saida) - 1);
        arquivo_saida[sizeof(arquivo_saida) - 1] = '\0';
    }

    int resultado = yyparse();

    if (argc >= 2 && yyin)
        fclose(yyin);

    if (resultado == 0 && erros_semanticos == 0)
        imprimirTabela();

    liberarTabela();

    if (resultado != 0) return resultado;
    return erros_semanticos ? 1 : 0;
}
