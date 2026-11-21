# Testes do Compilador

Esta pasta contém os testes do compilador de subconjunto **Python para C**.
A suíte é **automática**: o script roda cada teste, compara a saída real com a esperada e mostra `[OK]` ou `[FALHA]` (com o `diff`).

## Como rodar

```bash
cd compilador
make test
```

O `make test` constrói o `compilador-bin` e o `test_lexer`, depois roda a suíte inteira. Também dá para rodar direto:

```bash
cd compilador && make && make test_lexer
cd ../tests
bash run_tests.sh                 # todas as categorias
bash run_tests.sh lexer tabela    # só as categorias escolhidas
```

Saída esperada hoje:

```
24 passaram, 0 falharam, 1 falhas conhecidas
```

## Estrutura

Cada teste é uma pasta com:

| Arquivo | Para que serve |
|---|---|
| `entrada.py` | código Python de entrada |
| `esperado.txt` | saída esperada, comparada linha a linha |
| `FALHA_CONHECIDA` | *(opcional)* motivo de uma limitação conhecida. O teste roda, mas a falha não conta como erro |

O que cada categoria compara:

| Categoria | O que roda | O que compara |
|---|---|---|
| `lexer/` | `test_lexer` | um token por linha, ex.: `IDENTIFIER(x)`, `PLUS`, `INDENT` |
| `parser/` | `compilador-bin` | saída completa (stdout + stderr) |
| `ast/` | `compilador-bin` | a AST impressa como código, com parênteses mostrando a estrutura |
| `tabela/` | `compilador-bin` | tabela de símbolos e erros semânticos |
| `geracao/` | `compilador-bin` → `gcc` → programa | a saída do **programa C gerado** quando executado (teste ponta a ponta) |

## Testes

### Lexer (`tests/lexer/`)

| Teste | Status | O que verifica |
|---|---|---|
| `identificadores` | ✅ | nomes de variáveis, inclusive com `_` e dígitos |
| `numeros` | ✅ | inteiros (`NUMBER`) e reais (`FLOAT`) |
| `operadores` | ✅ | aritméticos e relacionais |
| `palavras_reservadas` | ✅ | `print`, `if`, `else`, `while`, `def`, `return` |
| `booleanos` | ✅ | `True` / `False` (padrão Python, maiúsculo) |
| `strings` | ✅ | aspas duplas **e simples** |
| `comentarios` | ✅ | `#` até o fim da linha é ignorado |
| `caracteres_invalidos` | ✅ | `@` gera erro léxico e a análise continua |
| `indentacao` | ✅ | geração de `INDENT` / `DEDENT`, inclusive dois níveis |
| `strings_nao_terminadas` | ⚠️ conhecida | `print("hello` deveria dar erro de string não terminada |

### Parser (`tests/parser/`)

| Teste | Status | O que verifica |
|---|---|---|
| `atribuicao` | ✅ | `x = 10` |
| `print` | ✅ | `print(1)` |
| `if` | ✅ | `if` / `else` com blocos por indentação |
| `while` | ✅ | `while` com bloco por indentação |
| `def` | ✅ | definição de função, `return` e chamada |
| `erros_sintaticos` | ✅ | `x =` incompleto gera erro sintático |

### AST (`tests/ast/`)

| Teste | Status | O que verifica |
|---|---|---|
| `atribuicao` | ✅ | nó de atribuição |
| `precedencia` | ✅ | `1 + 2 * 3` vira `(1 + (2 * 3))`: a multiplicação fica mais embaixo na árvore |
| `print` | ✅ | string sem aspas duplicadas |
| `if` | ✅ | nó `if` com condição e ramo `else` |

### Tabela de Símbolos (`tests/tabela/`)

| Teste | Status | O que verifica |
|---|---|---|
| `insercao` | ✅ | inserção de variáveis `INTEIRO`, `FLOAT` e `STRING` |
| `busca` | ✅ | busca e inferência de tipo (`y = x + 5` → `INTEIRO`) |
| `erro_tipo` | ✅ | barra `x = 10` seguido de `x = "texto"` |
| `nao_declarada` | ✅ | barra o uso de variável antes de ser definida |
| `redeclaracao` | ✅ | `x = 10; x = 20` é **reatribuição válida** em Python, não um erro |

### Geração de código (`tests/geracao/`)

Testes ponta a ponta: o código Python é traduzido para C, compilado com `gcc` e executado. Compara a saída do programa. Ver PR `fix/geracao-tipo-variaveis`.

## Limitações conhecidas

- **String não terminada:** `print("hello` não gera erro de string não terminada. A aspa vira "caractere inválido" e `hello` vira identificador.
- **Impressão da AST sem indentação:** o conteúdo dos blocos `if`/`while`/`def` é impresso sem recuo. A estrutura está correta, só a visualização fica achatada.

## Adicionando um teste novo

1. Crie uma pasta dentro da categoria, ex.: `tests/parser/meu_teste/`
2. Escreva o `entrada.py`
3. Gere a saída e **confira se ela está certa** antes de salvar como esperada:
   ```bash
   cd compilador
   ./compilador-bin < ../tests/parser/meu_teste/entrada.py
   # (lexer: ./test_lexer < ...)
   ```
4. Salve como `esperado.txt` e rode `bash run_tests.sh`.

## Referências

- `docs/tokens.md` — documentação dos tokens
- Issue #35 — testes da Tabela de Símbolos
