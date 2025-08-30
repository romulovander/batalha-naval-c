#include <stdio.h>

// ---------------------------------------------
// Batalha Naval — Nível Novato
// 0 = água, 3 = navio
// Tabuleiro 10x10, 2 navios de tamanho 3 (H e V)
// ---------------------------------------------

#define N 10
#define AGUA 0
#define NAVIO 3

typedef struct {
    int linha;
    int coluna;
    int comprimento; // tamanho fixo = 3
    char orientacao; // 'H' ou 'V'
} Navio;

void inicializarTabuleiro(int tab[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tab[i][j] = AGUA;
        }
    }
}

int dentroDosLimites(Navio n) {
    if (n.orientacao == 'H') {
        return n.linha >= 0 && n.linha < N &&
               n.coluna >= 0 && (n.coluna + n.comprimento - 1) < N;
    } else if (n.orientacao == 'V') {
        return n.coluna >= 0 && n.coluna < N &&
               n.linha >= 0 && (n.linha + n.comprimento - 1) < N;
    }
    return 0;
}

int podePosicionar(int tab[N][N], Navio n) {
    if (!dentroDosLimites(n)) return 0;

    if (n.orientacao == 'H') {
        for (int k = 0; k < n.comprimento; k++) {
            if (tab[n.linha][n.coluna + k] != AGUA) return 0;
        }
    } else { // 'V'
        for (int k = 0; k < n.comprimento; k++) {
            if (tab[n.linha + k][n.coluna] != AGUA) return 0;
        }
    }
    return 1;
}

void posicionarNavio(int tab[N][N], Navio n) {
    if (n.orientacao == 'H') {
        for (int k = 0; k < n.comprimento; k++) {
            tab[n.linha][n.coluna + k] = NAVIO;
        }
    } else { // 'V'
        for (int k = 0; k < n.comprimento; k++) {
            tab[n.linha + k][n.coluna] = NAVIO;
        }
    }
}

void imprimirTabuleiro(int tab[N][N]) {
    printf("   ");
    for (int j = 0; j < N; j++) printf("%2d ", j);
    printf("\n");

    printf("   ");
    for (int j = 0; j < N; j++) printf("---");
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%2d|", i);
        for (int j = 0; j < N; j++) {
            printf("%2d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int tabuleiro[N][N];
    inicializarTabuleiro(tabuleiro);

    Navio navioHorizontal = { .linha = 2, .coluna = 1, .comprimento = 3, 
.orientacao = 'H' };
    Navio navioVertical   = { .linha = 5, .coluna = 6, .comprimento = 3, 
.orientacao = 'V' };

    if (podePosicionar(tabuleiro, navioHorizontal)) {
        posicionarNavio(tabuleiro, navioHorizontal);
    } else {
        printf("[ERRO] Navio H não cabe/colide em (%d,%d)\n", 
navioHorizontal.linha, navioHorizontal.coluna);
    }

    if (podePosicionar(tabuleiro, navioVertical)) {
        posicionarNavio(tabuleiro, navioVertical);
    } else {
        printf("[ERRO] Navio V não cabe/colide em (%d,%d)\n", 
navioVertical.linha, navioVertical.coluna);
    }

    printf("\nTabuleiro (0 = água, 3 = navio)\n\n");
    imprimirTabuleiro(tabuleiro);
    return 0;
}


