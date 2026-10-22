#ifndef TIPOS_H
#define TIPOS_H

typedef enum {
    AST_NUM,
    AST_STRING,
    AST_ID,
    AST_OP,
    AST_ATRIB,
    AST_PRINT,
    AST_LISTA_CMD,
    AST_PROGRAMA,
    AST_WHILE
} ASTTipo;

typedef struct noAST {
    ASTTipo tipo;
    int valor;
    char texto[256];
    char nome[50];
    char operador;
    struct noAST *esquerda;
    struct noAST *direita;
    struct noAST *proximo;
} NoAST;

#endif
