/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __TABELASIMBOLO_AB_H__
#define __TABELASIMBOLO_AB_H__

#include "auxfuncs.h"

typedef struct btnode_t {
    char *key;
    int value;
    struct btnode_t *left;
    struct btnode_t *right;
} BTNode;

typedef struct btst_t {
    int top;
    BTNode *root;
} BinaryTreeSTable;

#define BTST BinaryTreeSTable

BTST *BSTTableCreate ();

void BSTTableDestroy (BTST *Table);

void BSTTableDestroyNode (BTNode *Node);

InsertionResult *BSTPush (BTST *Table, const char *key);

void BSTPrintLexi (BTNode *Table, int topChar);

void BSTPrintVal (BTST *Table, int topChar);

#endif