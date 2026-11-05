#!/bin/bash

# Script para rodar os testes do lexer
# Uso: ./run_lexer_tests.sh

TEST_LEXER="../compilador/test_lexer"

echo "=========================================="
echo "  TESTES DO LEXER"
echo "=========================================="

for dir in lexer/*/; do
    nome=$(basename "$dir")
    entrada="$dir/entrada.py"
    esperado="$dir/esperado.txt"

    if [ ! -f "$entrada" ]; then
        continue
    fi

    echo ""
    echo "=========================================="
    echo "  TESTE: $nome"
    echo "=========================================="
    echo ""
    echo "--- Entrada ($entrada) ---"
    cat "$entrada"
    echo ""
    echo "--- Saída do lexer ---"
    $TEST_LEXER < "$entrada"
    echo ""
    echo "--- Esperado ($esperado) ---"
    cat "$esperado"
    echo ""
done

echo ""
echo "=========================================="
echo "  FIM DOS TESTES"
echo "=========================================="
