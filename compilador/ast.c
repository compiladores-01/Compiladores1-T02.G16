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
    destino[tamanho - 1] = '\0';
}

NoAST *criarNoNum(int valor) {
    NoAST *no = criarNo(AST_NUM);
    if (no) no->valor = valor;
    return no;
}

NoAST *criarNoFloat(double valor) {
    NoAST *no = criarNo(AST_FLOAT);
    if (no) no->valorFloat = valor;
    return no;
}

NoAST *criarNoBool(int valor) {
    NoAST *no = criarNo(AST_BOOL);
    if (no) no->valor = valor ? 1 : 0;
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

NoAST *criarNoComp(const char *comparador, NoAST *esquerda, NoAST *direita) {
    NoAST *no = criarNo(AST_COMP);
    if (no) {
        copiarTexto(no->comparador, sizeof(no->comparador), comparador);
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

NoAST *criarNoIf(NoAST *condicao, NoAST *corpo, NoAST *alternativo) {
    NoAST *no = criarNo(AST_IF);
    if (no) {
        no->esquerda = condicao;
        no->direita = corpo;
        no->alternativo = alternativo;
    }
    return no;
}

NoAST *criarNoWhile(NoAST *condicao, NoAST *corpo) {
    NoAST *no = criarNo(AST_WHILE);
    if (no) {
        no->esquerda = condicao;
        no->direita = corpo;
    }
    return no;
}

NoAST *criarNoFunc(const char *nome, NoAST *params, NoAST *corpo) {
    NoAST *no = criarNo(AST_FUNC);
    if (no) {
        copiarTexto(no->nome, sizeof(no->nome), nome);
        no->esquerda = params;
        no->direita = corpo;
    }
    return no;
}

NoAST *criarNoReturn(NoAST *expressao) {
    NoAST *no = criarNo(AST_RETURN);
    if (no) no->esquerda = expressao;
    return no;
}

NoAST *criarNoChamada(const char *nome, NoAST *args) {
    NoAST *no = criarNo(AST_CHAMADA);
    if (no) {
        copiarTexto(no->nome, sizeof(no->nome), nome);
        no->esquerda = args;
    }
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

static void imprimirLista(const NoAST *no);

void imprimirAST(const NoAST *raiz) {
    if (!raiz) return;

    switch (raiz->tipo) {
        case AST_NUM:
            printf("%d", raiz->valor);
            break;
        case AST_FLOAT:
            printf("%g", raiz->valorFloat);
            break;
        case AST_BOOL:
            printf("%s", raiz->valor ? "True" : "False");
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
        case AST_COMP:
            printf("(");
            imprimirAST(raiz->esquerda);
            printf(" %s ", raiz->comparador);
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
        case AST_IF:
            printf("if ");
            imprimirAST(raiz->esquerda);
            printf(":\n");
            imprimirLista(raiz->direita);
            if (raiz->alternativo) {
                printf("else:\n");
                imprimirLista(raiz->alternativo);
            }
            break;
        case AST_WHILE:
            printf("while ");
            imprimirAST(raiz->esquerda);
            printf(":\n");
            imprimirLista(raiz->direita);
            break;
        case AST_FUNC:
            printf("def %s(", raiz->nome);
            {
                int primeiro = 1;
                for (const NoAST *p = raiz->esquerda; p; p = p->proximo) {
                    if (!p->esquerda) continue;
                    if (!primeiro) printf(", ");
                    imprimirAST(p->esquerda);
                    primeiro = 0;
                }
            }
            printf("):\n");
            imprimirLista(raiz->direita);
            break;
        case AST_RETURN:
            printf("return");
            if (raiz->esquerda) {
                printf(" ");
                imprimirAST(raiz->esquerda);
            }
            break;
        case AST_CHAMADA:
            printf("%s(", raiz->nome);
            {
                int primeiro = 1;
                for (const NoAST *a = raiz->esquerda; a; a = a->proximo) {
                    if (!a->esquerda) continue;
                    if (!primeiro) printf(", ");
                    imprimirAST(a->esquerda);
                    primeiro = 0;
                }
            }
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

static void imprimirLista(const NoAST *no) {
    for (; no; no = no->proximo) {
        if (no->esquerda) {
            imprimirAST(no->esquerda);
            printf("\n");
        }
    }
}

void liberarAST(NoAST *raiz) {
    if (!raiz) return;
    liberarAST(raiz->esquerda);
    liberarAST(raiz->direita);
    liberarAST(raiz->alternativo);
    liberarAST(raiz->proximo);
    free(raiz);
}
