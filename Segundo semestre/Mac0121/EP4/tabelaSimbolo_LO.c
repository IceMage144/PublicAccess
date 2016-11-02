/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlistfuncs.h"
#include "tabelaSimbolo_LO.h"
#include "auxfuncs.h"

void OLLPush (LLST *Table, const char *key) {
    const char errmsg[] = "A chave não pode ser adicionada na tabela\n";
    LLNode *currNode, *newNode, *memNode, *Head;
    int comp;
    memNode = NULL;
    Head = Table->head;
    currNode = Head->next;
    if (currNode != NULL && strcmp(currNode->key, key) <= 0) {
        comp = strcmp(currNode->key, key);
        while (currNode->next != NULL && comp < 0){
            memNode = currNode;
            currNode = currNode->next;
            comp = strcmp(currNode->key, key);
        }
        if (comp == 0)
            (currNode->value)++;
        else {
            newNode = emalloc(sizeof(LLNode), errmsg);
            newNode->key = estrdup(key);
            newNode->value = 1;
            if (comp > 0) {
                newNode->next = memNode->next;
                memNode->next = newNode;
            }
            else {
                newNode->next = NULL;
                currNode->next = newNode;
            }
            (Table->top)++;
        }
    }
    else {
        newNode = emalloc(sizeof(LLNode), errmsg);
        newNode->key = estrdup(key);
        newNode->value = 1;
        newNode->next = Head->next;
        Head->next = newNode;
        (Table->top)++;
    }
}

void OLLPrintVal (LLST *Table, int topChar) {
    int i, len;
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

void OLLPrintLexi (LLST *Table, int topChar) {
    int i, len;
    LLNode *auxNode;
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