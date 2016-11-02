/*
	Biblioteca feita por João Gabriel Basi
*/

#ifndef __TABELASIMBOLO_AB_H__
#define __TABELASIMBOLO_AB_H__

#include <stdio.h>

typedef struct btnode_t {
	char *key;
	int value;
	struct btnode_t *lesser;
	struct btnode_t *greater;
} BTNode;

void BSTTableDestroy (BtNode *Root);

void BSTPush (BTNode *Root, const char *key);

void BSTPrintLexi (BTNode *Root);

void BSTPrintFreq (BTNode *Root);

void executeBST (FILE *input, char ordType);

#endif