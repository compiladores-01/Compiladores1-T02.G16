#!/bin/bash
# Testes ponta a ponta: Python -> C -> executavel -> compara a saida.
# Uso (dentro de tests/): ./run_geracao_tests.sh
# Requer o compilador ja construido: cd ../compilador && make

COMPILADOR="${COMPILADOR:-$(cd "$(dirname "$0")/../compilador" && pwd)/compilador-bin}"
TMP=$(mktemp -d)
passou=0; falhou=0

for dir in "$(dirname "$0")"/geracao/*/; do
    nome=$(basename "$dir")
    [ -f "$dir/entrada.py" ] || continue
    ( cd "$TMP" && "$COMPILADOR" < "$OLDPWD/$dir/entrada.py" > /dev/null 2>&1 ) \
        && gcc -o "$TMP/prog" "$TMP/saida.c" 2> "$TMP/gcc.log" \
        && "$TMP/prog" > "$TMP/obtido.txt"
    if diff -q "$TMP/obtido.txt" "$dir/esperado.txt" > /dev/null 2>&1; then
        echo "[OK]    $nome"; passou=$((passou+1))
    else
        echo "[FALHA] $nome"; falhou=$((falhou+1))
        diff "$dir/esperado.txt" "$TMP/obtido.txt" 2>/dev/null | sed 's/^/        /'
    fi
    rm -f "$TMP/saida.c" "$TMP/prog" "$TMP/obtido.txt"
done

rm -rf "$TMP"
echo "-----"
echo "$passou passaram, $falhou falharam"
[ "$falhou" -eq 0 ]
