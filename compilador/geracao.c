#include "geracao.h"
#include "tabela.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARIAVEIS 128
#define MAX_FUNCOES 64
#define MAX_PARAMETROS 16
#define PASSOS_INFERENCIA 4

typedef struct {
    char nome[64];
    TipoDado tipo;
    int usadaEmFuncao;   /* global lida dentro de alguma funcao */
} DeclaracaoVariavel;

/* Informacoes de cada funcao (def), descobertas antes de gerar o C:
 * o tipo de cada parametro e deduzido pelas chamadas, e o tipo de retorno
 * pelos 'return' do corpo. */
typedef struct {
    const NoAST *no;
    int quantidadeParametros;
    TipoDado parametros[MAX_PARAMETROS];
    TipoDado retorno;
} InfoFuncao;

static int usouConcatenacao = 0;
static int usouModulo = 0;

static InfoFuncao funcoes[MAX_FUNCOES];
static int quantidadeFuncoes = 0;

/* Erros encontrados na geracao (ex.: parametro recebendo tipos
 * incompativeis). So sao reportados no ultimo passo da inferencia, quando
 * os tipos ja estabilizaram. */
static int errosGeracao = 0;
static int reportarErros = 0;

/* Contexto de tipos: variaveis ja registradas, usadas por tipoDoNo() para
 * descobrir o tipo de um identificador (AST_ID) dentro de expressoes. */
static DeclaracaoVariavel *ctxGlobais = NULL;
static int *ctxQtdGlobais = NULL;
static DeclaracaoVariavel *ctxLocais = NULL;
static int *ctxQtdLocais = NULL;
static InfoFuncao *ctxFuncao = NULL;

static TipoDado tipoDoNo(const NoAST *no);

static int mesmoNome(const char *a, const char *b) {
    return a && b && strcmp(a, b) == 0;
}

static const char *nomeTipo(TipoDado t) {
    switch (t) {
        case TIPO_INTEIRO: return "inteiro";
        case TIPO_FLOAT:   return "float";
        case TIPO_STRING:  return "string";
        case TIPO_BOOLEAN: return "boolean";
        default:           return "desconhecido";
    }
}

static void erroGeracao(const char *mensagem, const char *nome, TipoDado a, TipoDado b) {
    if (!reportarErros) return;
    fprintf(stderr, "Erro semantico: ");
    fprintf(stderr, mensagem, nome, nomeTipo(a), nomeTipo(b));
    fprintf(stderr, "\n");
    errosGeracao++;
}

/* Posicao de 'nome' na lista de parametros, ou -1. */
static int indiceParametro(const NoAST *parametros, const char *nome) {
    int i = 0;
    for (const NoAST *p = parametros; p; p = p->proximo) {
        if (!p->esquerda || p->esquerda->tipo != AST_ID) continue;
        if (mesmoNome(p->esquerda->nome, nome)) return i;
        i++;
    }
    return -1;
}

static int ehParametro(const NoAST *parametros, const char *nome) {
    return indiceParametro(parametros, nome) >= 0;
}

static InfoFuncao *buscarFuncao(const char *nome) {
    for (int i = 0; i < quantidadeFuncoes; i++)
        if (mesmoNome(funcoes[i].no->nome, nome)) return &funcoes[i];
    return NULL;
}

static DeclaracaoVariavel *buscarDeclaracao(DeclaracaoVariavel *variaveis, int quantidade,
                                            const char *nome) {
    for (int i = 0; i < quantidade; i++)
        if (mesmoNome(variaveis[i].nome, nome)) return &variaveis[i];
    return NULL;
}

static TipoDado tipoDaVariavel(const char *nome) {
    if (!nome) return TIPO_DESCONHECIDO;
    if (ctxFuncao) {
        int i = indiceParametro(ctxFuncao->no->esquerda, nome);
        if (i >= 0 && i < MAX_PARAMETROS) return ctxFuncao->parametros[i];
    }
    if (ctxLocais && ctxQtdLocais) {
        DeclaracaoVariavel *d = buscarDeclaracao(ctxLocais, *ctxQtdLocais, nome);
        if (d) return d->tipo;
    }
    if (ctxGlobais && ctxQtdGlobais) {
        DeclaracaoVariavel *d = buscarDeclaracao(ctxGlobais, *ctxQtdGlobais, nome);
        if (d) return d->tipo;
    }
    return TIPO_DESCONHECIDO;
}

/* Mesma regra da analise semantica do parser: o tipo de uma variavel e o
 * do primeiro valor; depois so aceita o mesmo tipo (ou inteiro em float). */
static int tiposCompativeis(TipoDado atual, TipoDado novo) {
    if (atual == TIPO_DESCONHECIDO || novo == TIPO_DESCONHECIDO) return 1;
    if (atual == novo) return 1;
    return atual == TIPO_FLOAT && novo == TIPO_INTEIRO;
}

static void registrarVariavel(DeclaracaoVariavel *variaveis, int *quantidade,
                              const char *nome, TipoDado tipo, const NoAST *parametros) {
    if (!nome || nome[0] == '\0') return;
    if (parametros && ehParametro(parametros, nome)) return;
    DeclaracaoVariavel *d = buscarDeclaracao(variaveis, *quantidade, nome);
    if (d) {
        if (d->tipo == TIPO_DESCONHECIDO)
            d->tipo = tipo;
        else if (!tiposCompativeis(d->tipo, tipo))
            erroGeracao("variavel '%s' e %s e nao pode receber %s", nome, d->tipo, tipo);
        return;
    }
    if (*quantidade >= MAX_VARIAVEIS) return;
    strncpy(variaveis[*quantidade].nome, nome, sizeof(variaveis[*quantidade].nome) - 1);
    variaveis[*quantidade].nome[sizeof(variaveis[*quantidade].nome) - 1] = '\0';
    variaveis[*quantidade].tipo = tipo;
    variaveis[*quantidade].usadaEmFuncao = 0;
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
        case AST_CHAMADA: {
            InfoFuncao *f = buscarFuncao(no->nome);
            return f ? f->retorno : TIPO_DESCONHECIDO;
        }
        case AST_ID:      return tipoDaVariavel(no->nome);
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

/* Junta o tipo de um argumento ao que ja se sabe do parametro:
 * inteiro + float vira float; tipos incompativeis sao erro. */
static void mesclarParametro(InfoFuncao *f, int i, TipoDado novo) {
    if (i >= MAX_PARAMETROS || novo == TIPO_DESCONHECIDO) return;
    TipoDado *atual = &f->parametros[i];
    if (*atual == TIPO_DESCONHECIDO || *atual == novo) {
        *atual = novo;
        return;
    }
    if ((*atual == TIPO_INTEIRO || *atual == TIPO_FLOAT) &&
        (novo == TIPO_INTEIRO || novo == TIPO_FLOAT)) {
        *atual = TIPO_FLOAT;
        return;
    }
    erroGeracao("funcao '%s' recebe tipos incompativeis no mesmo parametro (%s e %s)",
                f->no->nome, *atual, novo);
}

/* Percorre as chamadas de funcao e deduz o tipo de cada parametro pelos
 * argumentos usados. Nao entra no corpo de outras funcoes (cada corpo e
 * percorrido com o seu proprio contexto). */
static void inferirParametros(const NoAST *no) {
    if (!no) return;
    if (no->tipo == AST_FUNC) {
        inferirParametros(no->proximo);
        return;
    }
    if (no->tipo == AST_CHAMADA) {
        InfoFuncao *f = buscarFuncao(no->nome);
        if (f) {
            int i = 0;
            for (const NoAST *a = no->esquerda; a; a = a->proximo) {
                if (!a->esquerda) continue;
                mesclarParametro(f, i, tipoDoNo(a->esquerda));
                i++;
            }
        }
    }
    inferirParametros(no->esquerda);
    inferirParametros(no->direita);
    inferirParametros(no->alternativo);
    inferirParametros(no->proximo);
}

/* Marca as globais lidas dentro de uma funcao: elas precisam ser declaradas
 * fora do main para a funcao enxergar. */
static void marcarGlobaisUsadas(const NoAST *no, DeclaracaoVariavel *locais, int quantidadeLocais,
                                const NoAST *parametros) {
    if (!no) return;
    if (no->tipo == AST_ID && !ehParametro(parametros, no->nome) &&
        !buscarDeclaracao(locais, quantidadeLocais, no->nome) && ctxGlobais && ctxQtdGlobais) {
        DeclaracaoVariavel *g = buscarDeclaracao(ctxGlobais, *ctxQtdGlobais, no->nome);
        if (g) g->usadaEmFuncao = 1;
    }
    marcarGlobaisUsadas(no->esquerda, locais, quantidadeLocais, parametros);
    marcarGlobaisUsadas(no->direita, locais, quantidadeLocais, parametros);
    marcarGlobaisUsadas(no->alternativo, locais, quantidadeLocais, parametros);
    marcarGlobaisUsadas(no->proximo, locais, quantidadeLocais, parametros);
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
            if (no->operador == '%') {
                /* resto com o sinal do divisor, como em Python (-7 % 3 == 2) */
                fputs("py_resto(", saida);
                emitirExpressao(saida, no->esquerda);
                fputs(", ", saida);
                emitirExpressao(saida, no->direita);
                fputs(")", saida);
                break;
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
            if (!no->esquerda) {            /* not x */
                fputs("(!", saida);
                emitirExpressao(saida, no->direita);
                fputs(")", saida);
                break;
            }
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

static void emitirFuncao(FILE *saida, InfoFuncao *f) {
    const NoAST *funcao = f->no;
    DeclaracaoVariavel locais[MAX_VARIAVEIS];
    int quantidadeLocais = 0;
    ctxLocais = locais;
    ctxQtdLocais = &quantidadeLocais;
    ctxFuncao = f;
    coletarVariaveis(funcao->direita, locais, &quantidadeLocais, funcao->esquerda);

    fprintf(saida, "%s %s(", nomeTipoC(f->retorno), funcao->nome);
    int i = 0;
    for (const NoAST *p = funcao->esquerda; p; p = p->proximo) {
        if (!p->esquerda || p->esquerda->tipo != AST_ID) continue;
        if (i > 0) fputs(", ", saida);
        TipoDado t = (i < MAX_PARAMETROS) ? f->parametros[i] : TIPO_INTEIRO;
        fprintf(saida, "%s %s", nomeTipoC(t), p->esquerda->nome);
        i++;
    }
    if (i == 0)
        fputs("void", saida);
    fputs(") {\n", saida);
    emitirDeclaracoes(saida, locais, quantidadeLocais, 1);
    emitirListaComandos(saida, funcao->direita, 1);
    fputs("}\n\n", saida);
    ctxLocais = NULL;
    ctxQtdLocais = NULL;
    ctxFuncao = NULL;
}

static void marcarConcatenacao(const NoAST *no) {
    if (!no) return;
    if (no->tipo == AST_OP && no->operador == '%')
        usouModulo = 1;
    if (no->tipo == AST_OP && no->operador == '+') {
        if (tipoDoNo(no->esquerda) == TIPO_STRING || tipoDoNo(no->direita) == TIPO_STRING)
            usouConcatenacao = 1;
    }
    marcarConcatenacao(no->esquerda);
    marcarConcatenacao(no->direita);
    marcarConcatenacao(no->alternativo);
    marcarConcatenacao(no->proximo);
}

/* Verifica se alguma funcao concatena strings, usando o contexto de cada
 * funcao (parametros e variaveis locais). */
static void marcarConcatenacaoEmFuncoes(void) {
    for (int k = 0; k < quantidadeFuncoes; k++) {
        InfoFuncao *f = &funcoes[k];
        DeclaracaoVariavel locais[MAX_VARIAVEIS];
        int quantidadeLocais = 0;
        ctxFuncao = f;
        ctxLocais = locais;
        ctxQtdLocais = &quantidadeLocais;
        coletarVariaveis(f->no->direita, locais, &quantidadeLocais, f->no->esquerda);
        marcarConcatenacao(f->no->direita);
    }
    ctxFuncao = NULL;
    ctxLocais = NULL;
    ctxQtdLocais = NULL;
}

/* Descobre os tipos de globais, parametros e retornos antes de gerar o C.
 * Os tipos dependem uns dos outros (o retorno depende dos parametros, que
 * dependem dos argumentos, que podem ser globais...), por isso a analise
 * roda alguns passos, ate os tipos estabilizarem. */
static void analisarTipos(const NoAST *comandos, DeclaracaoVariavel *globais, int *quantidadeGlobais) {
    quantidadeFuncoes = 0;
    for (const NoAST *item = comandos; item; item = item->proximo) {
        if (!item->esquerda || item->esquerda->tipo != AST_FUNC) continue;
        if (quantidadeFuncoes >= MAX_FUNCOES) break;
        InfoFuncao *f = &funcoes[quantidadeFuncoes++];
        f->no = item->esquerda;
        f->retorno = TIPO_DESCONHECIDO;
        f->quantidadeParametros = 0;
        for (int i = 0; i < MAX_PARAMETROS; i++)
            f->parametros[i] = TIPO_DESCONHECIDO;
    }

    ctxGlobais = globais;
    ctxQtdGlobais = quantidadeGlobais;

    for (int passo = 0; passo < PASSOS_INFERENCIA; passo++) {
        reportarErros = (passo == PASSOS_INFERENCIA - 1);

        *quantidadeGlobais = 0;
        ctxFuncao = NULL;
        ctxLocais = NULL;
        ctxQtdLocais = NULL;
        coletarVariaveis(comandos, globais, quantidadeGlobais, NULL);
        inferirParametros(comandos);

        for (int k = 0; k < quantidadeFuncoes; k++) {
            InfoFuncao *f = &funcoes[k];
            DeclaracaoVariavel locais[MAX_VARIAVEIS];
            int quantidadeLocais = 0;
            ctxFuncao = f;
            ctxLocais = locais;
            ctxQtdLocais = &quantidadeLocais;
            coletarVariaveis(f->no->direita, locais, &quantidadeLocais, f->no->esquerda);
            TipoDado retorno = TIPO_DESCONHECIDO;
            coletarTipoRetorno(f->no->direita, &retorno);
            f->retorno = retorno;
            inferirParametros(f->no->direita);
            if (reportarErros)
                marcarGlobaisUsadas(f->no->direita, locais, quantidadeLocais, f->no->esquerda);
        }
        ctxFuncao = NULL;
        ctxLocais = NULL;
        ctxQtdLocais = NULL;
    }
    reportarErros = 0;

    /* o que nao foi possivel deduzir vira int */
    for (int k = 0; k < quantidadeFuncoes; k++) {
        if (funcoes[k].retorno == TIPO_DESCONHECIDO) funcoes[k].retorno = TIPO_INTEIRO;
        for (int i = 0; i < MAX_PARAMETROS; i++)
            if (funcoes[k].parametros[i] == TIPO_DESCONHECIDO) funcoes[k].parametros[i] = TIPO_INTEIRO;
    }

    /* A analise do parser nao sabe o tipo do resultado de uma chamada de
     * funcao (marca como desconhecido). Atualiza a tabela de simbolos com o
     * tipo descoberto aqui. */
    for (int i = 0; i < *quantidadeGlobais; i++) {
        Simbolo *s = buscarSimbolo(globais[i].nome);
        if (s && s->tipo == TIPO_DESCONHECIDO && globais[i].tipo != TIPO_DESCONHECIDO)
            s->tipo = globais[i].tipo;
    }
}

int gerarCodigoC(const NoAST *raiz, const char *arquivo) {
    if (!raiz || !arquivo) return 1;

    DeclaracaoVariavel globais[MAX_VARIAVEIS];
    int quantidadeGlobais = 0;
    const NoAST *comandos = (raiz->tipo == AST_PROGRAMA) ? raiz->esquerda : raiz;

    errosGeracao = 0;
    analisarTipos(comandos, globais, &quantidadeGlobais);
    if (errosGeracao > 0) {
        ctxGlobais = NULL;
        ctxQtdGlobais = NULL;
        return 1;
    }

    FILE *saida = fopen(arquivo, "w");
    if (!saida) {
        fprintf(stderr, "Erro: nao foi possivel criar %s\n", arquivo);
        return 1;
    }

    /* depois de conhecer os tipos, para reconhecer concatenacao entre
     * variaveis string (ex.: s + t) */
    usouConcatenacao = 0;
    usouModulo = 0;
    marcarConcatenacao(raiz);
    marcarConcatenacaoEmFuncoes();

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

    if (usouModulo) {
        fputs("static int py_resto(int a, int b) {\n", saida);
        fputs("    int r = a % b;\n", saida);
        fputs("    if (r != 0 && (r < 0) != (b < 0)) r += b;\n", saida);
        fputs("    return r;\n", saida);
        fputs("}\n\n", saida);
    }

    /* globais lidas dentro de funcoes: declaradas fora do main */
    DeclaracaoVariavel compartilhadas[MAX_VARIAVEIS];
    DeclaracaoVariavel doMain[MAX_VARIAVEIS];
    int qtdCompartilhadas = 0, qtdMain = 0;
    for (int i = 0; i < quantidadeGlobais; i++) {
        if (globais[i].usadaEmFuncao) compartilhadas[qtdCompartilhadas++] = globais[i];
        else doMain[qtdMain++] = globais[i];
    }
    if (qtdCompartilhadas > 0) {
        emitirDeclaracoes(saida, compartilhadas, qtdCompartilhadas, 0);
        fputs("\n", saida);
    }

    for (int k = 0; k < quantidadeFuncoes; k++)
        emitirFuncao(saida, &funcoes[k]);

    fputs("int main(void) {\n", saida);
    emitirDeclaracoes(saida, doMain, qtdMain, 1);
    for (const NoAST *item = comandos; item; item = item->proximo) {
        if (item->esquerda && item->esquerda->tipo != AST_FUNC)
            emitirComando(saida, item->esquerda, 1);
    }
    fputs("    return 0;\n", saida);
    fputs("}\n", saida);

    fclose(saida);
    ctxGlobais = NULL;
    ctxQtdGlobais = NULL;
    printf("Codigo C gerado em %s\n", arquivo);
    return 0;
}
