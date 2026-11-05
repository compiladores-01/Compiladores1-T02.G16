# Testes do Compilador

Esta pasta contém os testes do compilador de subconjunto **Python para C**.

## Estrutura

```
tests/
├── lexer/                          ← testes do analisador léxico
│   ├── identificadores/
│   ├── numeros/
│   ├── strings/
│   ├── operadores/
│   ├── palavras_reservadas/
│   ├── comentarios/
│   ├── caracteres_invalidos/
│   └── strings_nao_terminadas/
├── parser/                         ← testes do analisador sintático
│   ├── atribuicao/
│   ├── print/
│   ├── if/
│   ├── while/
│   └── erros_sintaticos/
└── README.md
```

Cada pasta de teste contém:
- **`entrada.py`** — código Python para testar
- **`esperado.txt`** — saída esperada (formato simplificado)

## Como rodar os testes do lexer

```bash
cd tests
./run_lexer_tests.sh
```

O script:
1. Roda o `test_lexer` em cada `entrada.py` da pasta `lexer/`
2. Mostra a saída do lexer
3. Mostra a saída esperada (`esperado.txt`)

** Atenção:** O script **não compara automaticamente** — a comparação é visual. Você precisa olhar a saída do lexer e comparar com o `esperado.txt`.

## Como rodar os testes do parser

```bash
cd compilador
./compilador < ../tests/parser/atribuicao/entrada.py
```

**O que esperar:**
- Se o parser aceitar, não mostra nada (ou mostra `OK`)
- Se o parser rejeitar, mostra `Erro sintático`

## Limitações conhecidas

###  Strings com aspas simples NÃO são suportadas

O lexer atual só reconhece strings com **aspas duplas** (`"hello"`). Strings com **aspas simples** (`'hello'`) são tratadas como **caractere inválido** + `IDENTIFIER`.

**Exemplo:**

```python
'hello'
```

Saída do lexer:
```
Caractere inválido: '
Token: 258, Valor: 'hello', Linha: 1
Caractere inválido: '
```

**Isso é uma limitação conhecida** — o PR #25 tentou corrigir, mas não foi mesclado.

###  Strings não terminadas NÃO são detectadas

O lexer atual **não detecta** strings não terminadas. Em vez disso, trata a aspa como **caractere inválido** e o resto como `IDENTIFIER`.

**Exemplo:**

```python
print("hello
```

Saída do lexer:
```
Token: 264, Valor: 'print', Linha: 1
Token: 270, Valor: '(', Linha: 1
Caractere inválido: "
Token: 258, Valor: 'hello', Linha: 1
```

**Isso é uma limitação conhecida** — o PR #25 tentou corrigir, mas não foi mesclado.

### Operadores relacionais NÃO estão no escopo original

Os operadores `==`, `!=`, `<`, `>`, `<=`, `>=` foram adicionados no PR #30 (Fernanda), mas **não estão no escopo oficial** (issue #001). Eles são **essenciais** para `if` e `while` funcionarem.

### Booleanos usam `true`/`false` (minúsculo)

O lexer atual reconhece `true` e `false` (minúsculo). O padrão Python é `True` e `False` (maiúsculo). **Isso precisa ser corrigido.**

### Indentação NÃO está implementada

Python usa indentação para blocos. O compilador atual **não implementa** `INDENT`/`DEDENT` — em vez disso, usa `{ }` (como C). **Isso é uma simplificação.**

## Testes que falham (limitações conhecidas)

| Teste | Status | Motivo |
|-------|--------|--------|
| `lexer/strings` |  Falha | Aspas simples não são suportadas |
| `lexer/strings_nao_terminadas` |  Falha | Strings não terminadas não são detectadas |

## Testes que passam

| Teste | Status |
|-------|--------|
| `lexer/identificadores` |  OK |
| `lexer/numeros` |  OK |
| `lexer/operadores` |  OK |
| `lexer/palavras_reservadas` |  OK |
| `lexer/comentarios` |  OK |
| `lexer/caracteres_invalidos` |  OK |

## Testes da AST

Os testes da pasta `tests/ast/` verificam a impressão da Árvore Sintática Abstrata (AST).

| Teste | Status | Motivo |
|-------|--------|--------|
| `ast/atribuicao` |  OK | Atribuição simples funciona |
| `ast/precedencia` |  OK | Precedência de operadores funciona |
| `ast/print` |  Bug | As aspas da string aparecem duplicadas (`""hello""`) |
| `ast/if_falha` |  Falha | O parser atual não consegue ler o `if` (erro sintático) |

**Nota sobre o `if`:** O time declarou que a AST do `if` não foi implementada nesta versão. O teste `if_falha` serve como guia para a P2.

## Testes da Tabela de Símbolos

Os testes da pasta `tests/tabela/` verificam o comportamento da Tabela de Símbolos.

| Teste | Status | O que verifica |
|-------|--------|----------------|
| `tabela/insercao` |  OK | Inserção de variáveis (int, float, string) |
| `tabela/busca` |  OK | Busca e inferência de tipos |
| `tabela/redeclaracao` |  Limitação | O compilador não detecta redeclaração; ele apenas sobrescreve. |

## Próximos passos

1. **Corrigir strings:** suportar aspas simples, escapes e detectar strings não terminadas (o PR #25 tentou fazer isso)
2. **Corrigir booleanos:** usar `True`/`False` (maiúsculo)
3. **Implementar indentação:** `INDENT`/`DEDENT` para blocos Python
4. **Adicionar testes do parser:** automatizar a comparação

## Referências

- Issue #15 — Testar Lexer e tratar erros léxicos
- Issue #14 — Implementar analisador léxico com Flex
- `docs/tokens.md` — documentação dos tokens