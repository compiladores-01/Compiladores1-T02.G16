![](docs/assets/ptoc.jpg)

## Introdução

Bem-vindo ao repositório do projeto de **Compiladores 1** da Universidade de Brasília.

O projeto aborda os fundamentos e os mecanismos envolvidos na construção de compiladores: análise léxica, análise sintática, representação intermediária, análise semântica e geração de código. Como aplicação prática, a equipe desenvolve um compilador de um subconjunto de `Python` para `C`, utilizando **Flex** e **Bison**.



## Como Executar

### 1. Clonar o repositório

```bash
git clone https://github.com/Fernandavazgit1/-FGA0003Compiladores1-T02.G16.git
cd -FGA0003Compiladores1-T02.G16
```

### 2. Instalar dependências

É necessário ter **Flex**, **Bison** e **GCC** instalados.

Em distribuições Linux baseadas em Debian/Ubuntu:

```bash
sudo apt-get update
sudo apt-get install flex bison build-essential
```

No Windows, recomenda-se utilizar **WSL2** ou **MSYS2 MinGW64**.

### 3. Compilar o compilador

No terminal com Flex, Bison, GCC e Make instalados, execute:

```bash
cd compilador
make
```

O executável gerado é `compilador-bin`.

### 4. Testar com um programa de entrada

```bash
./compilador-bin entrada.py saida.c
```

O compilador analisa `entrada.py` e gera o código C em `saida.c`. Para compilar e executar esse código:

```bash
gcc saida.c -o saida_prog
./saida_prog
```

Também é possível testar outra entrada, passando os caminhos como argumentos:

```bash
./compilador-bin caminho/para/programa.py caminho/para/saida.c
```

No Windows, use o terminal do WSL2 ou o terminal MinGW64 do MSYS2 para executar esses comandos.

## Estado Atual

O compilador implementa um subconjunto de Python, incluindo variáveis, expressões, impressão, condicionais, laços e funções, com análise semântica e geração de código C.



## Pipeline do Compilador

```text
programa.py -> Flex -> tokens -> Bison -> AST -> análise semântica -> código C
```

## Melhorias Planejadas

- ampliar o conjunto de tokens reconhecidos;
- implementar variáveis e atribuições;
- adicionar estruturas `if`, `else` e `while`;
- construir e percorrer a AST;
- implementar tabela de símbolos e checagens semânticas;
- gerar arquivos `.c` a partir da AST ou de uma representação intermediária;
- adicionar testes automatizados;
- documentar decisões técnicas, problemas e soluções.

## Organização da Equipe

As atividades são organizadas em sprints, com acompanhamento no GitHub e na documentação do projeto. As páginas de planejamento, atas, atividades semanais e decisões técnicas estão disponíveis no site MkDocs.
![Logo do Projeto](C:\Users\euoid\Documents\compiladores\-FGA0003Compiladores1-T02.G16\docs\assets\ptoc.jpg)
