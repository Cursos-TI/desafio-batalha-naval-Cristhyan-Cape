#include <stdio.h>
#include <stdlib.h> // Para a função abs()

// Definições de constantes para o tabuleiro e elementos
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Definições para as matrizes de habilidade
#define TAMANHO_HABILIDADE_CONE 5
#define TAMANHO_HABILIDADE_CRUZ 5
#define TAMANHO_HABILIDADE_OCTAEDRO 5

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, int horizontal) {
    if (horizontal) {
        if (coluna + tamanho <= TAMANHO_TABULEIRO) {
            for (int i = 0; i < tamanho; i++) {
                tabuleiro[linha][coluna + i] = NAVIO;
            }
            printf("Navio horizontal posicionado em (%c%d) a (%c%d).\n",
                   'A' + coluna, linha + 1, 'A' + coluna + tamanho - 1, linha + 1);
        } else {
            printf("Erro ao posicionar navio horizontal.\n");
        }
    } else {
        if (linha + tamanho <= TAMANHO_TABULEIRO) {
            for (int i = 0; i < tamanho; i++) {
                tabuleiro[linha + i][coluna] = NAVIO;
            }
            printf("Navio vertical posicionado em (%c%d) a (%c%d).\n",
                   'A' + coluna, linha + 1, 'A' + coluna, linha + tamanho);
        } else {
            printf("Erro ao posicionar navio vertical.\n");
        }
    }
}

// Função para criar a matriz de habilidade em Cone
void criarHabilidadeCone(int habilidade[][TAMANHO_HABILIDADE_CONE]) {
    int centro = TAMANHO_HABILIDADE_CONE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE_CONE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_CONE; j++) {
            if (i >= centro && j >= centro - (i - centro) && j <= centro + (i - centro)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em Cruz
void criarHabilidadeCruz(int habilidade[][TAMANHO_HABILIDADE_CRUZ]) {
    int centro = TAMANHO_HABILIDADE_CRUZ / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE_CRUZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_CRUZ; j++) {
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz de habilidade em Octaedro (Losango)
void criarHabilidadeOctaedro(int habilidade[][TAMANHO_HABILIDADE_OCTAEDRO]) {
    int centro = TAMANHO_HABILIDADE_OCTAEDRO / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE_OCTAEDRO; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_OCTAEDRO; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Função para aplicar a habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[][TAMANHO_TABULEIRO], int habilidade[][5], int tamanho_habilidade, int linha_origem, int coluna_origem) {
    int centro_habilidade = tamanho_habilidade / 2;
    for (int i = 0; i < tamanho_habilidade; i++) {
        for (int j = 0; j < tamanho_habilidade; j++) {
            if (habilidade[i][j] == 1) {
                int linha_tabuleiro = linha_origem + (i - centro_habilidade);
                int coluna_tabuleiro = coluna_origem + (j - centro_habilidade);
                if (linha_tabuleiro >= 0 && linha_tabuleiro < TAMANHO_TABULEIRO &&
                    coluna_tabuleiro >= 0 && coluna_tabuleiro < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linha_tabuleiro][coluna_tabuleiro] != NAVIO) {
                        tabuleiro[linha_tabuleiro][coluna_tabuleiro] = HABILIDADE;
                    }
                }
            }
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[][TAMANHO_TABULEIRO]) {
    printf("\n  ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            switch (tabuleiro[i][j]) {
                case AGUA:
                    printf(". ");
                    break;
                case NAVIO:
                    printf("N ");
                    break;
                case HABILIDADE:
                    printf("H ");
                    break;
                default:
                    printf("? "); // Para casos inesperados
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Representação do tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // --- Posicionamento dos Navios ---
    posicionarNavio(tabuleiro, 2, 1, TAMANHO_NAVIO, 1); // Navio horizontal 1
    posicionarNavio(tabuleiro, 6, 3, TAMANHO_NAVIO, 0); // Navio vertical 2
    posicionarNavio(tabuleiro, 8, 6, TAMANHO_NAVIO, 1); // Navio horizontal 3

    printf("\nTabuleiro com navios posicionados:\n");
    exibirTabuleiro(tabuleiro);

    // --- Criação das Matrizes de Habilidade ---
    int habilidadeCone[TAMANHO_HABILIDADE_CONE][TAMANHO_HABILIDADE_CONE];
    criarHabilidadeCone(habilidadeCone);
    printf("Matriz de habilidade Cone:\n");
    for (int i = 0; i < TAMANHO_HABILIDADE_CONE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_CONE; j++) {
            printf("%d ", habilidadeCone[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int habilidadeCruz[TAMANHO_HABILIDADE_CRUZ][TAMANHO_HABILIDADE_CRUZ];
    criarHabilidadeCruz(habilidadeCruz);
    printf("Matriz de habilidade Cruz:\n");
    for (int i = 0; i < TAMANHO_HABILIDADE_CRUZ; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_CRUZ; j++) {
            printf("%d ", habilidadeCruz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int habilidadeOctaedro[TAMANHO_HABILIDADE_OCTAEDRO][TAMANHO_HABILIDADE_OCTAEDRO];
    criarHabilidadeOctaedro(habilidadeOctaedro);
    printf("Matriz de habilidade Octaedro:\n");
    for (int i = 0; i < TAMANHO_HABILIDADE_OCTAEDRO; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE_OCTAEDRO; j++) {
            printf("%d ", habilidadeOctaedro[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // --- Aplicação das Habilidades ao Tabuleiro ---
    // Habilidade Cone
    int linha_cone = 1;
    int coluna_cone = 1;
    printf("Aplicando habilidade Cone no ponto (%c%d):\n", 'A' + coluna_cone, linha_cone + 1);
    aplicarHabilidade(tabuleiro, habilidadeCone, TAMANHO_HABILIDADE_CONE, linha_cone, coluna_cone);
    exibirTabuleiro(tabuleiro);

    // Habilidade Cruz
    int linha_cruz = 5;
    int coluna_cruz = 5;
    printf("Aplicando habilidade Cruz no ponto (%c%d):\n", 'A' + coluna_cruz, linha_cruz + 1);
    aplicarHabilidade(tabuleiro, habilidadeCruz, TAMANHO_HABILIDADE_CRUZ, linha_cruz, coluna_cruz);
    exibirTabuleiro(tabuleiro);

    // Habilidade Octaedro
    int linha_octaedro = 3;
    int coluna_octaedro = 7;
    printf("Aplicando habilidade Octaedro no ponto (%c%d):\n", 'A' + coluna_octaedro, linha_octaedro + 1);
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, TAMANHO_HABILIDADE_OCTAEDRO, linha_octaedro, coluna_octaedro);
    exibirTabuleiro(tabuleiro);

    return 0;
}
