/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlistfuncs.h"
#include "tabelaSimbolo_LD.h"
#include "auxfuncs.h"


void ULLPush (LLST *Table, const char *key) {
    const char errmsg[] = "A chave não pode ser adicionada na tabela\n";
    LLNode *currNode, *newNode, *Head;
    int comp;
    Head = Table->head;
    currNode = Head->next;
    if (currNode != NULL) {
        comp = strcmp(currNode->key, key);
        while (currNode->next != NULL && comp != 0){
            currNode = currNode->next;
            comp = strcmp(currNode->key, key);
        }
        if (comp == 0)
            (currNode->value)++;
        else {
            newNode = emalloc(sizeof(LLNode), errmsg);
            newNode->key = estrdup(key);
            newNode->value = 1;
            newNode->next = NULL;
            currNode->next = newNode;
            (Table->top)++;
        }
    }
    else {
        newNode = emalloc(sizeof(LLNode), errmsg);
        newNode->key = estrdup(key);
        newNode->value = 1;
        newNode->next = NULL;
        Head->next = newNode;
        (Table->top)++;
    }
}

void ULLPrintVal (LLST *Table, int topChar) {
    int len, i;
    LLNode *auxNode;
    mergeSortL(Table->head, NULL, Table->top, valcompL);
    auxNode = (Table->head)->next;
    while (auxNode != NULL) {
        len = strlen(auxNode->key);
        printf("%s", auxNode->key);
        for (i = len; i <= topChar; i++)
            printf(" ");
        printf("%d\n", auxNode->value);
        auxNode = auxNode->next;
    }
}

void ULLPrintLexi (LLST *Table, int topChar) {
    int len, i;
    LLNode *auxNode;
    mergeSortL(Table->head, NULL, Table->top, strcompL);
    auxNode = (Table->head)->next;
    while (auxNode != NULL) {
        len = strlen(auxNode->key);
        printf("%s", auxNode->key);
        for (i = len; i <= topChar; i++)
            printf(" ");
        printf("%d\n", auxNode->value);
        auxNode = auxNode->next;
    }
}