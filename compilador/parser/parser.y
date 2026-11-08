%{
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
}

%token <texto> IDENTIFIER STRING
%token <inteiro> NUMBER BOOLEAN
%token <real> FLOAT
%token PRINT IF ELSE WHILE DEF RETURN
%token COLON NEWLINE COMMA
%token INDENT DEDENT
%token LPAREN RPAREN
%token PLUS MINUS TIMES DIVIDE
%token EQ NEQ LEQ GEQ LT GT ATRIBUES

%type <no> lista_comandos comando atribuicao comando_print
%type <no> comando_if comando_while bloco
%type <no> definicao_funcao comando_return
%type <no> lista_parametros parametros lista_argumentos argumentos
%type <expr> expressao

%left EQ NEQ LT GT LEQ GEQ
%left PLUS MINUS
%left TIMES DIVIDE

%nonassoc MENOR_QUE_ELSE
%nonassoc ELSE

%%

programa:
    lista_comandos {
        if (erros_semanticos == 0) {
            NoAST *raiz = criarNoPrograma($1);
            imprimirAST(raiz);
            if (gerarCodigoC(raiz, arquivo_saida) != 0)
                erros_semanticos++;
            liberarAST(raiz);
        } else {
            liberarAST($1);
        }
    }
;

lista_comandos:
    comando {
        $$ = NULL;
        adicionarComando(&$$, $1);
    }
  | lista_comandos comando {
        $$ = $1;
        adicionarComando(&$$, $2);
    }
;

comando:
    atribuicao NEWLINE { $$ = $1; }
  | comando_print NEWLINE { $$ = $1; }
  | comando_return NEWLINE { $$ = $1; }
  | IDENTIFIER LPAREN lista_argumentos RPAREN NEWLINE {
        $$ = montarChamada($1, $3);
    }
  | comando_if { $$ = $1; }
  | comando_while { $$ = $1; }
  | definicao_funcao { $$ = $1; }
  | NEWLINE { $$ = NULL; }
;

atribuicao:
    IDENTIFIER ATRIBUES expressao {
        atribuir($1, $3.tipo);
        $$ = criarNoAtrib(criarNoId($1), $3.no);
        free($1);
    }
;

comando_print:
    PRINT LPAREN expressao RPAREN { $$ = criarNoPrint($3.no); }
;

comando_return:
    RETURN expressao {
        if (nivel_funcao == 0)
            erroSemantico("'return' fora de funcao");
        $$ = criarNoReturn($2.no);
    }
  | RETURN {
        if (nivel_funcao == 0)
            erroSemantico("'return' fora de funcao");
        $$ = criarNoReturn(NULL);
    }
;

comando_if:
    IF expressao COLON bloco %prec MENOR_QUE_ELSE {
        verificarCondicao("if", $2.tipo);
        $$ = criarNoIf($2.no, $4, NULL);
    }
  | IF expressao COLON bloco ELSE COLON bloco {
        verificarCondicao("if", $2.tipo);
        $$ = criarNoIf($2.no, $4, $7);
    }
;

comando_while:
    WHILE expressao COLON bloco {
        verificarCondicao("while", $2.tipo);
        $$ = criarNoWhile($2.no, $4);
    }
;

bloco:
    NEWLINE INDENT lista_comandos DEDENT { $$ = $3; }
;

definicao_funcao:
    DEF IDENTIFIER LPAREN {
        if (nivel_funcao > 0)
            erroSemantico("funcoes aninhadas nao sao suportadas");
        if (!inserirSimbolo($2, TIPO_FUNCAO))
            erroSemantico("nome '%s' ja foi declarado", $2);
        nivel_funcao++;
        entrarEscopo();
    }
    lista_parametros RPAREN COLON bloco {
        nivel_funcao--;
        $$ = criarNoFunc($2, $5, $8);
        sairEscopo();
        free($2);
    }
;

lista_parametros:
    /* vazio */ { $$ = NULL; }
  | parametros { $$ = $1; }
;

parametros:
    IDENTIFIER {
        if (!inserirSimbolo($1, TIPO_DESCONHECIDO))
            erroSemantico("parametro '%s' repetido", $1);
        $$ = NULL;
        adicionarComando(&$$, criarNoId($1));
        free($1);
    }
  | parametros COMMA IDENTIFIER {
        if (!inserirSimbolo($3, TIPO_DESCONHECIDO))
            erroSemantico("parametro '%s' repetido", $3);
        $$ = $1;
        adicionarComando(&$$, criarNoId($3));
        free($3);
    }
;

lista_argumentos:
    /* vazio */ { $$ = NULL; }
  | argumentos { $$ = $1; }
;

argumentos:
    expressao {
        $$ = NULL;
        adicionarComando(&$$, $1.no);
    }
  | argumentos COMMA expressao {
        $$ = $1;
        adicionarComando(&$$, $3.no);
    }
;

expressao:
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
        else if (s->tipo == TIPO_FUNCAO)
            erroSemantico("funcao '%s' usada sem chamada", $1);
        else
            t = s->tipo;
        $$ = novaExpr(criarNoId($1), t);
        free($1);
    }
  | IDENTIFIER LPAREN lista_argumentos RPAREN {
        $$ = novaExpr(montarChamada($1, $3), TIPO_INTEIRO);
    }
  | expressao PLUS expressao   { $$ = novaExpr(criarNoOp('+', $1.no, $3.no), tipoAritmetico('+', $1.tipo, $3.tipo)); }
  | expressao MINUS expressao  { $$ = novaExpr(criarNoOp('-', $1.no, $3.no), tipoAritmetico('-', $1.tipo, $3.tipo)); }
  | expressao TIMES expressao  { $$ = novaExpr(criarNoOp('*', $1.no, $3.no), tipoAritmetico('*', $1.tipo, $3.tipo)); }
  | expressao DIVIDE expressao { $$ = novaExpr(criarNoOp('/', $1.no, $3.no), tipoAritmetico('/', $1.tipo, $3.tipo)); }
  | expressao EQ expressao { $$ = novaExpr(criarNoComp("==", $1.no, $3.no), tipoComparacao("==", $1.tipo, $3.tipo)); }
  | expressao NEQ expressao { $$ = novaExpr(criarNoComp("!=", $1.no, $3.no), tipoComparacao("!=", $1.tipo, $3.tipo)); }
  | expressao LT expressao { $$ = novaExpr(criarNoComp("<", $1.no, $3.no), tipoComparacao("<", $1.tipo, $3.tipo)); }
  | expressao GT expressao { $$ = novaExpr(criarNoComp(">", $1.no, $3.no), tipoComparacao(">", $1.tipo, $3.tipo)); }
  | expressao LEQ expressao { $$ = novaExpr(criarNoComp("<=", $1.no, $3.no), tipoComparacao("<=", $1.tipo, $3.tipo)); }
  | expressao GEQ expressao { $$ = novaExpr(criarNoComp(">=", $1.no, $3.no), tipoComparacao(">=", $1.tipo, $3.tipo)); }
  | LPAREN expressao RPAREN { $$ = $2; }
;

%%

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
