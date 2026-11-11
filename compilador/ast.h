#ifndef AST_H
#define AST_H

#include "tipos.h"

typedef enum {
    AST_NUM,
    AST_FLOAT,
    AST_BOOL,
    AST_STRING,
    AST_ID,
    AST_OP,
    AST_COMP,
    AST_ATRIB,
    AST_PRINT,
    AST_LISTA_CMD,
    AST_PROGRAMA,
    AST_IF,
    AST_WHILE,
    AST_FUNC,
    AST_RETURN,
    AST_CHAMADA
} ASTTipo;

typedef struct NoAST {
    ASTTipo tipo;
    int valor;
    double valorFloat;
    char texto[256];
    char nome[64];
    char operador;
    char comparador[3];
    struct NoAST *esquerda;
    struct NoAST *direita;
    struct NoAST *alternativo;
    struct NoAST *proximo;
} NoAST;

NoAST *criarNoNum(int valor);
NoAST *criarNoFloat(double valor);
NoAST *criarNoBool(int valor);
NoAST *criarNoString(const char *texto);
NoAST *criarNoId(const char *nome);
NoAST *criarNoOp(char operador, NoAST *esquerda, NoAST *direita);
NoAST *criarNoComp(const char *comparador, NoAST *esquerda, NoAST *direita);
NoAST *criarNoAtrib(NoAST *id, NoAST *expressao);
NoAST *criarNoPrint(NoAST *expressao);
NoAST *criarNoIf(NoAST *condicao, NoAST *corpo, NoAST *alternativo);
NoAST *criarNoWhile(NoAST *condicao, NoAST *corpo);
NoAST *criarNoFunc(const char *nome, NoAST *params, NoAST *corpo);
NoAST *criarNoReturn(NoAST *expressao);
NoAST *criarNoChamada(const char *nome, NoAST *args);
NoAST *criarNoListaCmd(NoAST *comando);
NoAST *criarNoPrograma(NoAST *comandos);
void imprimirAST(const NoAST *raiz);
void liberarAST(NoAST *raiz);

#endif
