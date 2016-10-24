/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlistfuncs.h"
#include "tabelaSimbolo_LD.h"
#include "auxfuncs.h"

void ULLPush (LLST *Table, const char *key) {
	const char errmsg[] = "A chave não pode ser adicionada na tabela\n"
	Node *auxNode, *newNode;
	int comp;
	auxNode = Table->head;
	comp = strcmp(auxNode->key, key);
	while (auxNode->next != NULL && comp != 0) {
		auxNode = auxNode->next;
		comp = strcmp(auxNode->key, key);
	}
	if (comp > 0) {
		newNode = emalloc(sizeof(Node), errmsg);
		newNode->key = emalloc(strlen(key)*sizeof(char));
		strcpy(newNode->key, key);
		newNode->value = 1;
		newNode->next = NULL;
		auxNode->next = newNode;
	}
	else 
		(auxNode->value)++;
}

void ULLPrintFreq (LLST *Table);

void ULLPrintLexi (LLST *Table);