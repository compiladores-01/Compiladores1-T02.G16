%{
#include <stdlib.h>
#include "parser.tab.h"
#include <string.h>
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
    if (strcmp(yytext, "true") == 0 || strcmp(yytext, "false") == 0) {
        yylval.inteiro = (strcmp(yytext, "true") == 0);
        return BOOLEAN;
<<<<<<< Updated upstream
=======
    }
    yylval.texto = copiarLexema(yytext);
>>>>>>> Stashed changes
    return IDENTIFIER;
}

"="             {return ATRIBUES;}
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }
<<<<<<< Updated upstream
[0-9]+          { yylval = atoi(yytext); return NUMBER; }
[0-9]+\.[0-9]+       { return FLOAT; }
\"[^\"]*\"            { return STRING; }
=======
[0-9]+          { yylval.inteiro = atoi(yytext); return NUMBER; }
[0-9]+\.[0-9]+       { yylval.real = atof(yytext); return FLOAT; }
\"[^\"]*\"            { yylval.texto = copiarLexema(yytext); return STRING; }
>>>>>>> Stashed changes
#.*             { /* Ignorar comentário */ }



[ \t]+          { }
\n              { return NEWLINE; }
.               { printf("Caractere inválido: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
