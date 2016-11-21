/*
    EP5 - MAC121
    Nome: João Gabriel Basi
    N° USP: 9793801
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*#include "myvector.h"
#include "auxfuncs.h"
#include "PlayerFunctions.h"*/

#define INF 1073741824

typedef struct tile_t {
    int lin, col;
    char color;
} Pos;

typedef struct protopath_t {
    int value, *tops;
    Pos **stacks;
} PPath;

typedef struct pathnode_t {
    int lin, col;
    char color;
    struct pathnode_t *next;
} PNode;

typedef struct path_t {
    PNode* head;
} Path;

typedef struct btile_t {
    int lin, col;
    char color;
    struct btile_t **Neigh;
    int **weights;
} BTile;

static const int macro[2][2][6] = {{{1, 0, 0, 1, 10, 10}, {1, 10, 10, 1, 0, 0}},
                                   {{10, 10, 1, 0, 0, 1}, {0, 0, 1, 10, 10, 1}}};

static const int macroAux[2][6] = {{3, 2, 1, 0, 5, 4}, {1, 0, 5, 4, 3, 2}};

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

/*Colocar emalloc*/
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

void imprimeMatriz (int **mat, int m, int n) {
    int i, j;
    printf("[");
    for (i = 0; i < m; i++){
        printf("[");
        for (j = 0; j < n-1; j++)
            printf("%d, ", mat[i][j]);
        printf("%d]%c", mat[i][j], "\n]"[i == m-1]);
    }
    printf("\n");
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
    ret->stacks = emalloc(2*sizeof(Pos*), errmsg);
    ret->stacks[0] = emalloc(20*sizeof(Pos), errmsg);
    ret->stacks[1] = emalloc(20*sizeof(Pos), errmsg);
    ret->tops = emalloc(2*sizeof(int*), errmsg);
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

void PPathPush (PPath *path, int stack, int lin, int col, char color) {
    int prevColor;
    /*printf("Adding (%d:%d) %c to stack %d\n", lin, col, color, stack);*/
    path->stacks[stack][path->tops[stack]].lin = lin;
    path->stacks[stack][path->tops[stack]].col = col;
    path->stacks[stack][path->tops[stack]].color = color;
    if (path->tops[stack] != 0) {
        prevColor = path->stacks[stack][(path->tops[stack])-1].color;
        if (color == '-' && prevColor == '-')
            path->value += 4;
        else if (color != prevColor)
            path->value += 2;
    }
    (path->tops[stack])++;
}

Pos PPathPop (PPath *path, int stack) {
    int prevColor, color;
    if (path->tops[stack] > 1) {
        color = path->stacks[stack][(path->tops[stack])-1].color;
        prevColor = path->stacks[stack][(path->tops[stack])-2].color;
        if (color == '-' && prevColor == '-')
            path->value -= 4;
        else if (color != prevColor)
            path->value -= 2;
    }
    (path->tops[stack])--;
    /*printf("Removing (%d:%d)\n", path->stacks[stack][path->tops[stack]].lin, path->stacks[stack][path->tops[stack]].col);*/
    return path->stacks[stack][path->tops[stack]];
}

int PPathIsFull (PPath *path) {
    if (path->tops[0] == 20 || path->tops[1] == 20)
        return 1;
    return 0;
}

void PathDestroy (Path *path) {
    PNode *ptr, *ptrAux;
    ptr = path->head;
    while (ptr != NULL) {
        ptrAux = ptr;
        ptr = ptr->next;
        free(ptrAux);
    }
    free(path);
}

Path *PPtoP (PPath *ppath) {
    const char errmsg[] = "O nó de lista ligada não pode ser alocado\n";
    int i;
    Path *ret;
    PNode *auxNode;
    ret = emalloc(sizeof(Path), errmsg);
    ret->head = NULL;
    for (i = ppath->tops[1] - 1; i > 0; i--) {
        auxNode = emalloc(sizeof(PNode), errmsg);
        auxNode->lin = ppath->stacks[1][i].lin;
        auxNode->col = ppath->stacks[1][i].col;
        auxNode->color = ppath->stacks[1][i].color;
        auxNode->next = ret->head;
        ret->head = auxNode;
    }
    for (i = 0; i < ppath->tops[0]; i++) {
        auxNode = emalloc(sizeof(PNode), errmsg);
        auxNode->lin = ppath->stacks[0][i].lin;
        auxNode->col = ppath->stacks[0][i].col;
        auxNode->color = ppath->stacks[0][i].color;
        auxNode->next = ret->head;
        ret->head = auxNode;
    }
    return ret;
}

/*Cria um vetor de tamanho "tam" e retorna um ponteiro para ele*/
/*Colocar emalloc*/
int *criaVetor (int tam) {
    int *v;
    v = malloc(tam*sizeof(int));
    if (!v)
        exit(1);
    return v;
}

void imprimeVetor (int *v, int tam) {
    int i;
    printf("[");
    for (i = 0; i < tam-1; i++)
        printf("%d, ", v[i]);
    printf("%d]\n", v[i]);
}

int coltoi (char color) {
    if (color == 'b')
        return 1;
    if (color == 'p')
        return 0;
    return -1;
}

int *decode (char color, int dir) {
    int colorNo, *ret, i;
    colorNo = coltoi(color);
    ret = criaVetor(6);
    for (i = 0; i < 6; i++)
        ret[i] = macro[colorNo][dir][i];
    return ret;
}

int *decodeAux (char color, int par) {
    int *ret, i, colorNo;
    ret = criaVetor(6);
    colorNo = coltoi(color);
    if (par == 0)
        for (i = 0; i < 6; i++)
            ret[i] = i;
    else
        for (i = 0; i < 6; i++)
            ret[i] = macroAux[colorNo][i];
    return ret;
}

void troca (int *num1, int *num2) {
	*num1 ^= *num2;
	*num2 ^= *num1;
	*num1 ^= *num2;
}

int *getPriority (BTile **board, int lin, int col, char color, int dir, int par) {
    int count = 0, i, *macro, *priority, colorNo;
    colorNo = coltoi(color);
    macro = decode(color, dir);
    printf("Macro = ");
    imprimeVetor(macro, 6);
    priority = decodeAux(color, par);
    printf("Priority = ");
    imprimeVetor(priority, 6);
    for (i = 0; i < 6; i++)
        macro[i] = macro[i] + board[lin][col].weights[i][colorNo];
    printf("Weighted macro = ");
    imprimeVetor(macro, 6);
    while (count != 5) {
        count = 0;
        for (i = 0; i < 5; i++)
            if (macro[i] > macro[i+1]) {
                troca(&macro[i], &macro[i+1]);
                troca(&priority[i], &priority[i+1]);
            }
            else
                count++;
    }
    free(macro);
    return priority;
}

/*dir = 0 -> down/left
dir = 1 -> up/right*/
int partialFindPath (BTile **board, PPath *path, int **used, int lin, int col, char color, int dir, int par) {
    char thiscolor = board[lin][col].color;
    int i, linN, colN, *priority, res = 0;
    if (PPathIsFull(path)) {
        printf("Path is full, returning 0\n");
        return 0;
    }
    if (used[lin][col]) {
        printf("%d:%d already used\n", lin, col);
        return 0;
    }
    printf("Marking %d:%d as used\n", lin, col);
    used[lin][col] = 1;
    if (thiscolor != '-' && thiscolor != color) {
        printf("Tile has oposit color, returning 0\n");
        return 0;
    }
    PPathPush(path, dir, lin, col, thiscolor);
    if (color == 'b') {
        if (dir == 0 && lin == 0) {
            printf("Position is a goal\n");
            return 1;
        }
        if (dir == 1 && lin == 13) {
            printf("Position is a goal\n");
            return 1;
        }
    }
    else {
        if (dir == 0 && col == 0) {
            printf("Position is a goal\n");
            return 1;
        }
        if (dir == 1 && col == 13) {
            printf("Position is a goal\n");
            return 1;
        }
    }
    priority = getPriority(board, lin, col, color, dir, par);
    imprimeVetor(priority, 6);
    for (i = 0; i < 6 && !res; i++) {
        if (board[lin][col].Neigh[priority[i]] != NULL) {
            if (i != 0)
                printf("%d:%d: Neighbor %d returned 0, checking neighbor %d\n", lin, col, priority[i-1], priority[i]);
            linN = board[lin][col].Neigh[priority[i]]->lin;
            colN = board[lin][col].Neigh[priority[i]]->col;
            res = partialFindPath(board, path, used, linN, colN, color, dir, !par);
        }
    }
    free(priority);
    if (res != 1) {
        printf("%d:%d: Partial path returned 0 or -1\n", lin, col);
        PPathPop(path, dir);
        return res;
    }
    printf("%d:%d: All alright, returning 1\n", lin, col);
    return 1;
}

Path *findPath (BTile **board, char color) {
    int i, j, k, l, m, ret1, ret2;
    PPath *ppath1, *ppath2;
    Path *ret;
    int **used;
    ppath2 = NULL;
    used = criaMatriz(14, 14);
    for (i = 0; i < 14; i++)
        for (j = 0; j < 14; j++) {
            if (board[i][j].color == color) {
                for (m = 0; m < 2; m++) {
                    for (k = 0; k < 14; k++)
                        for (l = 0; l < 14; l++)
                            used[k][l] = 0;
                    ppath1 = PPathCreate();
                    printf("Creating Protopath1\n");
                    ret1 = partialFindPath(board, ppath1, used, i, j, color, 0, m);
                    printf("Finding direction 0 and returning %d\n", ret1);
                    used[i][j] = 0;
                    ret2 = partialFindPath(board, ppath1, used, i, j, color, 1, m);
                    printf("Finding direction 1 and returning %d\n", ret2);
                    if (ret1 != 1 || ret2 != 1) {
                        printf("Destoying path1\n");
                        PPathDestroy(ppath1);
                        continue;
                    }
                    if (ppath2 == NULL) {
                        printf("Transfering path1 to path2, because path2 == NULL\n");
                        ppath2 = ppath1;
                    }
                    else if (ppath1->value < ppath2->value) {
                        printf("Destroying path2\n");
                        printf("Transfering path1 to path2, because %d < %d\n", ppath1->value, ppath2->value);
                        PPathDestroy(ppath2);
                        ppath2 = ppath1;
                    }
                    else {
                        printf("Destroying path1 because %d >= %d\n", ppath1->value, ppath2->value);
                        PPathDestroy(ppath1);
                    }
                }
            }
        }
    ret = PPtoP(ppath2);
    freeMatriz(used, 14);
    if (ppath1 != ppath2)
        PPathDestroy(ppath1);
    PPathDestroy(ppath2);
    return ret;
}

void printPath (Path *path) {
    PNode *ptr;
    for (ptr = path->head; ptr != NULL; ptr = ptr->next)
        printf("%d:%d -> %c /", ptr->lin, ptr->col, ptr->color);
    printf("\n");
}

Pos *Interssec (Path* path1, Path *path2) {
    const char errmsg[] = "Uma estrutura auxiliar não pode ser alocada\n";
    PNode *i, *j;
    Pos *ret;
    i = path1->head;
    while (i != NULL) {
        j = path2->head;
        while (j != NULL) {
            if (j->lin == i->lin && j->col == i->col) {
                ret = emalloc(sizeof(Pos), errmsg);
                ret->lin = i->lin;
                ret->col = i->col;
                return ret;
            }
            j = j->next;
        }
        i = i->next;
    }
    return NULL;
}

Pos *play (BTile **board, char color, int turn, int Llin, int Lcol) {
    const char errmsg[] = "Não foi possível alocar uma estrutura auxiliar\n";
    Pos *ret;
    Path *path1, *path2;
    if (turn != 0) {
        path1 = findPath(board, 'b');
        printPath(path1);
        path2 = findPath(board, 'p');
        printPath(path2);
        ret = Interssec(path1, path2);
        PathDestroy(path1);
        PathDestroy(path2);
    }
    else {
        ret = emalloc(sizeof(Pos), errmsg);
        if (color == 'b') {
            ret->lin = 7;
            ret->col = 5;
        }
        else {
            if (Llin == Lcol) {
                ret->lin = Llin;
                ret->col = Lcol;
            }
            else {
                ret->lin = rand()%14;
                ret->col = ret->lin;
            }
        }
    }
    printf("%d %d\n", ret->lin, ret->col);
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
            board[lin][col].weights[i][1] -= 2;
            if (board[lin][col].Neigh[i] != NULL) {
                board[lin][col].Neigh[i]->weights[(i+3)%6][0] = INF;
                board[lin][col].Neigh[i]->weights[(i+3)%6][1] -= 2;
            }
        }
    }
    if (board[lin][col].color == 'p') {
        for (i = 0; i < 6; i++) {
            board[lin][col].weights[i][0] -= 2;
            board[lin][col].weights[i][1] = INF;
            if (board[lin][col].Neigh[i] != NULL) {
                board[lin][col].Neigh[i]->weights[(i+3)%6][0] -= 2;
                board[lin][col].Neigh[i]->weights[(i+3)%6][1] = INF;
            }
        }
    }
}

int beginGame (BTile **board, char color, int printTab) {
    int turn = 0, col, lin;
    Pos *ret = NULL;
    srand(time(NULL));
    if (color == 'b') {
        ret = play(board, color, turn, 0, 0);
        board[ret->lin][ret->col].color = 'b';
        turn++;
        updateWeights(board, ret->lin, ret->col);
        if (printTab)
            printGame(board);
        free(ret);
    }
    while (noWinner(board)) {
        do {
            if (scanf("%d %d", &lin, &col) != 2)
                return 0;
            /*Remover-------------*/
            if (lin == EOF) {
                free(ret);
                return 0;
            }
            /*--------------------*/
            /*Consertar isso*/
            if (turn == 1 && color == 1) {
                if (lin == ret->lin && col == ret->col) {
                    color = 2;
                    turn--;
                    break;
                }
            }
        } while (!isValid(board, lin, col));
        board[lin][col].color = (color == 'b')? 'p' : 'b';
        updateWeights(board, lin, col);
        if (noWinner(board)) {
            ret = play(board, color, turn, lin, col);
            if (ret->lin == lin && ret->col == col)
                color = (color == 'b')? 'p' : 'b';
            else {
                turn++;
                board[ret->lin][ret->col].color = color;
                updateWeights(board, ret->lin, ret->col);
                if (printTab)
                    printGame(board);
                free(ret);
            }
        }
        else {
            if (printTab)
                printGame(board);
            break;
        }
    }
    if (printTab)
        printGame(board);
    return 1;
}

int main(int argc, char *argv[]) {
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
