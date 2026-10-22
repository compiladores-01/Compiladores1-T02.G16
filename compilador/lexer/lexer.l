%{
#include <stdlib.h>
#include "parser.tab.h"
#include <string.h>

static char *copiarLexema(const char *texto) {
    size_t tamanho = strlen(texto) + 1;
    char *copia = malloc(tamanho);
    if (copia) memcpy(copia, texto, tamanho);
    return copia;
}
%}

%%
"print"     { return PRINT; }
"("     { return LPAREN; }
")"     { return RPAREN; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
":"         { return COLON; }

"=="        { return EQ; }
"!="        { return NEQ; }
"<="        { return LEQ; }
">="        { return GEQ; }
"<"         { return LT; }
">"         { return GT; }

[a-zA-Z_][a-zA-Z0-9_]* {
    if (strcmp(yytext, "true") == 0 || strcmp(yytext, "false") == 0)
        return BOOLEAN;
    yylval.texto = copiarLexema(yytext);
    return IDENTIFIER;
}
"="             {return ATRIBUES;}
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }
[0-9]+          { yylval.inteiro = atoi(yytext); return NUMBER; }
[0-9]+\.[0-9]+       { return FLOAT; }
\"[^\"]*\"            { yylval.texto = copiarLexema(yytext); return STRING; }
#.*             { /* Ignorar comentário */ }



[ \t]+          { }
\n              { return NEWLINE; }
.               { printf("Caractere inválido: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
