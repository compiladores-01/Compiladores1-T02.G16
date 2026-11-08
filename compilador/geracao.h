#ifndef GERACAO_H
#define GERACAO_H

#include "ast.h"

int gerarCodigoC(const NoAST *raiz, const char *arquivo);

#endif
