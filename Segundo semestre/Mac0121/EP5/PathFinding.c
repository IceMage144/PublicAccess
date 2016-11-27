/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include "auxfuncs.h"
#include "PathFinding.h"
#include "BoardFuncs.h"

/*Retorna um ponteiro para uma cabeça de Path nova*/
Path *PathCreate () {
    const char errmsg[] = "O caminho não pode ser alocado\n";
    Path *ret;
    ret = emalloc(sizeof(Path), errmsg);
    ret->head = emalloc(sizeof(PNode), errmsg);
    ret->head->pos = 0;
    ret->head->next = NULL;
    ret->value = 0;
    ret->stCount = 0;
    return ret;
}

/*Desaloca um caminho "path"*/
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

/*-----------------------------Retirar----------------------------------------*/
void printPath (Path *path) {
    PNode *ptr;
    if (path == NULL)
        printf("(NULL)\n");
    else
        for (ptr = path->head->next; ptr != NULL; ptr = ptr->next)
            printf("%d:%d -> %c /", ptr->lin, ptr->col, ptr->color);
        printf("\n");
}

/*Devolve o primeiro nó pertencente ao "path1" que é comum aos caminhos "path1"
e "path2"*/
PNode *Interssec (Path *path1, Path *path2) {
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

/*Função auxiliar à getPriority que recebe uma cor "color" e uma direção "dir"
e retorna o vetor correspondente à essas informações da matriz "macro"*/
int *decode (char color, int dir) {
    int colorNo, *ret, i;
    colorNo = coltoi(color);
    ret = criaVetor(6);
    for (i = 0; i < 6; i++)
        ret[i] = macro[colorNo][dir][i];
    return ret;
}

/*Função auxiliar à getPriority que recebe uma cor "color" e uma paridade "par"
e retorna o vetor correspondente à essas informações da matriz "macroAux"*/
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

/*Função auxiliar à partialFindPath que recebe o tabuleiro "board", uma
posição ("lin","col"), uma cor "color", uma direção "dir" e uma paridade "par"
e retorna um vetor de 6 posições com números de 0 a 5, ordenados de acordo com
a prioridade de cada vizinho*/
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

/*Função recursiva auxiliar à findPath que recebe o tabuleiro "board", um
ponteiro para um nó de caminho "node", um caminho "path", uma matriz de
posições já visitadas "used", uma posição do tabuleiro ("lin","col"), uma cor
"color", uma direção "dir" e uma paridade "par" e guarda em "path" um caminho
entre as bordas associadas à cor "color" e retorna 1 se foi achado um caminho,
ou 0 caso contrário*/
int partialFindPath (BTile **board, PNode **node, Path *path, int **used, int lin, int col, char color, int dir, int par) {
    const char errmsg[] = "Um nó de lista ligada não pode ser alocado\n";
    char thiscolor = board[lin][col].color;
    char otcolor = (color == 'b')? 'p' : 'b';
    int i, linN, colN, *priority, res = 0;
    PNode *aux;
    if ((*node)->pos >= 25) {
        /*MEMO*//*printf("Path is full, returning 0\n");*//*MEMO*/
        return 0;
    }
    if (used[lin][col]) {
        /*MEMO*//*printf("%d:%d already used\n", lin, col);*//*MEMO*/
        return 0;
    }
    /*MEMO*//*printf("Marking %d:%d as used\n", lin, col);*//*MEMO*/
    used[lin][col] = 1;
    /*if (color == 'b')*/
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

/*Recebe o tabuleiro "board" e uma cor "color" e devolve um caminho entre as
laterais do tabuleiro pertencentes a cor fornecida (Obs.: o caminho devolvido
não é o melhor possível, mas é um dos melhores)*/
Path *findPath (BTile **board, char color) {
    int i, j, k, l, count = 0, found;
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
            count = 1;
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
            count = 1;
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
    if (!count)
        ret = NULL;
    else
        ret = path2;
    freeMatriz(used, N);
    return ret;
}

/*Recebe dois caminhos "path1" e "path2" e devolve 1 se eles forem iguais ou
0 caso contrário (Obs.: só compara a linha e a coluna de cada posição, não
compara a cor)*/
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
