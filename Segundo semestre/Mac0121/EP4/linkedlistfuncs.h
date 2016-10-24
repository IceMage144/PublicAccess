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
	Node *head;
} LinkedListSTable;

#define LLST LinkedListSTable

LLST *LLTableCreate ();

void LLTableDestroy (LLST *Table);

#endif