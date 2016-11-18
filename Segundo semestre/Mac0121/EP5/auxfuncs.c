/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>

/*Biblioteca de funções que ajudam o programa a manusear a memória*/

/*Aloca espaço de tamanho "size" na memória, e, se a alocação falhar,
mostra a mensagem "msg" na saída de erros*/
void *emalloc (size_t size, const char *msg) {
    int *Ret;
    Ret = malloc(size);
    if (Ret == NULL) {
        fprintf(stderr, "%s", msg);
        exit(1);
    }
    return Ret;
}
/*
Adiciona uma chave "key" à uma tablela de símbolos "Table", do tipo
árvore de busca binária, e retorna um InsertionResult, com um ponteiro
para o campo value associado à "key" e com a variável new igual à 1 se
a chave é nova, ou 0 caso contrário
int SAdd (Set set, const Tile *tile) {
    const char errmsg[] = "A posição não pode ser adicionada no conjunto\n";
    TreeNode *auxNode, *newNode;
    int comp;
    auxNode = set;
    if (auxNode != NULL) {
        comp = tilecmp(tile, auxNode->tile);
        while (auxNode != NULL && comp != 0) {
            comp = tilecmp(tile, auxNode->tile);
            if (comp > 0)
                auxNode = auxNode->rNode;
            else if (comp < 0)
                auxNode = auxNode->lNode;
            else
                return 0;
        }
        if (auxNode == NULL) {
            newNode = emalloc(sizeof(TreeNode), errmsg);
            newNode->rNode = NULL;
            newNode->lNode = NULL;
            newNode->tile = tileCreate(tile->lin, tile->col);
            if (comp < 0)
                auxNode->left = newNode;
            else
                auxNode->right = newNode;
            return 1;
        }
    }
    else {
        newNode = emalloc(sizeof(TreeNode), errmsg);
        newNode->rNode = NULL;
        newNode->lNode = NULL;
        newNode->tile = tileCreate(tile->lin, tile->col);
        set = newNode;
        return 1;
    }
}

int SFind (Set set, const Tile *tile) {
    TreeNode *auxNode;
    auxNode = set;
    if (auxNode != NULL) {
        comp = tilecmp(tile, auxNode->tile);
        while (auxNode != NULL && comp != 0) {
            comp = tilecmp(tile, auxNode->tile);
            if (comp > 0)
                auxNode = auxNode->rNode;
            else if (comp < 0)
                auxNode = auxNode->lNode;
            else
                return 1;
        }
    }
    return 0;
}

Tile *tileCreate (int lin, int col) {
    const char errmsg[] = "Uma posição não pode ser alocada\n";
    Tile *ret;
    ret = emalloc(sizeof(Tile), errmsg);
    ret->lin = lin;
    ret->col = col;
    return ret;
}

Tile **findNeighbors (Tile *tile) {
    Tile **ret;
    ret = emalloc(6*sizeof(*Tile));
    if (col + 1 < 14) {
        ret[1] = tileCreate(lin, col+1);
        if (lin - 1 >= 0)
            ret[2] = tileCreate(lin-1, col+1);
        else
            ret[2] = NULL;
    }
    else {
        ret[1] = NULL;
        ret[2] = NULL;
    }
    if (col - 1 >= 0) {
        ret[3] = tileCreate(lin, col-1);
        if (lin + 1 < 14)
            ret[4] = tileCreate(lin+1, col-1);
        else
            ret[4] = NULL;
    }
    else {
        ret[3] = NULL;
        ret[4] = NULL;
    }
    if (lin + 1 < 14)
        ret[5] = tileCreate(lin+1, col);
    else
        ret[5] = NULL;
    if (lin - 1 >= 0)
        ret[6] = tileCreate(lin-1, col);
    else
        ret[6] = NULL;
    return ret;
}

int tilecmp (const Tile *tile1, const Tile *tile2) {
    if (tile1->lin < tile2->lin)
        return -1;
    if (tile1->lin > tile2->lin)
        return 1;
    if (tile1->col < tile2->col)
        return -1;
    if (tile1->col > tile2->col)
        return 1;
    return 0;
}
*/
