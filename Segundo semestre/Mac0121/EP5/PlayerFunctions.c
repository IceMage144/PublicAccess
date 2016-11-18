
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "auxfuncs.h"
#include "PlayerFunctions.h"

int isValid (int **tab, int lin, int col) {
    if (lin >= 0 && lin < 14 && col >= 0 && col < 14) {
        if (tab[lin][col] == '-')
            return 1;
        fprintf(stderr, "A posição escolhida já está ocupada. Faça outra jogada.\n");
        return 0;
    }
    fprintf(stderr, "A posição escolhida não está no tabuleiro. Faça outra jogada.\n");
    return 0;
}

int search(int **tab, int mlin, int mcol, int lin, int col, char color) {
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0, s6 = 0;
    /*printf("Verifying %d:%d\n", lin, col);*/
    if (tab[lin][col] == color && color == 'b' && lin == 13)
        return 1;
    if (tab[lin][col] == color && color == 'p' && col == 13)
        return 1;
    if (tab[lin][col] == color) {
        if (col + 1 < 14 && col + 1 != mcol) {
            s1 = search(tab, lin, col, lin, col+1, color);
            if (lin - 1 >= 0 && lin-1 != mlin)
                s2 = search(tab, lin, col, lin-1, col+1, color);
        }
        if (col - 1 >= 0 && col - 1 != mcol) {
            s3 = search(tab, lin, col, lin, col-1, color);
            if (lin + 1 < 14 && lin + 1 != mlin)
                s4 = search(tab, lin, col, lin+1, col-1, color);
        }
        if (lin + 1 < 14 && lin + 1 != mlin)
            s5 = search(tab, lin, col, lin+1, col, color);
        if (lin - 1 >= 0 && lin - 1 != mlin)
            s6 = search(tab, lin, col, lin-1, col, color);
        return (s1 | s2 | s3 | s4 | s5 | s6);
    }
    return 0;
}

int noWinner (int **tab) {
    int i;
    for (i = 0; i < 14; i++)
        if (search(tab, 0, 0, 0, i, 'b') || search(tab, 0, 0, i, 0, 'p'))
            return 0;
    return 1;
}

Tile *play (int **tab) {
    const char errmsg[] = "Não foi possível alocar uma estrutura auxiliar\n";
    Tile *ret;
    ret = emalloc(sizeof(Tile), errmsg);
    do {
        ret->lin = rand()%14;
        ret->col = rand()%14;
    } while (tab[ret->lin][ret->col] != '-');
    printf("%d %d\n", ret->lin, ret->col);
    return ret;
}

void printGame (int **tab) {
    int i, j;
    for (i = 13; i >= 0; i--) {
        for (j = 0; j < i; j++)
            fprintf(stderr, " ");
        for (j = 0; j < 14; j++)
            fprintf(stderr, "%c%c", tab[i][j], "\n "[j != 13]);
    }
}

TreeNode *findPath (int **tab, Set set, Tile *tile, char color, int uod) {
    const char errmsg[] = "Erro ao achar um caminho\n"
    int count = 0, minSize, i;
    TreeNode **Nodes;
    TreeNode *newNode;
    Tiles **negh;
    if (color == 'b' && tab[tile->lin][tile->col] == 'p')
        return NULL;
    if (color == 'p' && tab[tile->lin][tile->col] == 'b')
        return NULL;
    newNode = emalloc(sizeof(TreeNode), errmsg);
    newNode->tile = tileCreate(tile->lin, tile->col);
    newNode->lNode = NULL;
    newNode->rNode = NULL;
    newNode->size = 1;
    newNode->depth = 0;
    /*1 = up/left*/
    if (uod == 1) {
        if (color == 'b' && tile->lin == 13)
            return newNode;
        if (color == 'p' && tile->col == 13)
            return newNode;
    }
    /*0 = down/rigth*/
    else {
        if (color == 'b' && tile->lin == 0)
            return newNode;
        if (color == 'p' && tile->col == 0)
            return newNode;
    }
    Nodes = emalloc(5*sizeof(*TreeNode));
    neigh = findNeighbors(tile);
    if (neigh[0] != NULL && tilecmp(neigh[0], ptile) != 0 && !SFind(set, neigh[0])) {
        Nodes[count] = findPath(tab, tile, neigh[0], color, uod);
        count++;
    }
    if (neigh[1] != NULL && tilecmp(neigh[1], ptile) != 0 && !SFind(set, neigh[1])) {
        Nodes[count] = findPath(tab, tile, neigh[1], color, uod);
        count++;
    }
    if (neigh[2] != NULL && tilecmp(neigh[2], ptile) != 0 && !SFind(set, neigh[2])) {
        Nodes[count] = findPath(tab, tile, neigh[2], color, uod);
        count++;
    }
    if (neigh[3] != NULL && tilecmp(neigh[3], ptile) != 0 && !SFind(set, neigh[3])) {
        Nodes[count] = findPath(tab, tile, neigh[3], color, uod);
        count++;
    }
    if (neigh[4] != NULL && tilecmp(neigh[4], ptile) != 0 && !SFind(set, neigh[4])) {
        Nodes[count] = findPath(tab, tile, neigh[4], color, uod);
        count++;
    }
    if (neigh[5] != NULL && tilecmp(neigh[5], ptile) != 0 && !SFind(set, neigh[5])) {
        Nodes[count] = findPath(tab, tile, neigh[5], color, uod);
        count++;
    }
    for (i = 0; i < count; i++) {
        if (Nodes[i])
    }
}

int beginGame (int **tab, char color, int printTab) {
    int turn = 0, col, lin;
    Tile *ret = NULL;
    srand(time(NULL));
    if (color == 'b') {
        ret = play(tab);
        tab[ret->lin][ret->col] = 'b';
        turn++;
        if (printTab)
            printGame(tab);
    }
    while (noWinner(tab)) {
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
        } while (!isValid(tab, lin, col));
        turn++;
        tab[lin][col] = (color == 'b')? 'p' : 'b';
        ret = play(tab);
        tab[ret->lin][ret->col] = color;
        if (printTab)
            printGame(tab);
        free(ret);
    }
    return 1;
}
