/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __AUXFUNCS_H__
#define __AUXFUNCS_H__

/*Biblioteca de funções que ajudam o programa a manusear a memória e
resumir operações*/

#define INF 2147483647

typedef struct tile_t {
    int lin, col;
} Tile;

/*typedef struct treenode_t {
    struct treenode_t *rNode;
    struct treenode_t *lNode;
    Tile *tile;
    int size, depth;
} TreeNode;*/

//typedef Set TreeNode*;

typedef struct btile_t {
    int lin, col;
    char color;
    struct btile_t **Neigh;
    int **weigths;
} BTile;

/*Aloca espaço de tamanho "size" na memória, e, se a alocação falhar,
mostra a mensagem "msg" na saída de erros*/
void *emalloc (size_t size, const char *msg);

//int SAdd (Set set, Tile *tile);

//Tile *tileCreate (int lin, int col);

//Tile **findNeighbors (Tile *tile);

//int tilecmp (Tile *tile1, Tile *tile2);

#endif
