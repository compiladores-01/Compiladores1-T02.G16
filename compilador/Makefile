CC = gcc
LEX = flex
YACC = bison
CFLAGS = -Wall -Wextra

TARGET = compilador-bin

.PHONY: all clean

all: $(TARGET)

$(TARGET): parser.o lex.yy.o ast.o tabela.o
	$(CC) $(CFLAGS) -o $@ $^

parser.o: parser.tab.c parser.tab.h ast.h tabela.h tipos.h
	$(CC) $(CFLAGS) -c parser.tab.c -o $@

lex.yy.o: lex.yy.c parser.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c -o $@

parser.tab.c: parser/parser.y ast.h tipos.h tabela.h
	$(YACC) -d -o $@ $<

parser.tab.h: parser.tab.c

lex.yy.c: lexer/lexer.l parser.tab.h
	$(LEX) -o $@ $<

ast.o: ast.c ast.h tipos.h
	$(CC) $(CFLAGS) -c ast.c -o $@

tabela.o: tabela.c tabela.h tipos.h
	$(CC) $(CFLAGS) -c tabela.c -o $@

clean:
	rm -f $(TARGET) *.o lex.yy.c parser.tab.c parser.tab.h parser.output
