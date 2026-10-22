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

NoAST *criarNoWhile(NoAST *condicao, NoAST *comandos) {
    NoAST *no = criarNo(AST_WHILE);
    if (no) { no->esquerda = condicao; no->direita = comandos; }
    return no;
}

static void imprimirNo(const NoAST *raiz, const char *prefixo, int ultimo) {
    if (!raiz) return;

    printf("%s%s", prefixo, ultimo ? "`-- " : "|-- ");

    switch (raiz->tipo) {
        case AST_NUM:
            printf("Numero: %d\n", raiz->valor);
            break;
        case AST_STRING:
            printf("String: \"%s\"\n", raiz->texto);
            break;
        case AST_ID:
            printf("Identificador: %s\n", raiz->nome);
            break;
        case AST_OP:
            printf("Operador: %c\n", raiz->operador);
            break;
        case AST_ATRIB:
            printf("Atribuicao\n");
            break;
        case AST_PRINT:
            printf("Print\n");
            break;
        case AST_LISTA_CMD:
            printf("Comando\n");
            break;
        case AST_PROGRAMA:
            printf("Programa\n");
            break;
        case AST_WHILE:
            printf("While\n");
            break;
    }

    char proximoPrefixo[256];
    snprintf(proximoPrefixo, sizeof(proximoPrefixo), "%s%s", prefixo,
             ultimo ? "    " : "|   ");

    const NoAST *filhos[2] = {raiz->esquerda, raiz->direita};
    int quantidade = filhos[1] ? 2 : filhos[0] ? 1 : 0;
    for (int i = 0; i < quantidade; i++)
        imprimirNo(filhos[i], proximoPrefixo, i == quantidade - 1);

    for (const NoAST *item = raiz->proximo; item; item = item->proximo)
        imprimirNo(item, prefixo, item->proximo == NULL);
}

void imprimirAST(const NoAST *raiz) {
    if (!raiz) return;
    printf("Programa\n");
    const NoAST *comando = raiz->esquerda;
    for (const NoAST *item = comando; item; item = item->proximo) {
        if (item->esquerda)
            imprimirNo(item->esquerda, "", item->proximo == NULL);
    }
}

void liberarAST(NoAST *raiz) {
    if (!raiz) return;
    liberarAST(raiz->esquerda);
    liberarAST(raiz->direita);
    liberarAST(raiz->proximo);
    free(raiz);
}
