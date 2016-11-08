/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlistfuncs.h"
#include "tabelaSimbolo_LD.h"
#include "vectorfuncs.h"
#include "auxfuncs.h"

/*Biblioteca com funções sobre a tabela de símbolos implementada com
lista ligada desordenada*/

/*Adiciona uma chave "key" à uma tablela de símbolos desordenada "Table", do
tipo lista ligada, e retorna um InsertionResult, com um ponteiro para o campo
"value" associado à "key" e com a variável new igual à 1 se a chave é nova,
ou 0 caso contrário*/
InsertionResult *ULLAdd (LLST *Table, const char *key) {
    const char errmsg1[] = "A chave não pode ser adicionada na tabela\n";
    const char errmsg2[] = "Uma estrutura auxiliar não pode ser alocada\n";
    LLNode *currNode, *newNode;
    InsertionResult *res;
    int comp;
    res = emalloc(sizeof(InsertionResult), errmsg2);
    currNode = Table->head;
    if (currNode != NULL) {
        comp = strcmp(currNode->key, key);
        while (currNode->next != NULL && comp != 0){
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
            newNode->next = NULL;
            currNode->next = newNode;
            res->new = 1;
            res->value = &(newNode->value);
            (Table->top)++;
        }
    }
    else {
        newNode = emalloc(sizeof(LLNode), errmsg1);
        newNode->key = estrdup(key);
        newNode->value = 0;
        newNode->next = NULL;
        Table->head = newNode;
        res->new = 1;
        res->value = &(newNode->value);
        (Table->top)++;
    }
    return res;
}

/*Função que imprime a tabela de símbolos desordenada "Table", do tipo lista
ligada, na saída padrão, com seus elementos ordenados por ordem de ocorrência*/
void ULLPrintVal (LLST *Table, int topChar) {
    LLNode *auxNode;
    VST *AuxTable;
    int len, i, j;
    AuxTable = VTableCreate();
    for (auxNode = Table->head; auxNode != NULL; auxNode = auxNode->next)
        VTablePush(AuxTable, auxNode->key, auxNode->value);
    mergeSortV(AuxTable, 0, AuxTable->top, valcompV);
    for (i = 0; i < Table->top; i++) {
        len = strlen(AuxTable->data[i].key);
        printf("%s", AuxTable->data[i].key);
        for (j = len; j <= topChar; j++)
            printf(" ");
        printf("%d\n", AuxTable->data[i].value);
    }
    VTableDestroy(AuxTable);
}

/*Função que imprime a tabela de símbolos desordenada "Table", do tipo lista
ligada, na saída padrão, com seus elementos ordenados por ordem alfabética*/
void ULLPrintLexi (LLST *Table, int topChar) {
    LLNode *auxNode;
    VST *AuxTable;
    int len, i, j;
    AuxTable = VTableCreate();
    for (auxNode = Table->head; auxNode != NULL; auxNode = auxNode->next)
        VTablePush(AuxTable, auxNode->key, auxNode->value);
    mergeSortV(AuxTable, 0, (AuxTable->top)-1, strcompV);
    for (i = 0; i < Table->top; i++) {
        len = strlen(AuxTable->data[i].key);
        printf("%s", AuxTable->data[i].key);
        for (j = len; j <= topChar; j++)
            printf(" ");
        printf("%d\n", AuxTable->data[i].value);
    }
    VTableDestroy(AuxTable);
}