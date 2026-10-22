# Nome do executável final
TARGET = meu_compilador

# Arquivos fonte
LEXER = lexer/lexer.l
PARSER = parser/parser.y

# Compilador e flags
CC = gcc
CFLAGS = -Wall

all: $(TARGET)

# Regra de compilação
$(TARGET): $(PARSER) $(LEXER)
	bison -d $(PARSER) -o parser.tab.c
	flex -o lex.yy.c $(LEXER)
	$(CC) $(CFLAGS) parser.tab.c lex.yy.c -o $(TARGET)

# Regra para rodar os testes
test: $(TARGET)
	@echo "--- Executando Teste ---"
	./$(TARGET) < entrada.py
	@echo "--- Teste Concluído ---"

# Regra para limpar arquivos gerados
clean:
	rm -f $(TARGET) lex.yy.c parser.tab.c parser.tab.h parser.output temp.c temp.out