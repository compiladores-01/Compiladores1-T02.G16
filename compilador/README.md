>  **ATENÇÃO — VERSÃO PROVISÓRIA**
>
> Este README é uma versão **provisória**, elaborada para revisão do grupo. O conteúdo ainda pode sofrer alterações antes da versão final da documentação do projeto.
>
> **Não considerar este arquivo como a versão definitiva do README.**

# Compilador Python para C

Protótipo do compilador de um subconjunto de Python para C, desenvolvido para a disciplina FGA0003 - Compiladores 1.

## Estrutura do Projeto

O projeto foi refatorado e agora conta com os seguintes módulos:

- `lexer/lexer.l`: Analisador léxico (Flex).
- `parser/parser.y`: Analisador sintático e ações semânticas (Bison).
- `src/ast.c` e `src/ast.h`: Construção e impressão da Árvore Sintática Abstrata (AST).
- `tabela.c` e `tabela.h`: Tabela de Símbolos e verificação de tipos.
- `Makefile`: Automação da compilação.

## Como Compilar

A forma correta de compilar o projeto agora é usando o `Makefile`. Na pasta `compilador/`, execute os comandos abaixo em sequência:

```bash
make clean
make
```

O comando `make` vai executar o Flex, o Bison e o GCC na ordem correta, gerando o executável `compilador-bin`.

> **Nota:** O comando antigo `gcc parser.tab.c lex.yy.c -o compilador` não funciona mais, pois agora o projeto depende também de `ast.c` e `tabela.c`.

## Como Executar

Você pode passar o código Python via entrada padrão (stdin):

```bash
echo 'x = 10 + 2.5' | ./compilador-bin
```

A saída mostrará a árvore gerada e a Tabela de Símbolos.

## Testes

O projeto possui uma suíte de testes que cobre as principais etapas do compilador:

- **Lexer:** Validação de tokens (identificadores, números, strings, operadores, palavras reservadas, comentários, caracteres inválidos e strings não terminadas).
- **Parser:** Validação da gramática (atribuições, `print`, `if`, `while` e erros sintáticos).
- **AST:** Validação da impressão da Árvore Sintática Abstrata (atribuição, precedência, `print` e `if`).
- **Tabela de Símbolos:** Validação da inserção, busca, redeclaração e erros de tipo (semântica).

> **Nota:** A suíte completa está consolidada nos PRs #33 e #36. Enquanto esses PRs não forem mesclados, alguns testes podem não estar disponíveis na branch principal.

### Testes do Lexer

Para rodar o protótipo atual de testes do lexer:

```bash
cd ../tests
./run_lexer_tests.sh
```

## Limitações Conhecidas

- A AST do `if` e `else` ainda não está sendo construída corretamente, pois a função `imprimirAST` não trata esses nós.
- O parser atual não consome o `NEWLINE` no bloco `if`, gerando erro sintático.
- Strings com aspas simples (`'hello'`) não são suportadas pelo lexer.
- O compilador não detecta uso de variáveis não declaradas de forma abrangente em todos os contextos.

## Equipe

- Fernanda
- Manoel
- Cauã