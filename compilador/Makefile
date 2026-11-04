CC = gcc
LEX = flex
YACC = bison
CFLAGS = -Wall -Wextra

TARGET = compilador-bin

all: $(TARGET)

<<<<<<< Updated upstream
# Regra de compilação
$(TARGET): $(PARSER) $(LEXER)
	bison -d $(PARSER) -o parser.tab.c
	flex -o lex.yy.c $(LEXER)
	$(CC) $(CFLAGS) parser.tab.c lex.yy.c -o $(TARGET)
=======
$(TARGET): parser.o lex.yy.o ast.o tabela.o
	$(CC) $(CFLAGS) -o $(TARGET) parser.o lex.yy.o ast.o tabela.o
>>>>>>> Stashed changes

parser.o: parser.tab.c parser.tab.h ast.h tabela.h tipos.h
	$(CC) $(CFLAGS) -c parser.tab.c -o parser.o

lex.yy.o: lex.yy.c parser.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c -o lex.yy.o

parser.tab.c: parser/parser.y ast.h tipos.h tabela.h
	$(YACC) -d -o $@ parser/parser.y

parser.tab.h: parser.tab.c

ast.o: ast.c ast.h tipos.h
	$(CC) $(CFLAGS) -c ast.c -o ast.o

tabela.o: tabela.c tabela.h tipos.h
	$(CC) $(CFLAGS) -c tabela.c -o tabela.o

lex.yy.c: lexer/lexer.l parser.tab.h
	$(LEX) -o $@ lexer/lexer.l

clean:
<<<<<<< Updated upstream
	rm -f $(TARGET) lex.yy.c parser.tab.c parser.tab.h parser.output temp.c temp.out
=======
	rm -f $(TARGET) *.o lex.yy.c parser.tab.c parser.tab.h
>>>>>>> Stashed changes
