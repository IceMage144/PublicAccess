/*
    EP5 - MAC121
    Nome: João Gabriel Basi
    N° USP: 9793801
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "myvector.h"
//#include "auxfuncs.h"
//#include "PlayerFunctions.h"

#define INF 1073741824

typedef struct tile_t {
    int lin, col;
    char color;
} Pos;

typedef struct pathprot_t {
    int value, *tops;
    Pos **stacks;
} PPath;

typedef struct pathnode_t {
    int lin, col;
    char color;
    struct pathnode_t *next;
} PNode;

/*typedef *PNode Path;*/

typedef struct btile_t {
    int lin, col;
    char color;
    struct btile_t **Neigh;
    int **weights;
} BTile;

void *emalloc (size_t size, const char *msg) {
    int *Ret;
    Ret = malloc(size);
    if (Ret == NULL) {
        fprintf(stderr, "%s", msg);
        exit(1);
    }
    return Ret;
}

void show_usage (int num) {
    if (num == 0) {
        fprintf(stderr, "Uso: ep5 <cor das peças do programa> <imprime tabuleiro>\n");
    }
    if (num == 1) {
        fprintf(stderr, "Cores válidas são:\n");
        fprintf(stderr, "    - p: preto\n");
        fprintf(stderr, "    - b: branco\n");
    }
    if (num == 2) {
        fprintf(stderr, "O argumento <imprime tabuleiro> é opcional:\n");
        fprintf(stderr, "    - Se for fornecida a letra d, o programa imprime o tabuleiro a cada jogada\n");
        fprintf(stderr, "    - Se não houver argumento, o programa não imprime\n");
    }
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
                mat[i][j].Neigh[0] = &(mat[i][j+1]);
                mat[i][j].weights[0][0] = 2;
                mat[i][j].weights[0][1] = 2;
                if (i - 1 >= 0) {
                    mat[i][j].Neigh[5] = &(mat[i-1][j+1]);
                    mat[i][j].weights[5][0] = 2;
                    mat[i][j].weights[5][1] = 2;
                }
                else {
                    mat[i][j].Neigh[5] = NULL;
                    mat[i][j].weights[5][0] = INF;
                    mat[i][j].weights[5][1] = 1;
                }
            }
            else {
                mat[i][j].Neigh[0] = NULL;
                mat[i][j].weights[0][0] = 1;
                mat[i][j].weights[0][1] = INF;
                mat[i][j].Neigh[5] = NULL;
                mat[i][j].weights[5][0] = INF;
                mat[i][j].weights[5][1] = 1;
            }
            if (i + 1 < 14) {
                mat[i][j].Neigh[1] = &(mat[i+1][j]);
                mat[i][j].weights[1][0] = 2;
                mat[i][j].weights[1][1] = 2;
            }
            else {
                mat[i][j].Neigh[1] = NULL;
                mat[i][j].weights[1][0] = INF;
                mat[i][j].weights[1][1] = 1;
            }
            if (j - 1 >= 0) {
                mat[i][j].Neigh[3] = &(mat[i][j-1]);
                mat[i][j].weights[3][0] = 2;
                mat[i][j].weights[3][1] = 2;
                if (i + 1 < 14) {
                    mat[i][j].Neigh[2] = &(mat[i+1][j-1]);
                    mat[i][j].weights[2][0] = 2;
                    mat[i][j].weights[2][1] = 2;
                }
                else {
                    mat[i][j].Neigh[2] = NULL;
                    mat[i][j].weights[2][0] = INF;
                    mat[i][j].weights[2][1] = 1;
                }
            }
            else {
                mat[i][j].Neigh[3] = NULL;
                mat[i][j].weights[3][0] = INF;
                mat[i][j].weights[3][1] = 1;
                mat[i][j].Neigh[2] = NULL;
                mat[i][j].weights[2][0] = 1;
                mat[i][j].weights[2][1] = INF;
            }
            if (i - 1 >= 0) {
                mat[i][j].Neigh[4] = &(mat[i-1][j]);
                mat[i][j].weights[4][0] = 2;
                mat[i][j].weights[4][1] = 2;
            }
            else {
                mat[i][j].Neigh[4] = &(mat[i+1][j-1]);
                mat[i][j].weights[4][0] = INF;
                mat[i][j].weights[4][1] = 1;
            }
        }
    }
    return mat;
}

void printBo(BTile **board, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            printf("========================================\n");
            printf("lin = %d\n", board[i][j].lin);
            printf("col = %d\n", board[i][j].col);
            printf("color = %c\n", board[i][j].color);
            if (board[i][j].Neigh[0]) {
                printf("Neigh[0] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[0], board[i][j].Neigh[0]->lin, board[i][j].Neigh[0]->col);
            }
            else {
                printf("Neigh[0] = NULL\n");
            }
            printf("Weight[0] = [0]%d/[1]%d\n", board[i][j].weights[0][0], board[i][j].weights[0][1]);
            if (board[i][j].Neigh[1]) {
                printf("Neigh[1] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[1], board[i][j].Neigh[1]->lin, board[i][j].Neigh[1]->col);
            }
            else {
                printf("Neigh[1] = NULL\n");
            }
            printf("Weight[1] = [0]%d/[1]%d\n", board[i][j].weights[1][0], board[i][j].weights[1][1]);
            if (board[i][j].Neigh[2]) {
                printf("Neigh[2] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[2], board[i][j].Neigh[2]->lin, board[i][j].Neigh[2]->col);
            }
            else {
                printf("Neigh[2] = NULL\n");
            }
            printf("Weight[2] = [0]%d/[1]%d\n", board[i][j].weights[2][0], board[i][j].weights[2][1]);
            if (board[i][j].Neigh[3]) {
                printf("Neigh[3] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[3], board[i][j].Neigh[3]->lin, board[i][j].Neigh[3]->col);
            }
            else {
                printf("Neigh[3] = NULL\n");
            }
            printf("Weight[3] = [0]%d/[1]%d\n", board[i][j].weights[3][0], board[i][j].weights[3][1]);
            if (board[i][j].Neigh[4]){
                printf("Neigh[4] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[4], board[i][j].Neigh[4]->lin, board[i][j].Neigh[4]->col);
            }
            else {
                printf("Neigh[4] = NULL\n");
            }
            printf("Weight[4] = [0]%d/[1]%d\n", board[i][j].weights[4][0], board[i][j].weights[4][1]);
            if (board[i][j].Neigh[5]) {
                printf("Neigh[5] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[5], board[i][j].Neigh[5]->lin, board[i][j].Neigh[5]->col);
            }
            else {
                printf("Neigh[5] = NULL\n");
            }
            printf("Weight[5] = [0]%d/[1]%d\n", board[i][j].weights[5][0], board[i][j].weights[5][1]);
        }
    }
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
    for (i = 13; i >= 0; i--) {
        for (j = 0; j < i; j++)
            fprintf(stderr, " ");
        for (j = 0; j < 14; j++)
            fprintf(stderr, "%c%c", tab[i][j].color, "\n "[j != 13]);
    }
}

PPath *PPathCreate () {
    const char errmsg[] = "O protótipo de caminho não pode ser alocado\n";
    PPath *ret;
    ret = emalloc(sizeof(PPath), errmsg);
    ret->stacks = emalloc(sizeof(Pos*), errmsg);
    ret->stacks[0] = emalloc(100*sizeof(Pos), errmsg);
    ret->stacks[1] = emalloc(100*sizeof(Pos), errmsg);
    ret->tops = emalloc(sizeof(int*), errmsg);
    ret->tops[0] = 0;
    ret->tops[1] = 0;
    ret->value = 0;
    return ret;
}

void PPathDestroy (PPath *path) {
    free(path->stacks[0]);
    free(path->stacks[1]);
    free(path->stacks);
    free(path->tops);
    free(path);
}

void PPathAdd (PPath *path, int stack, int lin, int col, char color) {
    path->stacks[stack][path->tops[stack]].lin = lin;
    path->stacks[stack][path->tops[stack]].col = col;
    path->stacks[stack][path->tops[stack]].color = color;
    (path->tops[stack])++;
}

Pos PPathRemove (PPath *path, int stack) {
    (path->tops[stack])--;
    return path->stacks[stack][path->tops[stack]];
}

/*dir = 0 -> down/left
dir = 1 -> up/right*/
void search (PPath *path, char color, int dir, int par) {
    next = 
    if (color = 'b') {

    }
}

Path findPath (BTile **board, char color) {
    PPath *ppath1, *ppath2;
    ppath1 = PPathCreate();
    ppath2 = PPathCreate();
    if (color == 'p') {

    }
    else {

    }
}

Pos *play (BTile **board) {
    const char errmsg[] = "Não foi possível alocar uma estrutura auxiliar\n";
    Pos *ret;
    ret = emalloc(sizeof(Pos), errmsg);
    do {
        ret->lin = rand()%14;
        ret->col = rand()%14;
    } while (board[ret->lin][ret->col].color != '-');
    printf("%d %d\n", ret->lin, ret->col);
    return ret;
}

/*Mudar essa função*/
int search(BTile **board, int mlin, int mcol, int lin, int col, char color) {
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
    /*printf("Verifying %d:%d\n", lin, col);*/
    if (board[lin][col].color == color && color == 'b' && lin == 13)
        return 1;
    if (board[lin][col].color == color && color == 'p' && col == 13)
        return 1;
    if (board[lin][col].color == color) {
        if (col + 1 < 14 && col + 1 != mcol) {
            s1 = search(board, lin, col, lin, col+1, color);
            if (lin - 1 >= 0 && lin-1 != mlin)
                s2 = search(board, lin, col, lin-1, col+1, color);
        }
        if (col - 1 >= 0 && col - 1 != mcol) {
            s3 = search(board, lin, col, lin, col-1, color);
            if (lin + 1 < 14 && lin + 1 != mlin)
                s4 = search(board, lin, col, lin+1, col-1, color);
        }
        if (lin + 1 < 14 && lin + 1 != mlin)
            s5 = search(board, lin, col, lin+1, col, color);
        if (lin - 1 >= 0 && lin - 1 != mlin)
            s6 = search(board, lin, col, lin-1, col, color);
        return (s1 | s2 | s3 | s4 | s5 | s6);
    }
    return 0;
}

int noWinner (BTile **board) {
    int i;
    for (i = 0; i < 14; i++)
        if (search(board, 0, 0, 0, i, 'b') || search(board, 0, 0, i, 0, 'p'))
            return 0;
    return 1;
}

int isValid (BTile **board, int lin, int col) {
    if (lin >= 0 && lin < 14 && col >= 0 && col < 14) {
        if (board[lin][col].color == '-')
            return 1;
        fprintf(stderr, "A posição escolhida já está ocupada. Faça outra jogada.\n");
        return 0;
    }
    fprintf(stderr, "A posição escolhida não está no tabuleiro. Faça outra jogada.\n");
    return 0;
}

void updateWeights (BTile **board, int lin, int col) {
    int i;
    if (board[lin][col].color == 'b') {
        for (i = 0; i < 6; i++) {
            board[lin][col].weights[i][0] = INF;
            (board[lin][col].weights[i][1])--;
            board[lin][col].Neigh[i]->weights[(i+3)%6][0] = INF;
            (board[lin][col].Neigh[i]->weights[(i+3)%6][1])--;
        }
    }
    if (board[lin][col].color == 'p') {
        for (i = 0; i < 6; i++) {
            (board[lin][col].weights[i][0])--;
            board[lin][col].weights[i][1] = INF;
            (board[lin][col].Neigh[i]->weights[(i+3)%6][0])--;
            board[lin][col].Neigh[i]->weights[(i+3)%6][1] = INF;
        }
    }
}

int beginGame (BTile **board, char color, int printTab) {
    int turn = 0, col, lin;
    Pos *ret = NULL;
    srand(time(NULL));
    if (color == 'b') {
        ret = play(board);
        board[ret->lin][ret->col].color = 'b';
        turn++;
        updateWeights(board, ret->lin, ret->col);
        if (printTab)
            printGame(board);
    }
    while (noWinner(board)) {
        do {
            if (scanf("%d %d", &lin, &col) != 2)
                return 0;
            if (turn == 1 && color == 1) {
                if (lin == ret->lin && col == ret->col) {
                    color = 2;
                    turn--;
                    break;
                }
            }
        } while (!isValid(board, lin, col));
        turn++;
        board[lin][col].color = (color == 'b')? 'p' : 'b';
        updateWeights(board, lin, col);
        if (noWinner(board))
            ret = play(board);
        else {
            if (printTab)
                printGame(board);
            break;
        }
        board[ret->lin][ret->col].color = color;
        updateWeights(board, ret->lin, ret->col);
        if (printTab)
            printGame(board);
        free(ret);
    }
    if (printTab)
        printGame(board);
    return 1;
}

int main(int argc, char *argv[]) {
    int color, i, j;
    BTile **board;
    int printTab = 0;
    board = criaTabuleiro(14, 14);
    if (argc < 2) {
        show_usage(0);
        return 0;
    }
    if (argc == 3 && strcmp(argv[2], "d")) {
        show_usage(0);
        return 0;
    }
    else if (argc == 3)
        printTab = 1;
    if (strcmp(argv[1], "b") && strcmp(argv[1], "p")) {
        show_usage(1);
        return 0;
    }
    /*printBo(board, 14, 14);*/
    beginGame(board, argv[1][0], printTab);
    freeBo(board, 14, 14);
    return 0;
}
