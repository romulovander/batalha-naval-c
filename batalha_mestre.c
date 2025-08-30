#include <stdio.h>

#define N 10
#define S 5
#define AGUA 0
#define NAVIO 3
#define HABIL 5

typedef struct {
    int linha, coluna, comprimento;
    char orientacao; /* 'H' horizontal, 'V' vertical, 'M' main diag, 'A' 
anti diag */
} Navio;

/* Board helpers */
void inicializarTabuleiro(int tab[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tab[i][j] = AGUA;
}

void dirDeOrientacao(char o, int *dr, int *dc) {
    switch (o) {
        case 'H': *dr = 0; *dc = 1; break;
        case 'V': *dr = 1; *dc = 0; break;
        case 'M': *dr = 1; *dc = 1; break;
        case 'A': *dr = 1; *dc = -1; break;
        default : *dr = 0; *dc = 0;  break;
    }
}

int dentroDosLimitesNavio(Navio n) {
    int dr, dc; dirDeOrientacao(n.orientacao, &dr, &dc);
    if (dr == 0 && dc == 0) return 0;
    for (int k = 0; k < n.comprimento; k++) {
        int r = n.linha + k * dr, c = n.coluna + k * dc;
        if (r < 0 || r >= N || c < 0 || c >= N) return 0;
    }
    return 1;
}

int podePosicionar(int tab[N][N], Navio n) {
    if (!dentroDosLimitesNavio(n)) return 0;
    int dr, dc; dirDeOrientacao(n.orientacao, &dr, &dc);
    for (int k = 0; k < n.comprimento; k++) {
        int r = n.linha + k * dr, c = n.coluna + k * dc;
        if (tab[r][c] != AGUA) return 0;
    }
    return 1;
}

void posicionarNavio(int tab[N][N], Navio n) {
    int dr, dc; dirDeOrientacao(n.orientacao, &dr, &dc);
    for (int k = 0; k < n.comprimento; k++) {
        int r = n.linha + k * dr, c = n.coluna + k * dc;
        tab[r][c] = NAVIO;
    }
}

void imprimirTabuleiro(int tab[N][N]) {
    printf("   "); for (int j = 0; j < N; j++) printf("%2d ", j); 
printf("\n");
    printf("   "); for (int j = 0; j < N; j++) printf("---");    
printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%2d|", i);
        for (int j = 0; j < N; j++) printf("%2d ", tab[i][j]);
        printf("\n");
    }
}

/* Skills 5x5 (built with loops + conditionals) */
void habilidadeCone(int H[S][S]) {
    int c = S / 2;
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            int cond = (i >= c) && (j >= c - (i - c)) && (j <= c + (i - 
c));
            H[i][j] = cond ? 1 : 0;
        }
    }
}

void habilidadeCruz(int H[S][S]) {
    int c = S / 2;
    for (int i = 0; i < S; i++)
        for (int j = 0; j < S; j++)
            H[i][j] = (i == c || j == c) ? 1 : 0;
}

void habilidadeOctaedro(int H[S][S]) {
    int c = S / 2;
    for (int i = 0; i < S; i++)
        for (int j = 0; j < S; j++) {
            int di = (i > c ? i - c : c - i);
            int dj = (j > c ? j - c : c - j);
            H[i][j] = (di + dj <= c) ? 1 : 0;
        }
}

/* Overlay centered at (origLinha, origColuna) */
void sobreporHabilidadeCentrada(int tab[N][N], int H[S][S], int origLinha, 
int origColuna) {
    int c = S / 2;
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            if (H[i][j] == 1) {
                int r = origLinha + (i - c);
                int col = origColuna + (j - c);
                if (r >= 0 && r < N && col >= 0 && col < N) {
                    if (tab[r][col] != NAVIO) tab[r][col] = HABIL;
                }
            }
        }
    }
}

int main(void) {
    int tab[N][N];
    inicializarTabuleiro(tab);

    Navio navios[] = {
        {2, 1, 3, 'H'},
        {5, 6, 3, 'V'},
        {0, 7, 3, 'M'},
        {7, 2, 3, 'A'}
    };
    int qtd = (int)(sizeof(navios) / sizeof(navios[0]));
    for (int i = 0; i < qtd; i++) {
        if (podePosicionar(tab, navios[i])) posicionarNavio(tab, 
navios[i]);
        else printf("[ERRO] Navio %d ori %c invalido em (%d,%d)\n",
                    i, navios[i].orientacao, navios[i].linha, 
navios[i].coluna);
    }

    int cone[S][S], cruz[S][S], octa[S][S];
    habilidadeCone(cone);
    habilidadeCruz(cruz);
    habilidadeOctaedro(octa);

    sobreporHabilidadeCentrada(tab, cone, 3, 4);
    sobreporHabilidadeCentrada(tab, cruz, 6, 3);
    sobreporHabilidadeCentrada(tab, octa, 4, 7);

    printf("\nTabuleiro (0=agua, 3=navio, 5=habilidade)\n\n");
    imprimirTabuleiro(tab);
    return 0;
}

