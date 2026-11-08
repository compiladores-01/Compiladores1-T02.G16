%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

#define MAX_INDENTACAO 64
#define MAX_FILA 256

static char *copiarLexema(const char *texto) {
    size_t tamanho = strlen(texto) + 1;
    char *copia = malloc(tamanho);
    if (copia) memcpy(copia, texto, tamanho);
    return copia;
}

static int pilha_indent[MAX_INDENTACAO];
static int topo_indent = 0;

static int fila[MAX_FILA];
static int fila_ini = 0;
static int fila_fim = 0;

static void enfileirar(int tok) {
    if (fila_fim < MAX_FILA)
        fila[fila_fim++] = tok;
}

static int tem_fila(void) {
    return fila_ini < fila_fim;
}

static int desenfileirar(void) {
    return fila[fila_ini++];
}

static int contar_indent(const char *s) {
    int n = 0;
    for (; *s; s++)
        n += (*s == '\t') ? 4 : 1;
    return n;
}

static void aplicar_indentacao(int nivel) {
    int atual = pilha_indent[topo_indent];
    if (nivel == atual)
        return;
    if (nivel > atual) {
        if (topo_indent + 1 < MAX_INDENTACAO) {
            pilha_indent[++topo_indent] = nivel;
            enfileirar(INDENT);
        } else {
            fprintf(stderr, "Erro lexico: indentacao muito profunda na linha %d\n", yylineno);
        }
        return;
    }
    while (topo_indent > 0 && pilha_indent[topo_indent] > nivel) {
        topo_indent--;
        enfileirar(DEDENT);
    }
    if (pilha_indent[topo_indent] != nivel)
        fprintf(stderr, "Erro lexico: indentacao inconsistente na linha %d\n", yylineno);
}

#define YY_DECL static int yylex_raw(void)
#define YY_USER_INIT do { pilha_indent[0] = 0; topo_indent = 0; BEGIN(BOL); } while (0)
%}

%option noyywrap yylineno nounput noinput

%x BOL

%%

<BOL>\r             { }
<BOL>[ \t]*#.*\r?\n { }
<BOL>[ \t]*\r?\n    { }
<BOL>[ \t]+         {
                        aplicar_indentacao(contar_indent(yytext));
                        BEGIN(INITIAL);
                        if (tem_fila()) return desenfileirar();
                    }
<BOL>.              {
                        yyless(0);
                        BEGIN(INITIAL);
                        aplicar_indentacao(0);
                        if (tem_fila()) return desenfileirar();
                    }
<BOL><<EOF>>        {
                        aplicar_indentacao(0);
                        BEGIN(INITIAL);
                        if (tem_fila()) return desenfileirar();
                        return 0;
                    }

"print"     { return PRINT; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"def"       { return DEF; }
"return"    { return RETURN; }
"True"      { yylval.inteiro = 1; return BOOLEAN; }
"False"     { yylval.inteiro = 0; return BOOLEAN; }

"("         { return LPAREN; }
")"         { return RPAREN; }
":"         { return COLON; }
","         { return COMMA; }

"=="        { return EQ; }
"!="        { return NEQ; }
"<="        { return LEQ; }
">="        { return GEQ; }
"<"         { return LT; }
">"         { return GT; }

[a-zA-Z_][a-zA-Z0-9_]* {
    if (strcmp(yytext, "true") == 0 || strcmp(yytext, "false") == 0) {
        yylval.inteiro = (strcmp(yytext, "true") == 0);
        return BOOLEAN;
    }
    yylval.texto = copiarLexema(yytext);
    return IDENTIFIER;
}

"="             { return ATRIBUES; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }
[0-9]+\.[0-9]+  { yylval.real = atof(yytext); return FLOAT; }
[0-9]+          { yylval.inteiro = atoi(yytext); return NUMBER; }
\"[^\"]*\"      { yylval.texto = copiarLexema(yytext); return STRING; }
'[^']*'         { yylval.texto = copiarLexema(yytext); return STRING; }
#.*             { }

[ \t]+          { }
\r              { }
\n              { BEGIN(BOL); return NEWLINE; }
.               { fprintf(stderr, "Caractere invalido na linha %d: %s\n", yylineno, yytext); }

<<EOF>>         {
                    static int fim = 0;
                    if (!fim) {
                        fim = 1;
                        enfileirar(NEWLINE);
                        aplicar_indentacao(0);
                    }
                    if (tem_fila()) return desenfileirar();
                    return 0;
                }

%%

int yylex(void) {
    if (tem_fila())
        return desenfileirar();
    return yylex_raw();
}
