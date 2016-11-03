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

InsertionResult *OLLPush (LLST *Table, const char *key) {
    const char errmsg1[] = "A chave não pode ser adicionada na tabela\n";
    const char errmsg2[] = "Uma estrutura auxiliar não pode ser alocada\n";
    LLNode *currNode, *newNode, *memNode;
    InsertionResult *res;
    int comp;
    res = emalloc(sizeof(InsertionResult), errmsg2);
    memNode = NULL;
    currNode = Table->head;
    if (currNode != NULL && strcmp(currNode->key, key) <= 0) {
        comp = strcmp(currNode->key, key);
        while (currNode->next != NULL && comp < 0){
            memNode = currNode;
            currNode = currNode->next;
            comp = strcmp(currNode->key, key);
        }
        if (comp == 0) {
            res->new = 0;
            res->value = &(currNode->value);
        }
        else {
            newNode = emalloc(sizeof(LLNode), errmsg1);
            newNode->key = estrdup(key);
            newNode->value = 0;
            if (comp > 0) {
                newNode->next = memNode->next;
                memNode->next = newNode;
            }
            else {
                newNode->next = NULL;
                currNode->next = newNode;
            }
            res->new = 1;
            res->value = &(newNode->value);
            (Table->top)++;
        }
    }
    else {
        newNode = emalloc(sizeof(LLNode), errmsg1);
        newNode->key = estrdup(key);
        newNode->value = 0;
        newNode->next = Table->head;
        Table->head = newNode;
        res->new = 1;
        res->value = &(newNode->value);
        (Table->top)++;
    }
    return res;
}

void OLLPrintVal (LLST *Table, int topChar) {
    int i, len;
    LLNode *auxNode;
    mergeSortL(&(Table->head), NULL, Table->top, valcompL);
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