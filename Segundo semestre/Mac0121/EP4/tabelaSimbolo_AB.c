/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linkedlistfuncs.h"
#include "tabelaSimbolo_AB.h"
#include "auxfuncs.h"
#include "vectorfuncs.h"

BTST *BSTTableCreate () {
    const char errmsg[] = "A tabela de símbolos não pode ser alocada\n";
    BTST *newTable;
    newTable = emalloc(sizeof(BTST), errmsg);
    newTable->top = 0;
    newTable->root = NULL;
    return newTable;
}

void BSTTableDestroyNode (BTNode *Node) {
    if (Node != NULL) {
        BSTTableDestroyNode(Node->left);
        BSTTableDestroyNode(Node->right);
        free(Node->key);
        free(Node);
    }
}

void BSTTableDestroy (BTST *Table) {
    BSTTableDestroyNode(Table->root);
    free(Table);
}

InsertionResult *BSTPush (BTST *Table, const char *key) {
    const char errmsg1[] = "A chave não pode ser adicionada na tabela\n";
    const char errmsg2[] = "Uma estrutura auxiliar não pode ser alocada\n";
    BTNode *auxNode, *newNode;
    InsertionResult *res;
    int comp;
    res = emalloc(sizeof(InsertionResult), errmsg2);
    auxNode = Table->root;
    newNode = NULL;
    if (auxNode != NULL) {
        comp = strcmp(key, auxNode->key);
        if (comp > 0)
            newNode = auxNode->right;
        else if (comp < 0)
            newNode = auxNode->left;
        else {
            res->new = 0;
            res->value = &(auxNode->value);
        }
        while (newNode != NULL && comp != 0) {
            comp = strcmp(key, newNode->key);
            if (comp > 0){
                auxNode = newNode;
                newNode = newNode->right;
            }
            else if (comp < 0) {
                auxNode = newNode;
                newNode = newNode->left;
            }
            else {
                res->new = 0;
                res->value = &(newNode->value);
            }
        }
        if (newNode == NULL && comp != 0) {
            newNode = emalloc(sizeof(BTNode), errmsg1);
            newNode->value = 0;
            newNode->key = estrdup(key);
            newNode->right = NULL;
            newNode->left = NULL;
            if (comp < 0)
                auxNode->left = newNode;
            else
                auxNode->right = newNode;
            res->new = 1;
            res->value = &(newNode->value);
            (Table->top)++;
        }
    }
    else {
        newNode = emalloc(sizeof(BTNode), errmsg1);
        newNode->value = 0;
        newNode->key = estrdup(key);
        newNode->right = NULL;
        newNode->left = NULL;
        Table->root = newNode;
        res->new = 1;
        res->value = &(newNode->value);
        (Table->top)++;
    }
    return res;
}

void BSTPrintLexi (BTNode *Table, int topChar) {
    int i, len;
    if (Table != NULL) {
        len = strlen(Table->key);
        BSTPrintLexi(Table->left, topChar);
        printf("%s", Table->key);
        for (i = len; i <= topChar; i++)
            printf(" ");
        printf("%d\n", Table->value);
        BSTPrintLexi(Table->right, topChar);
    }
}

void BSTPrintValTransf (BTNode *Node, VST *AuxTable) {
    int i;
    Entry *EntryList;
    const char errmsg[] = "A tabela não pode ser impressa\n";
    if (Node != NULL) {
        AuxTable->data[AuxTable->top].key = estrdup(Node->key);
        AuxTable->data[AuxTable->top].value = Node->value;
        (AuxTable->top)++;
        if (AuxTable->top == AuxTable->maxPos) {
            EntryList = emalloc(2*AuxTable->maxPos*sizeof(Entry), errmsg);
            for (i = 0; i < AuxTable->maxPos; i++)
                EntryList[i] = AuxTable->data[i];
            free(AuxTable->data);
            AuxTable->data = EntryList;
            AuxTable->maxPos *= 2;
        }
        BSTPrintValTransf(Node->left, AuxTable);
        BSTPrintValTransf(Node->right, AuxTable);
    }
}

void BSTPrintVal (BTST *Table, int topChar) {
    int i, j, len;
    VST *AuxTable;
    AuxTable = VTableCreate();
    BSTPrintValTransf(Table->root, AuxTable);
    mergeSortV(AuxTable, 0, (AuxTable->top)-1, valcompV);
    for (i = 0; i < Table->top; i++) {
        len = strlen(AuxTable->data[i].key);
        printf("%s", AuxTable->data[i].key);
        for (j = len; j <= topChar; j++)
            printf(" ");
        printf("%d\n", AuxTable->data[i].value);
    }
    VTableDestroy(AuxTable);
}