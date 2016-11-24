#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INF 1073741824

typedef struct btile_t {
    int lin, col;
    char color;
    struct btile_t **Neigh;
    int **weights;
} BTile;

typedef struct pos_t {
    int lin, col;
    char color;
} Pos;

typedef struct pathnode_t {
    int lin, col;
    char color;
    struct pathnode_t *next;
} PNode;

typedef PNode* Path;

void *emalloc (size_t size, const char *msg) {
    int *Ret;
    Ret = malloc(size);
    if (Ret == NULL) {
        fprintf(stderr, "%s", msg);
        exit(1);
    }
    return Ret;
}

int **criaMatriz (int m, int n){
    int **mat;
    int i, j;
    mat = malloc(m*sizeof(int*));
    if (mat == NULL){
        free(mat);
        exit(1);
    }
    for (i = 0; i < m; i++){
        mat[i] = malloc(n*sizeof(int));
        if (mat[i] == NULL){
            for (j = 0; j <= i; j++)
                free(mat[j]);
            free(mat);
            exit(1);
        }
    }
    return mat;
}

void freeMatriz (int **mat, int m){
    int i;
    for (i = 0; i < m; i++)
        free(mat[i]);
    free(mat);
}

BTile **criaTabuleiro (int m, int n){
    const char errmsg[] = "Erro ao criar o tabuleiro";
    BTile **mat;
    int i, j, k;
    mat = emalloc(m*sizeof(BTile*), errmsg);
    for (i = 0; i < m; i++){
        mat[i] = emalloc(n*sizeof(BTile), errmsg);
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j].lin = i;
            mat[i][j].col = j;
            mat[i][j].color = '-';
            mat[i][j].Neigh = emalloc(6*sizeof(BTile*), errmsg);
            mat[i][j].weights = emalloc(6*sizeof(int*), errmsg);
            for (k = 0; k < 6; k++)
                mat[i][j].weights[k] = emalloc(2*sizeof(int), errmsg);
            if (j + 1 < 14) {
                mat[i][j].Neigh[5] = &(mat[i][j+1]);
                mat[i][j].weights[5][0] = 4;
                mat[i][j].weights[5][1] = 4;
                if (i - 1 >= 0) {
                    mat[i][j].Neigh[4] = &(mat[i-1][j+1]);
                    mat[i][j].weights[4][0] = 4;
                    mat[i][j].weights[4][1] = 4;
                }
                else {
                    mat[i][j].Neigh[4] = NULL;
                    mat[i][j].weights[4][0] = INF;
                    mat[i][j].weights[4][1] = 2;
                }
            }
            else {
                mat[i][j].Neigh[5] = NULL;
                mat[i][j].weights[5][0] = 2;
                mat[i][j].weights[5][1] = INF;
                mat[i][j].Neigh[4] = NULL;
                mat[i][j].weights[4][0] = INF;
                mat[i][j].weights[4][1] = 2;
            }
            if (i + 1 < 14) {
                mat[i][j].Neigh[0] = &(mat[i+1][j]);
                mat[i][j].weights[0][0] = 4;
                mat[i][j].weights[0][1] = 4;
            }
            else {
                mat[i][j].Neigh[0] = NULL;
                mat[i][j].weights[0][0] = INF;
                mat[i][j].weights[0][1] = 2;
            }
            if (j - 1 >= 0) {
                mat[i][j].Neigh[2] = &(mat[i][j-1]);
                mat[i][j].weights[2][0] = 4;
                mat[i][j].weights[2][1] = 4;
                if (i + 1 < 14) {
                    mat[i][j].Neigh[1] = &(mat[i+1][j-1]);
                    mat[i][j].weights[1][0] = 4;
                    mat[i][j].weights[1][1] = 4;
                }
                else {
                    mat[i][j].Neigh[1] = NULL;
                    mat[i][j].weights[1][0] = INF;
                    mat[i][j].weights[1][1] = 2;
                }
            }
            else {
                mat[i][j].Neigh[2] = NULL;
                mat[i][j].weights[2][0] = INF;
                mat[i][j].weights[2][1] = 2;
                mat[i][j].Neigh[1] = NULL;
                mat[i][j].weights[1][0] = 2;
                mat[i][j].weights[1][1] = INF;
            }
            if (i - 1 >= 0) {
                mat[i][j].Neigh[3] = &(mat[i-1][j]);
                mat[i][j].weights[3][0] = 4;
                mat[i][j].weights[3][1] = 4;
            }
            else {
                mat[i][j].Neigh[3] = NULL;
                mat[i][j].weights[3][0] = INF;
                mat[i][j].weights[3][1] = 2;
            }
        }
    }
    return mat;
}

void freeBo (BTile **mat, int m, int n){
    int i, j, k;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < 6; k++)
                free(mat[i][j].weights[k]);
            free(mat[i][j].Neigh);
            free(mat[i][j].weights);
        }
        free(mat[i]);
    }
    free(mat);
}

void printGame (BTile **tab) {
    int i, j;
    for (i = 15; i >= 0; i--)
        fprintf(stderr, " ");
    for (i = 0; i < 14; i++)
        fprintf(stderr, "%d ", i%10);
    fprintf(stderr, "\n");
    for (i = 13; i >= 0; i--) {
        for (j = 0; j < i-i/10; j++)
            fprintf(stderr, " ");
        fprintf(stderr, "%d ", i);
        for (j = 0; j < 14; j++)
            fprintf(stderr, "%c%c", tab[i][j].color, "\n "[j != 13]);
    }
}

int isValid (BTile **board, int lin, int col) {
    if (board[lin][col].color == '-')
        return 1;
    return 0;
}

Pos *play (BTile **board) {
    const char errmsg[] = "Não foi possível alocar uma estrutura auxiliar\n";
    Pos *ret;
    ret = emalloc(sizeof(Pos), errmsg);
    do {
        ret->lin = rand()%14;
        ret->col = rand()%14;
        printf("%d %d\n", ret->lin, ret->col);
    } while (!isValid(board, ret->lin, ret->col));
    return ret;
}

int search(BTile **board, int **used, int lin, int col, char color) {
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
    /*printf("Verifying %d:%d\n", lin, col);*/
    if (board[lin][col].color == color && color == 'b' && lin == 13)
        return 1;
    if (board[lin][col].color == color && color == 'p' && col == 13)
        return 1;
    if (board[lin][col].color == color && used[lin][col] == 0) {
        printf("Hey %c == %c ?\n", color, board[lin][col].color);
        used[lin][col] = 1;
        if (col + 1 < 14) {
            s1 = search(board, used, lin, col+1, color);
            if (lin - 1 >= 0)
                s2 = search(board, used, lin-1, col+1, color);
        }
        if (col - 1 >= 0) {
            s3 = search(board, used, lin, col-1, color);
            if (lin + 1 < 14)
                s4 = search(board, used, lin+1, col-1, color);
        }
        if (lin + 1 < 14)
            s5 = search(board, used, lin+1, col, color);
        if (lin - 1 >= 0)
            s6 = search(board, used, lin-1, col, color);
        return (s1 | s2 | s3 | s4 | s5 | s6);
    }
    return 0;
}

int noWinner (BTile **board) {
    int i, j;
    int **used;
    used = criaMatriz(14, 14);
    for (i = 0; i < 14; i++)
        for (j = 0; j < 14; j++)
            used[i][j] = 0;
    for (i = 0; i < 14; i++)
        if (search(board, used, 0, i, 'b') || search(board, used, i, 0, 'p')) {
            freeMatriz(used, 14);
            return 0;
        }
    freeMatriz(used, 14);
    return 1;
}

int beginGame (BTile **board) {
    Pos *ret;
    char color = 'b';
    while (noWinner(board)) {
        ret = play(board);
        board[ret->lin][ret->col].color = color;
        printGame(board);
        color = (color == 'b')? 'p' : 'b';
    }
    return 0;
}

int main(int argc, char *argv[]) {
    BTile **board;
    int stop;
    /*srand(time(NULL));*/
    do {
        board = criaTabuleiro(14, 14);
        beginGame(board);
        printGame(board);
        scanf("%d", &stop);
    } while (!stop);
    freeBo(board, 14, 14);
    return 0;
}
