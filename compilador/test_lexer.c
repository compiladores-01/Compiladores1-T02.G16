/*
 * test_lexer.c - roda SO o analisador lexico e imprime um token por linha.
 *
 * Formato:  NOME            (tokens fixos: PLUS, IF, NEWLINE, INDENT...)
 *           NOME(lexema)    (tokens com valor: IDENTIFIER, NUMBER, FLOAT,
 *                            STRING, BOOLEAN)
 *
 * Compilar:  make test_lexer
 * Usar:      ./test_lexer < arquivo.py
 */
#include <stdio.h>
#include "parser.tab.h"

extern int yylex(void);
extern char *yytext;

/* O lexer escreve em yylval; normalmente quem define essa variavel e o
 * parser. Definimos aqui para testar o lexer sem linkar o parser. */
YYSTYPE yylval;

static const char *nomeToken(int t) {
    switch (t) {
        case IDENTIFIER: return "IDENTIFIER";
        case STRING:     return "STRING";
        case NUMBER:     return "NUMBER";
        case BOOLEAN:    return "BOOLEAN";
        case FLOAT:      return "FLOAT";
        case PRINT:      return "PRINT";
        case IF:         return "IF";
        case ELSE:       return "ELSE";
        case WHILE:      return "WHILE";
        case DEF:        return "DEF";
        case RETURN:     return "RETURN";
        case COLON:      return "COLON";
        case NEWLINE:    return "NEWLINE";
        case COMMA:      return "COMMA";
        case INDENT:     return "INDENT";
        case DEDENT:     return "DEDENT";
        case LPAREN:     return "LPAREN";
        case RPAREN:     return "RPAREN";
        case PLUS:       return "PLUS";
        case MINUS:      return "MINUS";
        case TIMES:      return "TIMES";
        case DIVIDE:     return "DIVIDE";
        case EQ:         return "EQ";
        case NEQ:        return "NEQ";
        case LEQ:        return "LEQ";
        case GEQ:        return "GEQ";
        case LT:         return "LT";
        case GT:         return "GT";
        case ATRIBUES:   return "ATRIBUES";
        default:         return "DESCONHECIDO";
    }
}

int main(void) {
    /* sem buffer: as mensagens de erro do lexer (stderr) aparecem na ordem
     * certa no meio dos tokens */
    setvbuf(stdout, NULL, _IONBF, 0);

    int t;
    while ((t = yylex()) != 0) {
        switch (t) {
            case IDENTIFIER:
            case STRING:
            case NUMBER:
            case FLOAT:
            case BOOLEAN:
                printf("%s(%s)\n", nomeToken(t), yytext);
                break;
            default:
                printf("%s\n", nomeToken(t));
                break;
        }
    }
    return 0;
}
