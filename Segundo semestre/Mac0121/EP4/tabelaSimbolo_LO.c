/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "linkedlistfuncs.h"
#include "tabelaSimbolo_LO.h"
#include "auxfuncs.h"
#include "buffer.h"

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

void OLLPrintFreq (LLST *Table) {
    LLNode *auxNode;
    mergeSortL(Table->head, NULL, Table->top, valcompL);
    auxNode = (Table->head)->next;
    while (auxNode != NULL) {
        printf("%s : %d\n", auxNode->key, auxNode->value);
        auxNode = auxNode->next;
    }

}

void OLLPrintLexi (LLST *Table) {
    LLNode *auxNode;
    auxNode = (Table->head)->next;
    while (auxNode != NULL) {
        printf("%s : %d\n", auxNode->key, auxNode->value);
        auxNode = auxNode->next;
    }
}

void executeOLL (FILE *input, char ordType) {
    int beg = 0, len = 0, redChars, i;
    const char errmsg[] = "A string auxiliar não pode ser alocada\n";
    char *strAux;
    LLST *Table;
    Buffer *Buff;
    Table = LLTableCreate();
    Buff = BufferCreate();
    redChars = readLine(input, Buff);
    while (redChars) {
        while (beg < Buff->top){
            while (!isalpha(Buff->data[beg]) && beg < Buff->top)
                beg++;
            while (isalnum(Buff->data[beg+len]) && beg+len < Buff->top)
                len++;
            if (!len)
                break;
            strAux = emalloc(len*sizeof(char), errmsg);
            strAux[len+1] = 0;
            for (i = 0; i < len; i++)
                strAux[i] = Buff->data[beg+i];
            OLLPush(Table, strAux);
            beg += len;
            len = 0;
            free(strAux);
        }
        redChars = readLine(input, Buff);
        beg = 0;
    }
    if (ordType == 'O')
        OLLPrintFreq(Table);
    else
        OLLPrintLexi(Table);
    BufferDestroy(Buff);
    LLTableDestroy(Table);
}