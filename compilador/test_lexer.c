#include <stdio.h>
#include "parser.tab.h"

extern int yylex(void);
extern char *yytext;
extern int yylineno;

int main(void) {
    int token;
    while ((token = yylex()) != 0) {
        printf("Token: %d, Valor: '%s', Linha: %d\n", token, yytext, yylineno);
    }
    return 0;
}
