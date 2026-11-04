#ifndef TABELA_H
#define TABELA_H

#include "tipos.h"

#define TAMANHO_TABELA 100

typedef struct {
    char *nome;
    TipoDado tipo;
} Simbolo;

void inicializarTabela(void);

int inserirSimbolo(const char *nome, TipoDado tipo);

Simbolo *buscarSimbolo(const char *nome);

void imprimirTabela(void);

void liberarTabela(void);

#endif