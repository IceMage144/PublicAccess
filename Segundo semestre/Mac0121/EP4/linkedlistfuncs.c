/*
	Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlistfuncs.h"
#include "auxfuncs.h"

/*Cria funções comuns entre as tabelas de símbolo implementadas com lista
ligada desordenada e ordenada*/

LLST *LLTableCreate () {
	const char errmsg[] = "A tabela de símbolos não pode ser alocada\n";
	LLST *Ret;
	LLNode *Head;
	Ret = emalloc(sizeof(LLST), errmsg);
	Head = emalloc(sizeof(LLNode), errmsg);
	Ret->top = 0;
	Ret->head = Head;
	Head->key = NULL;
	Head->next = NULL;
	return Ret;
}

void LLTableDestroy (LLST *Table) {
	LLNode *curr, *next;
	next = Table->head;
	curr = NULL;
	free(Table);
	while (next != NULL) {
		curr = next;
		next = next->next;
		free(curr->key);
		free(curr);
	}
}

int strcompL (LLNode *node1, LLNode *node2) {
	int comp;
	comp = strcmp(node1->key, node2->key);
	return comp;
}

int valcompL (LLNode *node1, LLNode *node2) {
	if (node1->value < node2->value)
		return -1;
	if (node1->value > node2->value)
		return 1;
	return 0;
}

void mergeL (LLNode *beg, LLNode *mid, LLNode *end, int (*comp)(LLNode*, LLNode*)) {
    LLNode *auxNode1, *auxNode2, *currNode;
    currNode = beg;
    auxNode1 = beg->next;
    auxNode2 = mid;
    while (auxNode1 != mid && auxNode2 != end) {
        if (comp(auxNode1, auxNode2) < 0){
            currNode->next = auxNode2;
            currNode = auxNode2;
            auxNode2 = auxNode2->next;
        }
        else {
            currNode->next = auxNode1;
            currNode = auxNode1;
            auxNode1 = auxNode1->next;
        }
    }
    while (auxNode1 != mid) {
        currNode->next = auxNode1;
        currNode = auxNode1;
        auxNode1 = auxNode1->next;
    }
    while (auxNode2 != end) {
        currNode->next = auxNode2;
        currNode = auxNode2;
        auxNode2 = auxNode2->next;
    }
    currNode->next = end;
}

void mergeSortL (LLNode *beg, LLNode *end, int size, int (*comp)(LLNode*, LLNode*)) {
    int i = 0;
    LLNode *mid;
    mid = beg;
    if (size > 1) {
        while (i < size/2){
            mid = mid->next;
            i++;
        }
        mergeSortL(beg, mid->next, i, comp);
        i = 0;
        mid = beg;
        while (i < size/2){
            mid = mid->next;
            i++;
        }
        mergeSortL(mid, end, size-i, comp);
        mergeL(beg, mid->next, end, comp);
    }
}