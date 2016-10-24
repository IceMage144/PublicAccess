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

void BTTableDestroy (BtNode *Root);

void BTPush (BTNode *Root, const char *key);

void BTPrintLexi (BTNode *Root);

void BTPrintFreq (BTNode *Root);

void executeBT (FILE *input, char ordType);

#endif