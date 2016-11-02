/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "linkedlistfuncs.h"
#include "tabelaSimbolo_LD.h"
#include "auxfuncs.h"
#include "buffer.h"


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

void ULLPrintFreq (LLST *Table) {
	LLNode *auxNode;
    mergeSortL(Table->head, NULL, Table->top, valcompL);
    auxNode = (Table->head)->next;
    while (auxNode != NULL) {
        printf("%s : %d\n", auxNode->key, auxNode->value);
        auxNode = auxNode->next;
    }
}

void ULLPrintLexi (LLST *Table) {
	LLNode *auxNode;
    mergeSortL(Table->head, NULL, Table->top, strcompL);
    auxNode = (Table->head)->next;
    while (auxNode != NULL) {
        printf("%s : %d\n", auxNode->key, auxNode->value);
        auxNode = auxNode->next;
    }
}

void executeULL (FILE *input, char ordType) {
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
            while (beg < Buff->top && !isalpha(Buff->data[beg]))
                beg++;
            while (beg+len < Buff->top && isalnum(Buff->data[beg+len]))
                len++;
            if (!len)
                break;
            strAux = emalloc((len+1)*sizeof(char), errmsg);
            strAux[len] = 0;
            for (i = 0; i < len; i++)
                strAux[i] = tolower(Buff->data[beg+i]);
            ULLPush(Table, strAux);
            beg += len;
            len = 0;
            free(strAux);
        }
        redChars = readLine(input, Buff);
        beg = 0;
    }
    if (ordType == 'O')
        ULLPrintFreq(Table);
    else
        ULLPrintLexi(Table);
    BufferDestroy(Buff);
    LLTableDestroy(Table);
}
