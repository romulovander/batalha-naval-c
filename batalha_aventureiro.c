#include <stdio.h>

#define N 10
#define AGUA 0
#define NAVIO 3

// Orientações:
// 'H' = horizontal (→)
// 'V' = vertical   (↓)
// 'M' = diagonal principal (↘)  [linha+1, col+1]
// 'A' = diagonal secundária (↙) [linha+1, col-1]
typedef struct {
    int linha, coluna, comprimento;
    char orientacao;
} Navio;

void inicializarTabuleiro(int tab[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tab[i][j] = AGUA;
}

void dirDeOrientacao(char o, int *dr, int *dc) {
    switch (o) {
        case 'H': *dr = 0; *dc = 1; break;
        case 'V': *dr = 1; *dc = 0; break;
        case 'M': *dr = 1; *dc = 1; break;   // ↘
        case 'A': *dr = 1; *dc = -1; break;  // ↙
        default : *dr = 0; *dc = 0; break;
    }
}

int dentroDosLimites(Navio n) {
    int dr, dc; dirDeOrientacao(n.orientacao, &dr, &dc);
    if (dr == 0 && dc == 0) return 0;
    for (int k = 0; k < n.comprimento; k++) {
        int r = n.linha + k * dr;
        int c = n.coluna + k * dc;
        if (r < 0 || r >= N || c < 0 || c >= N) return 0;
    }
    return 1;
}

int podePosicionar(int tab[N][N], Navio n) {
    if (!dentroDosLimites(n)) return 0;
    int dr, dc; dirDeOrientacao(n.orientacao, &dr, &dc);
    for (int k = 0; k < n.comprimento; k++) {
        int r = n.linha + k * dr;
        int c = n.coluna + k * dc;
        if (tab[r][c] != AGUA) return 0; // impede sobreposição
    }
    return 1;
}

void posicionarNavio(int tab[N][N], Navio n) {
    int dr, dc; dirDeOrientacao(n.orientacao, &dr, &dc);
    for (int k = 0; k < n.comprimento; k++) {
        int r = n.linha + k * dr;
        int c = n.coluna + k * dc;
        tab[r][c] = NAVIO;
    }
}

void imprimirTabuleiro(int tab[N][N]) {
    printf("   ");
    for (int j = 0; j < N; j++) printf("%2d ", j);
    printf("\n   ");
    for (int j = 0; j < N; j++) printf("---");
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%2d|", i);
        for (int j = 0; j < N; j++) printf("%2d ", tab[i][j]);
        printf("\n");
    }
}

int main(void) {
    int tabuleiro[N][N];
    inicializarTabuleiro(tabuleiro);

    // 4 navios (tamanho 3): 2 normais (H/V) + 2 diagonais (M/A)
    Navio navios[] = {
        {2, 1, 3, 'H'}, // horizontal →  (2,1)-(2,3)
        {5, 6, 3, 'V'}, // vertical   ↓  (5,6)-(7,6)
        {0, 7, 3, 'M'}, // diag ↘        (0,7)-(2,9)
        {7, 2, 3, 'A'}  // diag ↙        (7,2)-(9,0)
    };
    int qtd = (int)(sizeof(navios)/sizeof(navios[0]));

    for (int i = 0; i < qtd; i++) {
        if (podePosicionar(tabuleiro, navios[i])) {
            posicionarNavio(tabuleiro, navios[i]);
        } else {
            printf("[ERRO] Navio %d (ori %c) inválido em (%d,%d)\n",
                   i, navios[i].orientacao, navios[i].linha, 
navios[i].coluna);
        }
    }

    printf("\nTabuleiro (0 = água, 3 = navio)\n\n");
    imprimirTabuleiro(tabuleiro);
    return 0;
}

