CC = gcc
LEX = flex
YACC = bison
CFLAGS = -Wall -Wextra

TARGET = compilador-bin

.PHONY: all clean test

all: $(TARGET)

$(TARGET): parser.o lex.yy.o ast.o tabela.o geracao.o
	$(CC) $(CFLAGS) -o $@ $^

parser.o: parser.tab.c parser.tab.h ast.h tabela.h tipos.h geracao.h
	$(CC) $(CFLAGS) -c parser.tab.c -o $@

lex.yy.o: lex.yy.c parser.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c -o $@

parser.tab.c: parser/parser.y ast.h tipos.h tabela.h geracao.h
	$(YACC) -d -o $@ $<

parser.tab.h: parser.tab.c

lex.yy.c: lexer/lexer.l parser.tab.h
	$(LEX) -o $@ $<

ast.o: ast.c ast.h tipos.h
	$(CC) $(CFLAGS) -c ast.c -o $@

tabela.o: tabela.c tabela.h tipos.h
	$(CC) $(CFLAGS) -c tabela.c -o $@

geracao.o: geracao.c geracao.h ast.h tipos.h tabela.h
	$(CC) $(CFLAGS) -c geracao.c -o $@

# Programa auxiliar que roda so o lexer (usado pelos testes)
test_lexer: test_lexer.c lex.yy.c parser.tab.h
	$(CC) $(CFLAGS) -o $@ test_lexer.c lex.yy.c

# Constroi tudo e roda a suite de testes
test: $(TARGET) test_lexer
	cd ../tests && bash run_tests.sh

clean:
	rm -f $(TARGET) test_lexer *.o lex.yy.c parser.tab.c parser.tab.h parser.output saida.c
