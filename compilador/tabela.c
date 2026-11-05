#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabela.h"

static Simbolo tabela[TAMANHO_TABELA];

static int quantidadeSimbolos = 0;


void inicializarTabela(void) {
    quantidadeSimbolos = 0;
}


Simbolo *buscarSimbolo(const char *nome) {

    for (int i = 0; i < quantidadeSimbolos; i++) {

        if (strcmp(tabela[i].nome, nome) == 0) {
            return &tabela[i];
        }

    }

    return NULL;
}


int inserirSimbolo(const char *nome, TipoDado tipo) {

    if (buscarSimbolo(nome) != NULL) {
        return 0;
    }

    if (quantidadeSimbolos >= TAMANHO_TABELA) {
        printf("Erro: tabela de simbolos cheia.\n");
        return 0;
    }

    tabela[quantidadeSimbolos].nome = malloc(strlen(nome) + 1);

    if (tabela[quantidadeSimbolos].nome == NULL) {
        return 0;
    }

    strcpy(tabela[quantidadeSimbolos].nome, nome);

    tabela[quantidadeSimbolos].tipo = tipo;

    quantidadeSimbolos++;

    return 1;
}


void imprimirTabela(void) {

    printf("TABELA DE SIMBOLOS\n");
    

    if (quantidadeSimbolos == 0) {
        printf("Tabela vazia.\n");
    }

    for (int i = 0; i < quantidadeSimbolos; i++) {

        printf("%-15s | ", tabela[i].nome);

        switch (tabela[i].tipo) {

            case TIPO_INTEIRO:
                printf("INTEIRO");
                break;

            case TIPO_FLOAT:
                printf("FLOAT");
                break;

            case TIPO_STRING:
                printf("STRING");
                break;

            case TIPO_BOOLEAN:
                printf("BOOLEAN");
                break;

            default:
                printf("DESCONHECIDO");
                break;
        }

        printf("\n");
    }

    printf("-----\n");
}


void liberarTabela(void) {

    for (int i = 0; i < quantidadeSimbolos; i++) {

        free(tabela[i].nome);

        tabela[i].nome = NULL;
    }

    quantidadeSimbolos = 0;
}