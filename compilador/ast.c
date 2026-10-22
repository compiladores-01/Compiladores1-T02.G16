#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static NoAST *criarNo(ASTTipo tipo) {
    NoAST *no = calloc(1, sizeof(*no));
    if (no) no->tipo = tipo;
    return no;
}

static void copiarTexto(char *destino, size_t tamanho, const char *origem) {
    if (!origem || tamanho == 0) return;
    strncpy(destino, origem, tamanho - 1);
}

NoAST *criarNoNum(int valor) {
    NoAST *no = criarNo(AST_NUM);
    if (no) no->valor = valor;
    return no;
}

NoAST *criarNoString(const char *texto) {
    NoAST *no = criarNo(AST_STRING);
    if (no) copiarTexto(no->texto, sizeof(no->texto), texto);
    return no;
}

NoAST *criarNoId(const char *nome) {
    NoAST *no = criarNo(AST_ID);
    if (no) copiarTexto(no->nome, sizeof(no->nome), nome);
    return no;
}

NoAST *criarNoOp(char operador, NoAST *esquerda, NoAST *direita) {
    NoAST *no = criarNo(AST_OP);
    if (no) {
        no->operador = operador;
        no->esquerda = esquerda;
        no->direita = direita;
    }
    return no;
}

NoAST *criarNoAtrib(NoAST *id, NoAST *expressao) {
    NoAST *no = criarNo(AST_ATRIB);
    if (no) {
        no->esquerda = id;
        no->direita = expressao;
    }
    return no;
}

NoAST *criarNoPrint(NoAST *expressao) {
    NoAST *no = criarNo(AST_PRINT);
    if (no) no->esquerda = expressao;
    return no;
}

NoAST *criarNoListaCmd(NoAST *comando) {
    NoAST *no = criarNo(AST_LISTA_CMD);
    if (no) no->esquerda = comando;
    return no;
}

NoAST *criarNoPrograma(NoAST *comandos) {
    NoAST *no = criarNo(AST_PROGRAMA);
    if (no) no->esquerda = comandos;
    return no;
}

static void imprimirLista(const NoAST *no) {
    for (; no; no = no->proximo) {
        if (no->esquerda) {
            imprimirAST(no->esquerda);
            printf("\n");
        }
    }
}

void imprimirAST(const NoAST *raiz) {
    if (!raiz) return;

    switch (raiz->tipo) {
        case AST_NUM:
            printf("%d", raiz->valor);
            break;
        case AST_STRING:
            printf("%s", raiz->texto);
            break;
        case AST_ID:
            printf("%s", raiz->nome);
            break;
        case AST_OP:
            printf("(");
            imprimirAST(raiz->esquerda);
            printf(" %c ", raiz->operador);
            imprimirAST(raiz->direita);
            printf(")");
            break;
        case AST_ATRIB:
            imprimirAST(raiz->esquerda);
            printf(" = ");
            imprimirAST(raiz->direita);
            break;
        case AST_PRINT:
            printf("print(");
            imprimirAST(raiz->esquerda);
            printf(")");
            break;
        case AST_LISTA_CMD:
            imprimirLista(raiz);
            break;
        case AST_PROGRAMA:
            imprimirLista(raiz->esquerda);
            break;
    }
}

void liberarAST(NoAST *raiz) {
    if (!raiz) return;
    liberarAST(raiz->esquerda);
    liberarAST(raiz->direita);
    liberarAST(raiz->proximo);
    free(raiz);
}
