%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "ast.h"
#include "tipos.h"
#include "tabela.h"
%}

%code requires {
#include "ast.h"
#include "tipos.h"

/* Valor semantico de uma expressao: no da AST + tipo inferido. */
typedef struct {
    NoAST *no;
    TipoDado tipo;
} Expr;
}

%union {
    int inteiro;
    double real;
    char *texto;
    NoAST *no;
    Expr expr;
}

%code {
int yylex(void);
void yyerror(const char *s);

int erros_semanticos = 0;

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

    if (s->tipo == t || t == TIPO_DESCONHECIDO)
        return;

    if (s->tipo == TIPO_FLOAT && t == TIPO_INTEIRO)   /* int -> float */
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
}

%token <texto> IDENTIFIER STRING
%token <inteiro> NUMBER BOOLEAN
%token <real> FLOAT
%token PRINT IF ELSE WHILE COLON NEWLINE
%token LPAREN RPAREN LBRACE RBRACE
%token PLUS MINUS TIMES DIVIDE
%token EQ NEQ LEQ GEQ LT GT ATRIBUES

%type <no> command_list command variable print_stmt
%type <no> if_stmt while_stmt block
%type <expr> expr

%left EQ NEQ LT GT LEQ GEQ
%left PLUS MINUS
%left TIMES DIVIDE

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program:
    command_list {
        if (erros_semanticos == 0) {
            NoAST *raiz = criarNoPrograma($1);
            imprimirAST(raiz);
            liberarAST(raiz);
        } else {
            liberarAST($1);
        }
    }
;

command_list:
    command {
        $$ = NULL;
        adicionarComando(&$$, $1);
    }
  | command_list command {
        $$ = $1;
        adicionarComando(&$$, $2);
    }
;

command:
    variable NEWLINE { $$ = $1; }
  | print_stmt NEWLINE { $$ = $1; }
  | if_stmt { $$ = $1; }
  | while_stmt { $$ = $1; }
  | NEWLINE { $$ = NULL; }
;

variable:
    IDENTIFIER ATRIBUES expr {
        atribuir($1, $3.tipo);
        $$ = criarNoAtrib(criarNoId($1), $3.no);
        free($1);
    }
;

print_stmt:
    PRINT LPAREN expr RPAREN { $$ = criarNoPrint($3.no); }
;

if_stmt:
    IF LPAREN expr RPAREN block %prec LOWER_THAN_ELSE {
        verificarCondicao("if", $3.tipo);
        liberarAST($3.no);
        $$ = NULL;
    }
  | IF LPAREN expr RPAREN block ELSE block {
        verificarCondicao("if", $3.tipo);
        liberarAST($3.no);
        $$ = NULL;
    }
;

while_stmt:
    WHILE LPAREN expr RPAREN block {
        verificarCondicao("while", $3.tipo);
        liberarAST($3.no);
        liberarAST($5);
        $$ = NULL;
    }
;

block:
    LBRACE command_list RBRACE {
        liberarAST($2);
        $$ = NULL;
    }
;

expr:
    NUMBER  { $$ = novaExpr(criarNoNum($1), TIPO_INTEIRO); }
  | FLOAT   { $$ = novaExpr(criarNoFloat($1), TIPO_FLOAT); }
  | STRING  {
        $$ = novaExpr(criarNoString($1), TIPO_STRING);
        free($1);
    }
  | BOOLEAN { $$ = novaExpr(criarNoBool($1), TIPO_BOOLEAN); }
  | IDENTIFIER {
        Simbolo *s = buscarSimbolo($1);
        TipoDado t = TIPO_DESCONHECIDO;
        if (s == NULL)
            erroSemantico("variavel '%s' usada antes de ser definida", $1);
        else
            t = s->tipo;
        $$ = novaExpr(criarNoId($1), t);
        free($1);
    }
  | expr PLUS expr   { $$ = novaExpr(criarNoOp('+', $1.no, $3.no), tipoAritmetico('+', $1.tipo, $3.tipo)); }
  | expr MINUS expr  { $$ = novaExpr(criarNoOp('-', $1.no, $3.no), tipoAritmetico('-', $1.tipo, $3.tipo)); }
  | expr TIMES expr  { $$ = novaExpr(criarNoOp('*', $1.no, $3.no), tipoAritmetico('*', $1.tipo, $3.tipo)); }
  | expr DIVIDE expr { $$ = novaExpr(criarNoOp('/', $1.no, $3.no), tipoAritmetico('/', $1.tipo, $3.tipo)); }
  | expr EQ expr { $$ = novaExpr(criarNoComp("==", $1.no, $3.no), tipoComparacao("==", $1.tipo, $3.tipo)); }
  | expr NEQ expr { $$ = novaExpr(criarNoComp("!=", $1.no, $3.no), tipoComparacao("!=", $1.tipo, $3.tipo)); }
  | expr LT expr { $$ = novaExpr(criarNoComp("<", $1.no, $3.no), tipoComparacao("<", $1.tipo, $3.tipo)); }
  | expr GT expr { $$ = novaExpr(criarNoComp(">", $1.no, $3.no), tipoComparacao(">", $1.tipo, $3.tipo)); }
  | expr LEQ expr { $$ = novaExpr(criarNoComp("<=", $1.no, $3.no), tipoComparacao("<=", $1.tipo, $3.tipo)); }
  | expr GEQ expr { $$ = novaExpr(criarNoComp(">=", $1.no, $3.no), tipoComparacao(">=", $1.tipo, $3.tipo)); }
  | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintatico: %s\n", s);
}

int main(void) {
    inicializarTabela();

    int resultado = yyparse();

    if (resultado == 0 && erros_semanticos == 0)
        imprimirTabela();

    liberarTabela();

    if (resultado != 0) return resultado;
    return erros_semanticos ? 1 : 0;
}
