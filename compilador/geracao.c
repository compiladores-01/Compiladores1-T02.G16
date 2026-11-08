#include "geracao.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARIAVEIS 128

typedef struct {
    char nome[64];
    TipoDado tipo;
} DeclaracaoVariavel;

static int usouConcatenacao = 0;

static TipoDado tipoDoNo(const NoAST *no);

static int mesmoNome(const char *a, const char *b) {
    return a && b && strcmp(a, b) == 0;
}

static int ehParametro(const NoAST *parametros, const char *nome) {
    for (const NoAST *p = parametros; p; p = p->proximo) {
        if (p->esquerda && p->esquerda->tipo == AST_ID && mesmoNome(p->esquerda->nome, nome))
            return 1;
    }
    return 0;
}

static void registrarVariavel(DeclaracaoVariavel *variaveis, int *quantidade,
                              const char *nome, TipoDado tipo, const NoAST *parametros) {
    if (!nome || nome[0] == '\0') return;
    if (parametros && ehParametro(parametros, nome)) return;
    for (int i = 0; i < *quantidade; i++) {
        if (mesmoNome(variaveis[i].nome, nome)) {
            if (variaveis[i].tipo == TIPO_DESCONHECIDO && tipo != TIPO_DESCONHECIDO)
                variaveis[i].tipo = tipo;
            return;
        }
    }
    if (*quantidade >= MAX_VARIAVEIS) return;
    strncpy(variaveis[*quantidade].nome, nome, sizeof(variaveis[*quantidade].nome) - 1);
    variaveis[*quantidade].nome[sizeof(variaveis[*quantidade].nome) - 1] = '\0';
    variaveis[*quantidade].tipo = (tipo == TIPO_DESCONHECIDO) ? TIPO_INTEIRO : tipo;
    (*quantidade)++;
}

static TipoDado tipoDoNo(const NoAST *no) {
    if (!no) return TIPO_DESCONHECIDO;
    switch (no->tipo) {
        case AST_NUM:     return TIPO_INTEIRO;
        case AST_FLOAT:   return TIPO_FLOAT;
        case AST_BOOL:    return TIPO_BOOLEAN;
        case AST_STRING:  return TIPO_STRING;
        case AST_COMP:    return TIPO_BOOLEAN;
        case AST_CHAMADA: return TIPO_INTEIRO;
        case AST_ID:      return TIPO_DESCONHECIDO;
        case AST_OP:
            if (no->operador == '/') return TIPO_FLOAT;
            if (no->operador == '+') {
                TipoDado esq = tipoDoNo(no->esquerda);
                TipoDado dir = tipoDoNo(no->direita);
                if (esq == TIPO_STRING || dir == TIPO_STRING) return TIPO_STRING;
                if (esq == TIPO_FLOAT || dir == TIPO_FLOAT) return TIPO_FLOAT;
            }
            {
                TipoDado esq = tipoDoNo(no->esquerda);
                TipoDado dir = tipoDoNo(no->direita);
                if (esq == TIPO_FLOAT || dir == TIPO_FLOAT) return TIPO_FLOAT;
            }
            return TIPO_INTEIRO;
        default:
            return TIPO_DESCONHECIDO;
    }
}

static void coletarVariaveis(const NoAST *no, DeclaracaoVariavel *variaveis, int *quantidade,
                             const NoAST *parametros) {
    if (!no) return;
    if (no->tipo == AST_ATRIB && no->esquerda && no->esquerda->tipo == AST_ID)
        registrarVariavel(variaveis, quantidade, no->esquerda->nome, tipoDoNo(no->direita), parametros);
    if (no->tipo == AST_FUNC) {
        coletarVariaveis(no->proximo, variaveis, quantidade, parametros);
        return;
    }
    coletarVariaveis(no->esquerda, variaveis, quantidade, parametros);
    coletarVariaveis(no->direita, variaveis, quantidade, parametros);
    coletarVariaveis(no->alternativo, variaveis, quantidade, parametros);
    coletarVariaveis(no->proximo, variaveis, quantidade, parametros);
}

static void coletarTipoRetorno(const NoAST *no, TipoDado *retorno) {
    if (!no) return;
    if (no->tipo == AST_RETURN && no->esquerda) {
        TipoDado t = tipoDoNo(no->esquerda);
        if (t == TIPO_FLOAT) *retorno = TIPO_FLOAT;
        else if (t == TIPO_STRING && *retorno != TIPO_FLOAT) *retorno = TIPO_STRING;
        else if (*retorno == TIPO_DESCONHECIDO) *retorno = t;
    }
    coletarTipoRetorno(no->esquerda, retorno);
    coletarTipoRetorno(no->direita, retorno);
    coletarTipoRetorno(no->alternativo, retorno);
    coletarTipoRetorno(no->proximo, retorno);
}

static const char *nomeTipoC(TipoDado t) {
    switch (t) {
        case TIPO_FLOAT:  return "double";
        case TIPO_STRING: return "const char *";
        default:          return "int";
    }
}

static void emitirIndentacao(FILE *saida, int nivel) {
    for (int i = 0; i < nivel; i++)
        fputs("    ", saida);
}

static void emitirExpressao(FILE *saida, const NoAST *no);
static void emitirListaComandos(FILE *saida, const NoAST *lista, int nivel);
static void emitirComando(FILE *saida, const NoAST *no, int nivel);

static void emitirArgumentos(FILE *saida, const NoAST *argumentos) {
    int primeiro = 1;
    for (const NoAST *a = argumentos; a; a = a->proximo) {
        if (!a->esquerda) continue;
        if (!primeiro) fputs(", ", saida);
        emitirExpressao(saida, a->esquerda);
        primeiro = 0;
    }
}

static void emitirExpressao(FILE *saida, const NoAST *no) {
    if (!no) {
        fputs("0", saida);
        return;
    }
    switch (no->tipo) {
        case AST_NUM:
            fprintf(saida, "%d", no->valor);
            break;
        case AST_FLOAT:
            fprintf(saida, "%g", no->valorFloat);
            break;
        case AST_BOOL:
            fprintf(saida, "%d", no->valor);
            break;
        case AST_STRING:
            fputs(no->texto, saida);
            break;
        case AST_ID:
            fputs(no->nome, saida);
            break;
        case AST_OP:
            if (no->operador == '+') {
                TipoDado esq = tipoDoNo(no->esquerda);
                TipoDado dir = tipoDoNo(no->direita);
                if (esq == TIPO_STRING || dir == TIPO_STRING) {
                    usouConcatenacao = 1;
                    fputs("concatenar(", saida);
                    emitirExpressao(saida, no->esquerda);
                    fputs(", ", saida);
                    emitirExpressao(saida, no->direita);
                    fputs(")", saida);
                    break;
                }
            }
            if (no->operador == '/') {
                fputs("((double)(", saida);
                emitirExpressao(saida, no->esquerda);
                fputs(") / (double)(", saida);
                emitirExpressao(saida, no->direita);
                fputs("))", saida);
                break;
            }
            fputs("(", saida);
            emitirExpressao(saida, no->esquerda);
            fprintf(saida, " %c ", no->operador);
            emitirExpressao(saida, no->direita);
            fputs(")", saida);
            break;
        case AST_COMP:
            fputs("(", saida);
            emitirExpressao(saida, no->esquerda);
            fprintf(saida, " %s ", no->comparador);
            emitirExpressao(saida, no->direita);
            fputs(")", saida);
            break;
        case AST_CHAMADA:
            fprintf(saida, "%s(", no->nome);
            emitirArgumentos(saida, no->esquerda);
            fputs(")", saida);
            break;
        default:
            fputs("0", saida);
            break;
    }
}

static void emitirImpressao(FILE *saida, const NoAST *expressao, int nivel) {
    TipoDado t = tipoDoNo(expressao);
    emitirIndentacao(saida, nivel);
    switch (t) {
        case TIPO_FLOAT:
            fputs("printf(\"%g\\n\", ", saida);
            emitirExpressao(saida, expressao);
            fputs(");\n", saida);
            break;
        case TIPO_STRING:
            fputs("printf(\"%s\\n\", ", saida);
            emitirExpressao(saida, expressao);
            fputs(");\n", saida);
            break;
        case TIPO_BOOLEAN:
            fputs("printf(\"%s\\n\", (", saida);
            emitirExpressao(saida, expressao);
            fputs(") ? \"True\" : \"False\");\n", saida);
            break;
        default:
            fputs("printf(\"%d\\n\", ", saida);
            emitirExpressao(saida, expressao);
            fputs(");\n", saida);
            break;
    }
}

static void emitirComando(FILE *saida, const NoAST *no, int nivel) {
    if (!no) return;
    switch (no->tipo) {
        case AST_ATRIB:
            emitirIndentacao(saida, nivel);
            emitirExpressao(saida, no->esquerda);
            fputs(" = ", saida);
            emitirExpressao(saida, no->direita);
            fputs(";\n", saida);
            break;
        case AST_PRINT:
            emitirImpressao(saida, no->esquerda, nivel);
            break;
        case AST_IF:
            emitirIndentacao(saida, nivel);
            fputs("if (", saida);
            emitirExpressao(saida, no->esquerda);
            fputs(") {\n", saida);
            emitirListaComandos(saida, no->direita, nivel + 1);
            emitirIndentacao(saida, nivel);
            fputs("}", saida);
            if (no->alternativo) {
                fputs(" else {\n", saida);
                emitirListaComandos(saida, no->alternativo, nivel + 1);
                emitirIndentacao(saida, nivel);
                fputs("}", saida);
            }
            fputs("\n", saida);
            break;
        case AST_WHILE:
            emitirIndentacao(saida, nivel);
            fputs("while (", saida);
            emitirExpressao(saida, no->esquerda);
            fputs(") {\n", saida);
            emitirListaComandos(saida, no->direita, nivel + 1);
            emitirIndentacao(saida, nivel);
            fputs("}\n", saida);
            break;
        case AST_RETURN:
            emitirIndentacao(saida, nivel);
            fputs("return", saida);
            if (no->esquerda) {
                fputs(" ", saida);
                emitirExpressao(saida, no->esquerda);
            }
            fputs(";\n", saida);
            break;
        case AST_CHAMADA:
            emitirIndentacao(saida, nivel);
            emitirExpressao(saida, no);
            fputs(";\n", saida);
            break;
        default:
            break;
    }
}

static void emitirListaComandos(FILE *saida, const NoAST *lista, int nivel) {
    for (const NoAST *item = lista; item; item = item->proximo) {
        if (item->esquerda)
            emitirComando(saida, item->esquerda, nivel);
    }
}

static void emitirDeclaracoes(FILE *saida, DeclaracaoVariavel *variaveis, int quantidade, int nivel) {
    for (int i = 0; i < quantidade; i++) {
        emitirIndentacao(saida, nivel);
        fprintf(saida, "%s %s", nomeTipoC(variaveis[i].tipo), variaveis[i].nome);
        if (variaveis[i].tipo == TIPO_STRING)
            fputs(" = \"\"", saida);
        else
            fputs(" = 0", saida);
        fputs(";\n", saida);
    }
}

static void emitirFuncao(FILE *saida, const NoAST *funcao) {
    DeclaracaoVariavel locais[MAX_VARIAVEIS];
    int quantidadeLocais = 0;
    TipoDado tipoRetorno = TIPO_DESCONHECIDO;
    coletarVariaveis(funcao->direita, locais, &quantidadeLocais, funcao->esquerda);
    coletarTipoRetorno(funcao->direita, &tipoRetorno);
    if (tipoRetorno == TIPO_DESCONHECIDO)
        tipoRetorno = TIPO_INTEIRO;

    fprintf(saida, "%s %s(", nomeTipoC(tipoRetorno), funcao->nome);
    int primeiro = 1;
    for (const NoAST *p = funcao->esquerda; p; p = p->proximo) {
        if (!p->esquerda || p->esquerda->tipo != AST_ID) continue;
        if (!primeiro) fputs(", ", saida);
        fprintf(saida, "int %s", p->esquerda->nome);
        primeiro = 0;
    }
    if (primeiro)
        fputs("void", saida);
    fputs(") {\n", saida);
    emitirDeclaracoes(saida, locais, quantidadeLocais, 1);
    emitirListaComandos(saida, funcao->direita, 1);
    fputs("}\n\n", saida);
}

static void marcarConcatenacao(const NoAST *no) {
    if (!no) return;
    if (no->tipo == AST_OP && no->operador == '+') {
        if (tipoDoNo(no->esquerda) == TIPO_STRING || tipoDoNo(no->direita) == TIPO_STRING)
            usouConcatenacao = 1;
    }
    marcarConcatenacao(no->esquerda);
    marcarConcatenacao(no->direita);
    marcarConcatenacao(no->alternativo);
    marcarConcatenacao(no->proximo);
}

int gerarCodigoC(const NoAST *raiz, const char *arquivo) {
    if (!raiz || !arquivo) return 1;

    FILE *saida = fopen(arquivo, "w");
    if (!saida) {
        fprintf(stderr, "Erro: nao foi possivel criar %s\n", arquivo);
        return 1;
    }

    usouConcatenacao = 0;
    marcarConcatenacao(raiz);

    DeclaracaoVariavel globais[MAX_VARIAVEIS];
    int quantidadeGlobais = 0;
    const NoAST *comandos = (raiz->tipo == AST_PROGRAMA) ? raiz->esquerda : raiz;
    coletarVariaveis(comandos, globais, &quantidadeGlobais, NULL);

    fputs("/* Gerado automaticamente pelo compilador Python -> C */\n", saida);
    fputs("#include <stdio.h>\n", saida);
    fputs("#include <stdlib.h>\n", saida);
    fputs("#include <string.h>\n\n", saida);

    if (usouConcatenacao) {
        fputs("static char *concatenar(const char *a, const char *b) {\n", saida);
        fputs("    size_t n = strlen(a) + strlen(b);\n", saida);
        fputs("    char *r = (char *)malloc(n + 1);\n", saida);
        fputs("    if (!r) return \"\";\n", saida);
        fputs("    strcpy(r, a);\n", saida);
        fputs("    strcat(r, b);\n", saida);
        fputs("    return r;\n", saida);
        fputs("}\n\n", saida);
    }

    for (const NoAST *item = comandos; item; item = item->proximo) {
        if (item->esquerda && item->esquerda->tipo == AST_FUNC)
            emitirFuncao(saida, item->esquerda);
    }

    fputs("int main(void) {\n", saida);
    emitirDeclaracoes(saida, globais, quantidadeGlobais, 1);
    for (const NoAST *item = comandos; item; item = item->proximo) {
        if (item->esquerda && item->esquerda->tipo != AST_FUNC)
            emitirComando(saida, item->esquerda, 1);
    }
    fputs("    return 0;\n", saida);
    fputs("}\n", saida);

    fclose(saida);
    printf("Codigo C gerado em %s\n", arquivo);
    return 0;
}
