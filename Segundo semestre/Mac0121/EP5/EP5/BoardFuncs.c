/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include "BoardFuncs.h"
#include "auxfuncs.h"

/*Biblioteca de funções que implementam o tabuleiro e ajudam a manuseá-lo*/

/*Recebe os números "m" e "n" e retrona um ponteiro para um novo tabuleiro
com "m" linhas e "n" colunas*/
BTile **BoardCreate (int m, int n) {
    const char errmsg[] = "Erro ao criar o tabuleiro";
    BTile **mat;
    int i, j;
    mat = emalloc(m*sizeof(BTile*), errmsg);
    for (i = 0; i < m; i++)
        mat[i] = emalloc(n*sizeof(BTile), errmsg);
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j].lin = i;
            mat[i][j].col = j;
            mat[i][j].color = '-';
            mat[i][j].Neigh = emalloc(6*sizeof(BTile*), errmsg);
            mat[i][j].weights = emalloc(2*sizeof(int), errmsg);
            mat[i][j].weights[0] = 4;
            mat[i][j].weights[1] = 4;
            if (j + 1 < N) {
                mat[i][j].Neigh[5] = &(mat[i][j+1]);
                if (i - 1 >= 0)
                    mat[i][j].Neigh[0] = &(mat[i-1][j+1]);
                else
                    mat[i][j].Neigh[0] = NULL;
            }
            else {
                mat[i][j].Neigh[5] = NULL;
                mat[i][j].Neigh[0] = NULL;
            }
            if (i + 1 < N)
                mat[i][j].Neigh[4] = &(mat[i+1][j]);
            else
                mat[i][j].Neigh[4] = NULL;
            if (j - 1 >= 0) {
                mat[i][j].Neigh[2] = &(mat[i][j-1]);
                if (i + 1 < N)
                    mat[i][j].Neigh[3] = &(mat[i+1][j-1]);
                else
                    mat[i][j].Neigh[3] = NULL;
            }
            else {
                mat[i][j].Neigh[2] = NULL;
                mat[i][j].Neigh[3] = NULL;
            }
            if (i - 1 >= 0)
                mat[i][j].Neigh[1] = &(mat[i-1][j]);
            else
                mat[i][j].Neigh[1] = NULL;
        }
    }
    return mat;
}

/*Desaloca um tabuleiro "board" com "m" linhas e "n" colunas*/
void freeBoard (BTile **board, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            free(board[i][j].Neigh);
            free(board[i][j].weights);
        }
        free(board[i]);
    }
    free(board);
}

/*Imprime o tabuleiro "board"*/
void printGame (BTile **board) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < i; j++)
            fprintf(stderr, " ");
        for (j = 0; j < N; j++)
            fprintf(stderr, "%c%c", board[i][j].color, "\n "[j != N-1]);
    }
}

/*Recebe o tabuleiro "board", uma posição ("lin","col") e um argumento "print"
e retorna 1 se a posição pertence ao tabuleiro e não está ocupada ou 0 caso
contrário. Caso "print" for 1 e a função for retornar 0, imprime uma mensagem
de erro*/
int isValid (BTile **board, int lin, int col, int print) {
    if (lin >= 0 && lin < N && col >= 0 && col < N) {
        if (board[lin][col].color == '-')
            return 1;
        if (print)
            fprintf(stderr, "A posição escolhida já está ocupada. Faça outra jogada.\n");
        return 0;
    }
    if (print)
        fprintf(stderr, "A posição escolhida não está no tabuleiro. Faça outra jogada.\n");
    return 0;
}

/*Função recursiva auxiliar à getWinner que recebe o tabuleiro "board",
uma matriz de posições já visitadas "used", uma posição ("lin","col") e
uma cor "color" e devolve 1 se foi achado um caminho vencedor de peças da cor
"color" ou 0 caso contrário*/
int search (BTile **board, int **used, int lin, int col, char color) {
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
    if (board[lin][col].color == color && color == 'b' && lin == N-1)
        return 1;
    if (board[lin][col].color == color && color == 'p' && col == N-1)
        return 1;
    if (board[lin][col].color == color && used[lin][col] == 0) {
        used[lin][col] = 1;
        if (board[lin][col].Neigh[0] != NULL)
            s1 = search(board, used, lin-1, col+1, color);
        if (board[lin][col].Neigh[1] != NULL)
            s2 = search(board, used, lin-1, col, color);
        if (board[lin][col].Neigh[2] != NULL)
            s3 = search(board, used, lin, col-1, color);
        if (board[lin][col].Neigh[3] != NULL)
            s4 = search(board, used, lin+1, col-1, color);
        if (board[lin][col].Neigh[4] != NULL)
            s5 = search(board, used, lin+1, col, color);
        if (board[lin][col].Neigh[5] != NULL)
            s6 = search(board, used, lin, col+1, color);
        return (s1 | s2 | s3 | s4 | s5 | s6);
    }
    return 0;
}

/*Recebe o tabuleiro "board" e retorna 0 se ningém venceu, 1 se as peças
brancas venceram ou 2 se as peças pretas venceram*/
int getWinner (BTile **board) {
    int i, j;
    int **used;
    used = criaMatriz(N, N);
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            used[i][j] = 0;
    for (i = 0; i < N; i++) {
        if (search(board, used, 0, i, 'b')) {
            freeMatriz(used, N);
            return 1;
        }
        if (search(board, used, i, 0, 'p')) {
            freeMatriz(used, N);
            return 2;
        }
    }
    freeMatriz(used, N);
    return 0;
}

/*Recebe o tabuleiro "board" e uma posição ("lin","col") e atualiza os pesos
ao redor dessa posição*/
void updateWeights (BTile **board, int lin, int col) {
    int i;
    if (board[lin][col].color == 'b') {
        board[lin][col].weights[0] = INF;
        board[lin][col].weights[1] = 0;
        for (i = 0; i < 6; i++)
            if (board[lin][col].Neigh[i] != NULL)
                if (board[lin][col].Neigh[i]->color != 'p') {
                    if (board[lin][col].Neigh[i]->weights[0] < 8)
                        board[lin][col].Neigh[i]->weights[0] += 2;
                    if (board[lin][col].Neigh[i]->weights[1] > 0)
                        board[lin][col].Neigh[i]->weights[1] -= 2;
                }
    }
    if (board[lin][col].color == 'p') {
        board[lin][col].weights[0] = 0;
        board[lin][col].weights[1] = INF;
        for (i = 0; i < 6; i++)
            if (board[lin][col].Neigh[i] != NULL)
                if (board[lin][col].Neigh[i]->color != 'b') {
                    if (board[lin][col].Neigh[i]->weights[0] > 0)
                        board[lin][col].Neigh[i]->weights[0] -= 2;
                    if (board[lin][col].Neigh[i]->weights[1] < 8)
                        board[lin][col].Neigh[i]->weights[1] += 2;
                }
    }
}
