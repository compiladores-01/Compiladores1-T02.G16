#!/bin/bash
# Mantido por compatibilidade: agora a suite e automatica.
# Use:  bash run_tests.sh            (todas as categorias)
#       bash run_tests.sh lexer      (so o lexer)
exec bash "$(dirname "$0")/run_tests.sh" lexer
