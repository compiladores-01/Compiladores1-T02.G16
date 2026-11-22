![Compilador Python para C](docs/assets/img/python-c.jpg)

# Compilador Python → C

Projeto da disciplina **FGA0003 – Compiladores 1** (UnB/FCTE, 2026/2), turma T02, equipe G16.

O compilador lê um programa escrito em um **subconjunto de Python** e gera um programa **C** equivalente, que pode ser compilado com o `gcc`. Foi construído com **Flex** (análise léxica), **Bison** (análise sintática) e **C**.

**Equipe:** Fernanda Vaz · Manoel Castro · Cauã Clemente
**Documentação do projeto** (planejamento, sprints, atas, decisões, problemas): pasta [`docs/`](docs/)

---

## Exemplo

Entrada (`entrada.py`):

```python
x = 0
while x < 3:
    print(x)
    x = x + 1

def soma(a, b):
    return a + b

n = soma(55, 3)
if n > 4:
    print(n)
else:
    print(0)
```

Saída gerada (`saida.c`):

```c
int soma(int a, int b) {
    return (a + b);
}

int main(void) {
    int x = 0;
    int n = 0;
    x = 0;
    while ((x < 3)) {
        printf("%d\n", x);
        x = (x + 1);
    }
    n = soma(55, 3);
    if ((n > 4)) {
        printf("%d\n", n);
    } else {
        printf("%d\n", 0);
    }
    return 0;
}
```

---

## Como executar

### 1. Pré-requisitos

**Flex**, **Bison**, **GCC** e **Make**. No Ubuntu/Debian (ou WSL2 no Windows):

```bash
sudo apt-get update
sudo apt-get install flex bison build-essential
```

### 2. Clonar e compilar

```bash
git clone https://github.com/compiladores-01/Compiladores1-T02.G16.git
cd Compiladores1-T02.G16/compilador
make
```

Isso gera o executável `compilador-bin`.

### 3. Traduzir um programa Python para C

```bash
./compilador-bin entrada.py saida.c   # lê entrada.py e gera saida.c
gcc saida.c -o programa
./programa
```

Os dois argumentos são opcionais. Sem argumentos, o compilador lê da entrada padrão e gera `saida.c`:

```bash
echo 'print(1 + 2 * 3)' | ./compilador-bin
```

### 4. Rodar os testes

```bash
cd compilador
make test
```

A suíte roda os testes automáticos de cada etapa (lexer, parser, AST, tabela de símbolos e geração de código) e mostra `[OK]` ou `[FALHA]` para cada um. Detalhes em [`tests/README.md`](tests/README.md).

---

## Subconjunto de Python suportado

| Construção | Exemplo | Tradução em C |
|---|---|---|
| Inteiros, reais, strings, booleanos | `10`, `-5`, `2.5`, `"oi"`, `'oi'`, `True` | `int`, `double`, `const char *`, `int` (1/0, impresso como `True`/`False`) |
| Atribuição e expressões | `x = 1 + 2 * 3`, `-x` | `x = (1 + (2 * 3));` |
| Resto da divisão | `-7 % 3` | função auxiliar `py_resto()`, com o sinal igual ao do Python (`2`) |
| Comparações | `==` `!=` `<` `>` `<=` `>=` | mesmos operadores |
| Operadores lógicos | `and`, `or`, `not` | `&&`, `\|\|`, `!` (mesma precedência do Python) |
| Concatenação de strings | `s + " mundo"` | função auxiliar `concatenar()` |
| `print` | `print(x)` | `printf` com o formato do tipo; float impresso como o Python (`2.0`, `0.30000000000000004`) por `py_print_float()` |
| `if` / `elif` / `else` | blocos por **indentação** | `if { } else { if ... }` |
| `while` | blocos por **indentação** | `while { }` |
| Funções | `def f(a, b):` / `return` | função C antes do `main`, com tipos de parâmetros e retorno deduzidos |
| Comentários | `# ...` | ignorados |

Fora do escopo: classes, listas, `for`, `import`, exceções, `print` com vários valores.

---

## Pipeline

```text
programa.py
   │
   ▼  Flex  (compilador/lexer/lexer.l)
tokens  ── inclui INDENT / DEDENT para os blocos
   │
   ▼  Bison (compilador/parser/parser.y)
AST     (compilador/ast.c)
   │
   ▼  análise semântica + tabela de símbolos (compilador/tabela.c)
AST validada  ── tipos inferidos, variáveis verificadas
   │
   ▼  geração de código (compilador/geracao.c)
saida.c  ──►  gcc  ──►  executável
```

Explicação de cada etapa em [`compilador/README.md`](compilador/README.md).

---

## Estrutura do repositório

```text
.
├── compilador/          código-fonte do compilador
│   ├── lexer/lexer.l      analisador léxico (Flex)
│   ├── parser/parser.y    analisador sintático + ações semânticas (Bison)
│   ├── ast.c / ast.h      árvore sintática abstrata
│   ├── tabela.c / .h      tabela de símbolos
│   ├── geracao.c / .h     gerador de código C
│   ├── tipos.h            tipos de dados do compilador
│   ├── test_lexer.c       programa auxiliar que roda só o lexer (testes)
│   ├── entrada.py         programa de exemplo
│   └── Makefile
├── tests/               suíte de testes automáticos (make test)
├── docs/                site de documentação do projeto
└── README.md
```
