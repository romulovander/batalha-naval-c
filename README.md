# Batalha Naval em C — Nível Novato

Tabuleiro 10x10 com 2 navios de tamanho 3 (1 horizontal e 1 vertical).
Valores: 0 = água, 3 = navio.

## Como compilar
clang -Wall -Wextra -O2 batalha_novato.c -o batalha_novato

## Como executar
./batalha_novato

## Observações
- Coordenadas dos navios estão no main (navioHorizontal/navioVertical).
- Há validação de limites e sobreposição.
