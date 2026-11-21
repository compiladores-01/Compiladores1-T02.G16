#!/bin/bash
# Suite de testes automatica do compilador Python -> C.
#
# Uso (dentro de tests/):
#   bash run_tests.sh                 # roda todas as categorias
#   bash run_tests.sh lexer tabela    # roda so as categorias escolhidas
#
# Antes, construa o compilador:  cd ../compilador && make && make test_lexer
# (ou simplesmente:  cd ../compilador && make test)
#
# Cada teste e uma pasta com:
#   entrada.py        codigo Python de entrada
#   esperado.txt      saida esperada (comparada linha a linha)
#   FALHA_CONHECIDA   (opcional) motivo de uma limitacao conhecida; o teste
#                     roda, mas a falha nao conta como erro
#
# O que cada categoria compara:
#   lexer    saida do test_lexer (um token por linha)
#   parser   saida do compilador-bin (stdout + stderr)
#   ast      idem
#   tabela   idem
#   geracao  saida do PROGRAMA C gerado, compilado com gcc e executado

cd "$(dirname "$0")" || exit 1
TESTS_DIR=$(pwd)
COMP_DIR="$TESTS_DIR/../compilador"
COMPILADOR="${COMPILADOR:-$COMP_DIR/compilador-bin}"
TEST_LEXER="${TEST_LEXER:-$COMP_DIR/test_lexer}"

CATEGORIAS="$*"
[ -z "$CATEGORIAS" ] && CATEGORIAS="lexer parser ast tabela geracao"

TMP=$(mktemp -d)
trap 'rm -rf "$TMP"' EXIT

passou=0; falhou=0; conhecidas=0

rodar_compilador() {   # $1 = entrada.py ; roda numa pasta temporaria (gera saida.c)
    ( cd "$TMP" && rm -f saida.c && "$COMPILADOR" < "$1" 2>&1 )
}

for cat in $CATEGORIAS; do
    [ -d "$cat" ] || continue
    echo "== $cat"
    for dir in "$cat"/*/; do
        dir=${dir%/}
        [ -f "$dir/entrada.py" ] || continue
        entrada="$TESTS_DIR/$dir/entrada.py"
        obtido="$TMP/obtido.txt"

        case "$cat" in
            lexer)
                "$TEST_LEXER" < "$entrada" > "$obtido" 2>&1 ;;
            geracao)
                : > "$obtido"
                if rodar_compilador "$entrada" > /dev/null \
                   && gcc -o "$TMP/prog" "$TMP/saida.c" 2> "$TMP/gcc.log"; then
                    "$TMP/prog" > "$obtido" 2>&1
                else
                    echo "(nao compilou)" > "$obtido"
                    cat "$TMP/gcc.log" >> "$obtido" 2>/dev/null
                fi ;;
            *)
                rodar_compilador "$entrada" > "$obtido" ;;
        esac

        if diff -q "$dir/esperado.txt" "$obtido" > /dev/null 2>&1; then
            echo "  [OK]        $dir"
            passou=$((passou+1))
        elif [ -f "$dir/FALHA_CONHECIDA" ]; then
            echo "  [CONHECIDA] $dir -- $(head -n1 "$dir/FALHA_CONHECIDA")"
            conhecidas=$((conhecidas+1))
        else
            echo "  [FALHA]     $dir"
            diff "$dir/esperado.txt" "$obtido" | sed 's/^/                /'
            falhou=$((falhou+1))
        fi
    done
done

echo "-----"
echo "$passou passaram, $falhou falharam, $conhecidas falhas conhecidas"
[ "$falhou" -eq 0 ]
