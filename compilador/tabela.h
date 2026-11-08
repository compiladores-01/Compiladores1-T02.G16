#ifndef TABELA_H
#define TABELA_H

#include "tipos.h"

#define TAMANHO_TABELA 100

typedef struct {
    char *nome;
    TipoDado tipo;
    int escopo;
} Simbolo;

void inicializarTabela(void);
void entrarEscopo(void);
void sairEscopo(void);
int inserirSimbolo(const char *nome, TipoDado tipo);
Simbolo *buscarSimbolo(const char *nome);
void imprimirTabela(void);
void liberarTabela(void);

#endif
