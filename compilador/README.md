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

Reconhece palavras-chave (`if`, `elif`, `else`, `while`, `def`, `return`, `print`, `and`, `or`, `not`, `True`, `False`), identificadores, números inteiros e reais, strings, operadores (incluindo `%`) e comentários.

- **Indentação:** o lexer mantém uma pilha com os níveis de recuo. Quando uma linha tem mais recuo que a anterior, emite `INDENT`. Quando volta, emite um `DEDENT` para cada nível fechado. Assim o parser enxerga os blocos de Python como se fossem `{` e `}`.
- **Strings:** aceita aspas duplas e simples. Aspas simples são convertidas para duplas (`'oi'` → `"oi"`), porque em C texto só existe com aspas duplas.
- **Erros léxicos:** caractere inválido (`@`) e string sem aspa de fechamento geram mensagem com o número da linha, e a análise continua.

### 2. Análise sintática (Bison)

A gramática define programa, comandos (atribuição, `print`, `if`/`elif`/`else`, `while`, `def`, `return`) e expressões. Cada regra constrói um nó da AST.

- **Precedência**, declarada com `%left`/`%right`, igual à de Python, da menor para a maior: `or` < `and` < `not` < comparações < `+ -` < `* / %` < `-` unário. Por isso `not x == 3` é `not (x == 3)`.
- **`elif`** vira um `if` dentro do `else`: `if a: ... elif b: ... else: ...` é o mesmo que `if a: ... else: (if b: ... else: ...)`. Aceita quantos `elif` forem necessários, sem nó novo na AST.
- **Número negativo:** `-5` vira o literal `-5`; `-x` vira `(0 - x)`.
- O *else* pendente é resolvido com `%nonassoc`.

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
3. traduz cada comando: `if`/`while` viram blocos C, `and`/`or`/`not` viram `&&`/`||`/`!`, e `print` usa o formato do tipo (`%d`, `%s`, ou `True`/`False` para booleanos);
4. inclui funções auxiliares só quando o programa precisa delas:
   - `concatenar()` para `s + t` com strings;
   - `py_resto()` para `%`, porque em C `-7 % 3` é `-1` e em Python é `2`;
   - `py_print_float()` para imprimir float como o Python (`2.0`, `0.30000000000000004`, `1e+16`).

Literais float são escritos no C com a menor quantidade de dígitos que representa o valor exato (`3.14159265` continua `3.14159265`).

O código C é gerado **diretamente a partir da AST**, sem uma representação intermediária (TAC). Para o subconjunto escolhido, a AST já tem toda a informação necessária, e isso mantém o compilador menor e mais fácil de verificar.

## Limitações conhecidas

- Um parâmetro não pode receber tipos incompatíveis em chamadas diferentes (`f(1)` e `f("a")` é erro semântico). Inteiro e float no mesmo parâmetro viram `double`.
- Em C uma função tem um tipo só. Se `dobro(x)` é chamada com `3` e com `2.5`, `x` vira `double` e `dobro(3)` devolve `6.0` (Python devolveria `6`). O valor está certo, só o tipo muda.
- `%` só entre inteiros; `and`/`or`/`not` e as condições de `if`/`while` exigem boolean (`if x:` com inteiro é erro).
- `print` aceita um valor só.
- A impressão da AST na tela não indenta o conteúdo dos blocos (a estrutura está correta, só a visualização fica achatada).
- Não há `for`, listas, classes nem `import`.
