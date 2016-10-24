/*
	Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
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