%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *s);

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
%}

%code requires {
#include "ast.h"
}

%union {
    int inteiro;
    char *texto;
    NoAST *no;
}

%token <texto> IDENTIFIER STRING
%token <inteiro> NUMBER
%token FLOAT BOOLEAN
%token PRINT IF ELSE WHILE COLON NEWLINE
%token LPAREN RPAREN LBRACE RBRACE
%token PLUS MINUS TIMES DIVIDE
%token EQ NEQ LEQ GEQ LT GT ATRIBUES

%type <no> command_list command variable print_stmt
%type <no> if_stmt while_stmt block expr

%left EQ NEQ LT GT LEQ GEQ
%left PLUS MINUS
%left TIMES DIVIDE

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program:
    command_list {
        NoAST *raiz = criarNoPrograma($1);
        imprimirAST(raiz);
        liberarAST(raiz);
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
        $$ = criarNoAtrib(criarNoId($1), $3);
        free($1);
    }
;

print_stmt:
    PRINT LPAREN expr RPAREN { $$ = criarNoPrint($3); }
;

if_stmt:
    IF expr COLON NEWLINE block %prec LOWER_THAN_ELSE {
        liberarAST($2);
        $$ = NULL;
    }
  | IF expr COLON NEWLINE block ELSE COLON NEWLINE block {
        liberarAST($2);
        $$ = NULL;
    }
;

while_stmt:
    WHILE expr LBRACE command_list RBRACE {
        $$ = criarNoWhile($2, $4);
    }
;

block:
    LBRACE command_list RBRACE {
        liberarAST($2);
        $$ = NULL;
    }
;

expr:
    NUMBER { $$ = criarNoNum($1); }
  | FLOAT { $$ = NULL; }
  | STRING {
        $$ = criarNoString($1);
        free($1);
    }
  | BOOLEAN { $$ = NULL; }
  | IDENTIFIER {
        $$ = criarNoId($1);
        free($1);
    }
  | expr PLUS expr { $$ = criarNoOp('+', $1, $3); }
  | expr MINUS expr { $$ = criarNoOp('-', $1, $3); }
  | expr TIMES expr { $$ = criarNoOp('*', $1, $3); }
  | expr DIVIDE expr { $$ = criarNoOp('/', $1, $3); }
  | expr EQ expr { $$ = criarNoOp('=', $1, $3); }
  | expr NEQ expr { $$ = criarNoOp('!', $1, $3); }
  | expr LT expr { $$ = criarNoOp('<', $1, $3); }
  | expr GT expr { $$ = criarNoOp('>', $1, $3); }
  | expr LEQ expr { $$ = criarNoOp('L', $1, $3); }
  | expr GEQ expr { $$ = criarNoOp('G', $1, $3); }
  | LPAREN expr RPAREN { $$ = $2; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

int main(void) {
    return yyparse();
}
