# Compilador — funcionamento interno

Este documento explica **como o compilador funciona por dentro**, etapa por etapa. Para instalar, compilar e rodar, veja o [README principal](../README.md).

## Arquivos

| Arquivo | Etapa | Responsabilidade |
|---|---|---|
| `lexer/lexer.l` | Análise léxica | Transforma o texto em tokens. Gera `INDENT`/`DEDENT` a partir do recuo das linhas |
| `parser/parser.y` | Análise sintática + semântica | Gramática do subconjunto Python. Constrói a AST e faz as verificações semânticas |
| `ast.c` / `ast.h` | Representação | Nós da árvore sintática abstrata e a impressão da árvore |
| `tabela.c` / `tabela.h` | Semântica | Tabela de símbolos: nome, tipo e escopo de cada variável e função |
| `geracao.c` / `geracao.h` | Geração de código | Percorre a AST e escreve o programa C |
| `tipos.h` | Comum | Tipos de dados: `INTEIRO`, `FLOAT`, `STRING`, `BOOLEAN`, `FUNCAO` |
| `test_lexer.c` | Testes | Roda só o lexer e imprime um token por linha |
| `Makefile` | Build | `make`, `make test_lexer`, `make test`, `make clean` |

## Comandos

```bash
make              # gera compilador-bin (roda Bison, Flex e GCC na ordem certa)
make test         # constrói tudo e roda a suíte de testes
make clean        # apaga os arquivos gerados

./compilador-bin entrada.py saida.c    # traduz entrada.py para saida.c
echo 'x = 1 + 2' | ./compilador-bin    # lê da entrada padrão e gera saida.c
```

Além do arquivo C, o compilador imprime na tela a AST reconstruída como código e a tabela de símbolos:

```text
$ echo 'x = 1 + 2 * 3' | ./compilador-bin
x = (1 + (2 * 3))
Codigo C gerado em saida.c
TABELA DE SIMBOLOS
x               | INTEIRO | escopo 0
-----
```

Os parênteses mostram a estrutura da árvore: `2 * 3` fica mais embaixo, por isso é calculado primeiro.

## Etapas

### 1. Análise léxica (Flex)

Reconhece palavras-chave (`if`, `else`, `while`, `def`, `return`, `print`, `True`, `False`), identificadores, números inteiros e reais, strings, operadores e comentários.

- **Indentação:** o lexer mantém uma pilha com os níveis de recuo. Quando uma linha tem mais recuo que a anterior, emite `INDENT`. Quando volta, emite um `DEDENT` para cada nível fechado. Assim o parser enxerga os blocos de Python como se fossem `{` e `}`.
- **Strings:** aceita aspas duplas e simples. Aspas simples são convertidas para duplas (`'oi'` → `"oi"`), porque em C texto só existe com aspas duplas.
- **Erros léxicos:** caractere inválido (`@`) e string sem aspa de fechamento geram mensagem com o número da linha, e a análise continua.

### 2. Análise sintática (Bison)

A gramática define programa, comandos (atribuição, `print`, `if`/`else`, `while`, `def`, `return`) e expressões. A precedência dos operadores é declarada com `%left` (`*` e `/` antes de `+` e `-`), e o *else* pendente é resolvido com `%nonassoc`. Cada regra constrói um nó da AST.

### 3. Análise semântica e tabela de símbolos

Python não declara tipos, mas C exige. Por isso o compilador **deduz o tipo de cada variável pelo primeiro valor atribuído** (`x = 2.5` → `x` é `FLOAT`) e registra na tabela de símbolos. A partir daí verifica:

| Verificação | Exemplo | Resultado |
|---|---|---|
| Variável usada antes de ser definida | `y = x + 5` | `Erro semantico: variavel 'x' usada antes de ser definida` |
| Mudança de tipo | `x = 10` e depois `x = "texto"` | `Erro semantico: variavel 'x' e inteiro e nao pode receber string` |
| Reatribuição do mesmo tipo | `x = 10` e depois `x = 20` | permitido, como em Python |

Se houver erro semântico, o código C não é gerado.

### 4. Geração de código C

O gerador percorre a AST e:

1. declara as variáveis globais com o tipo inferido (`int`, `double`, `const char *`): no início do `main` ou, se alguma função lê a variável, fora do `main`, para a função enxergar;
2. escreve cada função `def` como uma função C antes do `main`. O tipo de cada parâmetro é deduzido pelos argumentos das chamadas (`f("oi")` → `const char *`), e o tipo de retorno pelos `return`;
3. traduz cada comando: `if`/`while` viram blocos C, e `print` vira `printf` com o formato do tipo (`%d`, `%g`, `%s`, ou `True`/`False` para booleanos);
4. quando há concatenação de strings (`s + t`), inclui uma função auxiliar `concatenar()`.

O código C é gerado **diretamente a partir da AST**, sem uma representação intermediária (TAC). Para o subconjunto escolhido, a AST já tem toda a informação necessária, e isso mantém o compilador menor e mais fácil de verificar.

## Limitações conhecidas

- Um parâmetro não pode receber tipos incompatíveis em chamadas diferentes (`f(1)` e `f("a")` é erro semântico). Inteiro e float no mesmo parâmetro viram `double`.
- A impressão da AST na tela não indenta o conteúdo dos blocos (a estrutura está correta, só a visualização fica achatada).
- Não há `for`, listas, classes nem `import`.
