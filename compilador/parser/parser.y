%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token IDENTIFIER ATRIBUES NUMBER FLOAT STRING BOOLEAN
%token PRINT IF ELSE WHILE COLON NEWLINE
%token LPAREN RPAREN LBRACE RBRACE
%token PLUS MINUS TIMES DIVIDE
%token EQ NEQ LEQ GEQ LT GT

%left EQ NEQ LT GT LEQ GEQ
%left PLUS MINUS
%left TIMES DIVIDE

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

program:
    command_list;

command_list:
    command |
    command_list command;

command:
    variable NEWLINE |
    print_stmt NEWLINE |
    if_stmt |
    while_stmt |
    NEWLINE;

variable:
    IDENTIFIER ATRIBUES expr;

print_stmt:
    PRINT LPAREN expr RPAREN;

if_stmt:
    IF expr COLON NEWLINE block %prec LOWER_THAN_ELSE |
    IF expr COLON NEWLINE block ELSE COLON NEWLINE block;

while_stmt:
    WHILE expr LBRACE command_list RBRACE;

block:
    LBRACE command_list RBRACE;

expr:
    NUMBER |
    FLOAT |
    STRING |
    BOOLEAN |
    IDENTIFIER |
    expr PLUS expr |
    expr MINUS expr |
    expr TIMES expr |
    expr DIVIDE expr |
    expr EQ expr |
    expr NEQ expr |
    expr LT expr |
    expr GT expr |
    expr LEQ expr |
    expr GEQ expr |
    LPAREN expr RPAREN;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}

