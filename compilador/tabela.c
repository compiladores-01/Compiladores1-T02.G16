#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabela.h"

static Simbolo tabela[TAMANHO_TABELA];
static int quantidadeSimbolos = 0;
static int escopoAtual = 0;

void inicializarTabela(void) {
    quantidadeSimbolos = 0;
    escopoAtual = 0;
}

void entrarEscopo(void) {
    escopoAtual++;
}

void sairEscopo(void) {
    while (quantidadeSimbolos > 0 && tabela[quantidadeSimbolos - 1].escopo == escopoAtual) {
        quantidadeSimbolos--;
        free(tabela[quantidadeSimbolos].nome);
        tabela[quantidadeSimbolos].nome = NULL;
    }
    if (escopoAtual > 0)
        escopoAtual--;
}

Simbolo *buscarSimbolo(const char *nome) {
    for (int i = quantidadeSimbolos - 1; i >= 0; i--) {
        if (strcmp(tabela[i].nome, nome) == 0)
            return &tabela[i];
    }
    return NULL;
}

int inserirSimbolo(const char *nome, TipoDado tipo) {
    for (int i = 0; i < quantidadeSimbolos; i++) {
        if (tabela[i].escopo == escopoAtual && strcmp(tabela[i].nome, nome) == 0)
            return 0;
    }

    if (quantidadeSimbolos >= TAMANHO_TABELA) {
        fprintf(stderr, "Erro: tabela de simbolos cheia.\n");
        return 0;
    }

    tabela[quantidadeSimbolos].nome = malloc(strlen(nome) + 1);
    if (tabela[quantidadeSimbolos].nome == NULL)
        return 0;

    strcpy(tabela[quantidadeSimbolos].nome, nome);
    tabela[quantidadeSimbolos].tipo = tipo;
    tabela[quantidadeSimbolos].escopo = escopoAtual;
    quantidadeSimbolos++;
    return 1;
}

void imprimirTabela(void) {
    printf("TABELA DE SIMBOLOS\n");

    if (quantidadeSimbolos == 0)
        printf("Tabela vazia.\n");

    for (int i = 0; i < quantidadeSimbolos; i++) {
        printf("%-15s | ", tabela[i].nome);
        switch (tabela[i].tipo) {
            case TIPO_INTEIRO:     printf("INTEIRO"); break;
            case TIPO_FLOAT:       printf("FLOAT"); break;
            case TIPO_STRING:      printf("STRING"); break;
            case TIPO_BOOLEAN:     printf("BOOLEAN"); break;
            case TIPO_FUNCAO:      printf("FUNCAO"); break;
            default:               printf("DESCONHECIDO"); break;
        }
        printf(" | escopo %d\n", tabela[i].escopo);
    }

    printf("-----\n");
}

void liberarTabela(void) {
    for (int i = 0; i < quantidadeSimbolos; i++) {
        free(tabela[i].nome);
        tabela[i].nome = NULL;
    }
    quantidadeSimbolos = 0;
    escopoAtual = 0;
}
