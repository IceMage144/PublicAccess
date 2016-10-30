/*
	Biblioteca feita por João Gabriel Basi
*/

#ifndef __LINKEDLISTFUNCS_H__
#define __LINKEDLISTFUNCS_H__

typedef struct llnode_t {
	char *key;
	int value;
	struct llnode_t *next;
} LLNode;

typedef struct linkedlistst_t {
	int top;
	LLNode *head;
} LinkedListSTable;

#define LLST LinkedListSTable

LLST *LLTableCreate ();

void LLTableDestroy (LLST *Table);

int strcompL (LLNode *node1, LLNode *node2);

int valcompL (LLNode *node1, LLNode *node2);

void mergeSortL (LLNode *beg, LLNode *end, int size, int (*comp)(LLNode*, LLNode*));

#endif