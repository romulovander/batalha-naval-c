# Batalha Naval em C — Novato, Aventureiro e Mestre

Projeto didático em C para praticar **vetores, matrizes, loops e 
condicionais**.

- `0` = água  
- `3` = navio  
- `5` = área de habilidade (nível Mestre)

## Como compilar e executar

### Nível Novato
Tabuleiro 10x10 e **2 navios** (tamanho 3): 1 horizontal e 1 vertical.
```bash
clang -Wall -Wextra -O2 batalha_novato.c -o batalha_novato
./batalha_novato
```

### Nível Aventureiro
Tabuleiro 10x10 e **4 navios** (tamanho 3): 2 H/V + **2 diagonais**.
```bash
clang -Wall -Wextra -O2 batalha_aventureiro.c -o batalha_aventureiro
./batalha_aventureiro
```

### Nível Mestre
Habilidades com **matrizes 5x5** e **sobreposição centrada** no tabuleiro:
- Cone (abre para baixo), Cruz e Octaedro (losango).
```bash
clang -Wall -Wextra -O2 batalha_mestre.c -o batalha_mestre
./batalha_mestre
```

