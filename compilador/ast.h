#ifndef AST_H
#define AST_H

#include "tipos.h"

NoAST *criarNoNum(int valor);
NoAST *criarNoString(const char *texto);
NoAST *criarNoId(const char *nome);
NoAST *criarNoOp(char operador, NoAST *esquerda, NoAST *direita);
NoAST *criarNoAtrib(NoAST *id, NoAST *expressao);
NoAST *criarNoPrint(NoAST *expressao);
NoAST *criarNoListaCmd(NoAST *comando);
NoAST *criarNoPrograma(NoAST *comandos);
void imprimirAST(const NoAST *raiz);
void liberarAST(NoAST *raiz);

#endif
