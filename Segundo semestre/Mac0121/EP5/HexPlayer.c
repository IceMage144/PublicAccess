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

#define N 14

typedef struct pos_t {
    int lin, col;
    char color;
} Pos;

typedef struct pathnode_t {
    int lin, col, pos;
    char color;
    struct pathnode_t *next;
} PNode;

typedef struct path_t {
    PNode *head;
    int value, stCount;
} Path;

typedef struct btile_t {
    int lin, col;
    char color;
    struct btile_t **Neigh;
    int *weights;
} BTile;

static const int macro[2][2][6] = {{{10, 1, 0, 0, 1, 10}, {0, 1, 10, 10, 1, 0}},
                                   {{0, 0, 1, 10, 10, 1}, {10, 10, 1, 0, 0, 1}}};

static const int macroAux[2][6] = {{5, 4, 3, 2, 1, 0}, {1, 0, 5, 4, 3, 2}};


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
int **criaMatriz (int m, int n) {
    int **mat;
    int i, j;
    mat = malloc(m*sizeof(int*));
    if (mat == NULL) {
        free(mat);
        exit(1);
    }
    for (i = 0; i < m; i++) {
        mat[i] = malloc(n*sizeof(int));
        if (mat[i] == NULL) {
            for (j = 0; j <= i; j++)
                free(mat[j]);
            free(mat);
            exit(1);
        }
    }
    return mat;
}

void freeMatriz (int **mat, int m) {
    int i;
    for (i = 0; i < m; i++)
        free(mat[i]);
    free(mat);
}

void imprimeMatriz (int **mat, int m, int n) {
    int i, j;
    printf("[");
    for (i = 0; i < m; i++) {
        printf("[");
        for (j = 0; j < n-1; j++)
            printf("%d, ", mat[i][j]);
        printf("%d]%c", mat[i][j], "\n]"[i == m-1]);
    }
    printf("\n");
}

BTile **criaTabuleiro (int m, int n) {
    const char errmsg[] = "Erro ao criar o tabuleiro";
    BTile **mat;
    int i, j, k;
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

void printBo(BTile **board, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            printf("========================================\n");
            printf("lin = %d\n", board[i][j].lin);
            printf("col = %d\n", board[i][j].col);
            printf("color = %c\n", board[i][j].color);
            printf("Weights = [0]%d/[1]%d\n", board[i][j].weights[0], board[i][j].weights[1]);
            if (board[i][j].Neigh[0])
                printf("Neigh[0] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[0], board[i][j].Neigh[0]->lin, board[i][j].Neigh[0]->col);
            else
                printf("Neigh[0] = NULL\n");
            if (board[i][j].Neigh[1])
                printf("Neigh[1] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[1], board[i][j].Neigh[1]->lin, board[i][j].Neigh[1]->col);
            else
                printf("Neigh[1] = NULL\n");
            if (board[i][j].Neigh[2])
                printf("Neigh[2] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[2], board[i][j].Neigh[2]->lin, board[i][j].Neigh[2]->col);
            else
                printf("Neigh[2] = NULL\n");
            if (board[i][j].Neigh[3])
                printf("Neigh[3] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[3], board[i][j].Neigh[3]->lin, board[i][j].Neigh[3]->col);
            else
                printf("Neigh[3] = NULL\n");
            if (board[i][j].Neigh[4])
                printf("Neigh[4] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[4], board[i][j].Neigh[4]->lin, board[i][j].Neigh[4]->col);
            else
                printf("Neigh[4] = NULL\n");
            if (board[i][j].Neigh[5])
                printf("Neigh[5] = %p (lin: %d, col: %d)\n", board[i][j].Neigh[5], board[i][j].Neigh[5]->lin, board[i][j].Neigh[5]->col);
            else
                printf("Neigh[5] = NULL\n");
        }
    }
}

void freeBo (BTile **board, int m, int n) {
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

void printGame (BTile **tab) {
    int i, j;
    /*for (i = 0; i >= N+1; i--)
        fprintf(stderr, " ");*/
    fprintf(stderr, " ");
    for (i = 0; i < N; i++)
        fprintf(stderr, "%d ", i%10);
    fprintf(stderr, "\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < i-i/10; j++)
            fprintf(stderr, " ");
        fprintf(stderr, "%d ", i);
        for (j = 0; j < N; j++)
            fprintf(stderr, "%c%c", tab[i][j].color, "\n "[j != N-1]);
    }
}

Path *PathCreate () {
    const char errmsg[] = "O caminho não pode ser alocado\n";
    Path *ret;
    ret = emalloc(sizeof(Path), errmsg);
    ret->head = emalloc(sizeof(PNode), errmsg);
    ret->head->pos = 0;
    ret->value = 0;
    ret->stCount = 0;
    return ret;
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
    /*MEMO*//*printf("Macro = ");
    imprimeVetor(macro, 6);*//*MEMO*/
    priority = decodeAux(color, par);
    /*MEMO*//*printf("Priority = ");
    imprimeVetor(priority, 6);*//*MEMO*/
    for (i = 0; i < 6; i++) {
        if (board[lin][col].Neigh[priority[i]] != NULL)
            macro[i] = macro[i] + board[lin][col].Neigh[priority[i]]->weights[colorNo];
        else
            macro[i] = INF;
    }
    /*MEMO*//*printf("Weighted macro = ");
    imprimeVetor(macro, 6);*//*MEMO*/
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

int partialFindPath (BTile **board, PNode **node, Path *path, int **used, int lin, int col, char color, int dir, int par) {
    const char errmsg[] = "Um nó de lista ligada não pode ser alocado\n";
    char thiscolor = board[lin][col].color;
    char otcolor = (color == 'b')? 'p' : 'b';
    int i, linN, colN, *priority, res = 0;
    PNode *aux;
    if ((*node)->pos >= 30) {
        /*MEMO*//*printf("Path is full, returning 0\n");*//*MEMO*/
        return 0;
    }
    if (used[lin][col]) {
        /*MEMO*//*printf("%d:%d already used\n", lin, col);*//*MEMO*/
        return 0;
    }
    /*MEMO*//*printf("Marking %d:%d as used\n", lin, col);*//*MEMO*/
    used[lin][col] = 1;
    if (color == 'b')
    /*MEMO*//*imprimeMatriz(used, N, N);*//*MEMO*/
    if (thiscolor != '-' && thiscolor != color) {
        /*MEMO*//*printf("Tile has oposit color, returning 0\n");*//*MEMO*/
        return 0;
    }
    aux = emalloc(sizeof(PNode), errmsg);
    aux->lin = lin;
    aux->col = col;
    aux->color = thiscolor;
    aux->next = NULL;
    aux->pos = (*node)->pos + 1;
    (*node)->next = aux;
    path->value += board[lin][col].weights[coltoi(color)];
    if (color == 'b') {
        if (dir == 0 && lin == 0) {
            /*MEMO*//*printf("Position is a goal\n");*//*MEMO*/
            return 1;
        }
        if (dir == 1 && lin == N-1) {
            /*MEMO*//*printf("Position is a goal\n");*//*MEMO*/
            return 1;
        }
    }
    else {
        if (dir == 0 && col == 0) {
            /*MEMO*//*printf("Position is a goal\n");*//*MEMO*/
            return 1;
        }
        if (dir == 1 && col == N-1) {
            /*MEMO*//*printf("Position is a goal\n");*//*MEMO*/
            return 1;
        }
    }
    priority = getPriority(board, lin, col, color, dir, par);
    /*MEMO*//*imprimeVetor(priority, 6);*//*MEMO*/
    for (i = 0; i < 6 && !res; i++) {
        if (board[lin][col].Neigh[priority[i]] != NULL) {
            /*MEMO*//*if (i != 0)*//*MEMO*/
                /*MEMO*//*printf("%d:%d: Neighbor %d returned 0, checking neighbor %d\n", lin, col, priority[i-1], priority[i]);*//*MEMO*/
            linN = board[lin][col].Neigh[priority[i]]->lin;
            colN = board[lin][col].Neigh[priority[i]]->col;
            res = partialFindPath(board, &aux, path, used, linN, colN, color, dir, !par);
        }
        if (board[lin][col].Neigh[i] != NULL && board[lin][col].Neigh[(i+2)%6] != NULL) {
            if (board[lin][col].Neigh[i]->color == otcolor && board[lin][col].Neigh[(i+2)%6]->color == otcolor) {
                res = 0;
                break;
            }
        }
    }
    free(priority);
    if (res != 1) {
        /*MEMO*//*printf("%d:%d: Partial path returned 0 or -1\n", lin, col);*//*MEMO*/
        free(aux);
        (*node)->next = NULL;
        if (thiscolor == '-')
            path->value -= board[lin][col].weights[coltoi(color)];
        return res;
    }
    /*MEMO*//*printf("%d:%d: All alright, returning 1\n", lin, col);*//*MEMO*/
    return 1;
}

Path *findPath (BTile **board, char color) {
    int i, j, k, l, cont = 0, found;
    Path *path1, *path2;
    Path *ret;
    int **used;
    path1 = NULL;
    path2 = NULL;
    used = criaMatriz(N, N);
    for (i = 0; i < N; i++)
        for (j = 0; j < 2; j++) {
            for (k = 0; k < N; k++)
                for (l = 0; l < N; l++)
                    used[k][l] = 0;
            /*MEMO*//*printf("Creating Path1\n");*//*MEMO*/
            path1 = PathCreate();
            if (color == 'p')
                found = partialFindPath(board, &(path1->head), path1, used, i, 0, color, 1, j);
            else
                found = partialFindPath(board, &(path1->head), path1, used, 0, i, color, 1, j);
            /*MEMO*//*imprimeMatriz(used, N, N);*//*MEMO*/
            /*MEMO*//*printf("Finding direction 0 and returning %d\n", found);*//*MEMO*/
            if (found != 1) {
                /*MEMO*//*printf("Destoying path1\n");*//*MEMO*/
                PathDestroy(path1);
                continue;
            }
            cont = 1;
            if (path2 == NULL) {
                /*MEMO*//*printf("Transfering path1 to path2, because path2 == NULL\n");*//*MEMO*/
                path2 = path1;
            }
            else if (path1->value < path2->value) {
                /*MEMO*//*printf("Destroying path2\n");*//*MEMO*/
                /*MEMO*//*printf("Transfering path1 to path2, because %d < %d\n", path1->value, path2->value);*//*MEMO*/
                PathDestroy(path2);
                path2 = path1;
            }
            else {
                /*MEMO*//*printf("Destroying path1 because %d >= %d\n", path1->value, path2->value);*//*MEMO*/
                PathDestroy(path1);
            }
        }
    for (i = 7; i < N; i++)
        for (j = 0; j < 2; j++) {
            for (k = 0; k < N; k++)
                for (l = 0; l < N; l++)
                    used[k][l] = 0;
            /*MEMO*//*printf("Creating Protopath1\n");*//*MEMO*/
            path1 = PathCreate();
            if (color == 'p')
                found = partialFindPath(board, &(path1->head), path1, used, i, 13, color, 0, j);
            else
                found = partialFindPath(board, &(path1->head), path1, used, 13, i, color, 0, j);
            /*MEMO*//*printf("Finding direction 0 and returning %d\n", found);*//*MEMO*/
            /*MEMO*//*imprimeMatriz(used, N, N);*//*MEMO*/
            if (found != 1) {
                /*MEMO*//*printf("Destoying path1\n");*//*MEMO*/
                PathDestroy(path1);
                continue;
            }
            cont = 1;
            if (path2 == NULL) {
                /*MEMO*//*printf("Transfering path1 to path2, because path2 == NULL\n");*//*MEMO*/
                path2 = path1;
            }
            else if (path1->value < path2->value) {
                /*MEMO*//*printf("Destroying path2\n");*//*MEMO*/
                /*MEMO*//*printf("Transfering path1 to path2, because %d < %d\n", path1->value, path2->value);*//*MEMO*/
                PathDestroy(path2);
                path2 = path1;
            }
            else {
                /*MEMO*//*printf("Destroying path1 because %d >= %d\n", path1->value, path2->value);*//*MEMO*/
                PathDestroy(path1);
            }
        }
    if (!cont)
        ret = NULL;
    else
        ret = path2;
    freeMatriz(used, N);
    return ret;
}

void printPath (Path *path) {
    PNode *ptr;
    if (path == NULL)
        printf("(NULL)\n");
    else
        for (ptr = path->head->next; ptr != NULL; ptr = ptr->next)
            printf("%d:%d -> %c /", ptr->lin, ptr->col, ptr->color);
        printf("\n");
}

int pathcmp (Path *path1, Path *path2) {
    PNode *ptr1, *ptr2;
    ptr1 = path1->head->next;
    ptr2 = path2->head->next;
    while (ptr1 != NULL && ptr2 != NULL) {
        /*printf("Hey\n") ;*/
        if (ptr1->lin != ptr2->lin || ptr1->col != ptr2->col)
            return 0;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return 1;
}

PNode *Interssec (Path *path1, Path *path2) {
    const char errmsg[] = "Uma estrutura auxiliar não pode ser alocada\n";
    PNode *i, *j;
    i = path1->head->next;
    while (i != NULL) {
        j = path2->head->next;
        while (j != NULL) {
            if (j->lin == i->lin && j->col == i->col)
                return i;
            j = j->next;
        }
        i = i->next;
    }
    return NULL;
}

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

Pos *play (BTile **board, Path *prevpath, char color, int turn, int Llin, int Lcol) {
    const char errmsg[] = "Não foi possível alocar uma estrutura auxiliar\n";
    PNode *ptr;
    Pos *ret;
    Path *pathB, *pathP;
    if (turn != 0) {
        pathB = findPath(board, 'b');
        /*MEMO*/printPath(pathB);/*MEMO*/
        pathP = findPath(board, 'p');
        /*MEMO*/printPath(pathP);/*MEMO*/
        if (pathB == NULL || pathP == NULL) {
            ret = emalloc(sizeof(Pos), errmsg);
            do {
                ret->lin = rand()%N;
                ret->col = rand()%N;
            } while (!isValid(board, ret->lin, ret->col, 0));
            return ret;
        }
        if (color == 'b') {
            if (prevpath != NULL && pathcmp(pathB, prevpath)) {
                /*Attack*/
                ptr = Interssec(pathB, pathP);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
            }
            else if (prevpath != NULL) {
                /*Deffend*/
                ptr = Interssec(pathP, pathB);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
                /*MEMO*//*printf("Destroying prevpath\n");*//*MEMO*/
                PathDestroy(prevpath);
                prevpath = pathB;
            }
            else {
                /*Forced deffense*/
                ptr = Interssec(pathP, pathB);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
                prevpath = pathB;
            }
            if (ptr->next != NULL)
                if (ptr->next->color == '-')
                    ptr = ptr->next;
            ret = emalloc(sizeof(Pos), errmsg);
            /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
            ret->lin = ptr->lin;
            ret->col = ptr->col;
            /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
        }
        else {
            if (prevpath != NULL && pathcmp(pathP, prevpath)) {
                /*Attack*/
                ptr = Interssec(pathP, pathB);
            }
            else if (prevpath != NULL) {
                /*Deffend*/
                ptr = Interssec(pathB, pathP);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
                /*MEMO*//*printf("Destroying prevpath\n");*//*MEMO*/
                PathDestroy(prevpath);
                prevpath = pathP;
            }
            else {
                /*Forced deffense*/
                ptr = Interssec(pathB, pathP);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
                prevpath = pathP;
            }
            if (ptr->next != NULL && ptr->next->color == '-')
                ptr = ptr->next;
            ret = emalloc(sizeof(Pos), errmsg);
            ret->lin = ptr->lin;
            ret->col = ptr->col;
            /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
        }
        /*MEMO*//*printf("Destroying pathP\n");*//*MEMO*/
        PathDestroy(pathP);
        /*MEMO*//*printf("Destroying pathB\n");*//*MEMO*/
        PathDestroy(pathB);
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
                ret->lin = rand()%N;
                ret->col = ret->lin;
            }
        }
    }
    printf("%d %d\n", ret->lin, ret->col);
    return ret;
}

int search(BTile **board, int **used, int lin, int col, char color) {
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
    /*MEMO*//*printf("Verifying %d:%d\n", lin, col);*//*MEMO*/
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

int noWinner (BTile **board) {
    int i, j;
    int **used;
    used = criaMatriz(N, N);
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            used[i][j] = 0;
    for (i = 0; i < N; i++)
        if (search(board, used, 0, i, 'b') || search(board, used, i, 0, 'p')) {
            freeMatriz(used, N);
            return 0;
        }
    freeMatriz(used, N);
    return 1;
}

/*Melhorar*/
void updateWeights (BTile **board, int lin, int col) {
    int i;
    if (board[lin][col].color == 'b') {
        board[lin][col].weights[0] = INF;
        board[lin][col].weights[1] = 0;
        for (i = 0; i < 6; i++)
            if (board[lin][col].Neigh[i] != NULL)
                if (board[lin][col].Neigh[i]->color != 'p') {
                    if (board[lin][col].Neigh[i]->weights[0] < 4)
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
                    if (board[lin][col].Neigh[i]->weights[1] < 4)
                        board[lin][col].Neigh[i]->weights[1] += 2;
                }
    }
}

int beginGame (BTile **board, char color, int printTab) {
    int turn = 0, col, lin;
    Pos *ret, *retAux;
    Path *prevpath;
    clock_t t;
    ret = NULL;
    prevpath = NULL;
    srand(time(NULL));
    if (color == 'b') {
        retAux = play(board, prevpath, color, turn, 0, 0);
        board[retAux->lin][retAux->col].color = 'b';
        turn++;
        updateWeights(board, retAux->lin, retAux->col);
        if (printTab) {
            printGame(board);
            /*printBo(board, N, N);*/
        }
    }
    while (noWinner(board)) {
        do {
            if (scanf("%d %d", &lin, &col) != 2)
                return 0;
            /*Remover-------------*/
            if (lin == EOF) {
                PathDestroy(prevpath);
                return 0;
            }
            /*--------------------*/
            /*Consertar isso*/
            if (turn == 1 && color == 'b') {
                if (lin == retAux->lin && col == retAux->col) {
                    color = 'p';
                    turn--;
                    free(retAux);
                    break;
                }
                free(retAux);
            }
        } while (!isValid(board, lin, col, 1));
        t = clock();
        board[lin][col].color = (color == 'b')? 'p' : 'b';
        updateWeights(board, lin, col);
        if (noWinner(board)) {
            ret = play(board, prevpath, color, turn, lin, col);
            if (ret->lin == lin && ret->col == col)
                color = (color == 'b')? 'p' : 'b';
            else {
                turn++;
                board[ret->lin][ret->col].color = color;
                updateWeights(board, ret->lin, ret->col);
                if (printTab)
                    printGame(board);
            }
            free(ret);
        }
        else {
            if (printTab)
                printGame(board);
            break;
        }
        t = clock() - t;
        printf("Runtime = %fs\n", ((float)t)/CLOCKS_PER_SEC);
    }
    if (printTab)
        printGame(board);
    /*MEMO*//*printf("Destroying prevpath\n");*//*MEMO*/
    if (prevpath != NULL)
        PathDestroy(prevpath);
    return 1;
}

int main(int argc, char *argv[]) {
    BTile **board;
    int printTab = 0;
    board = criaTabuleiro(N, N);
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
    /*printBo(board, N, N);*/
    beginGame(board, argv[1][0], printTab);
    freeBo(board, N, N);
    return 0;
}
