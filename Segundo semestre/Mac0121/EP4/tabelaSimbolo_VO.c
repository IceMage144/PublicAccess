/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vectorfuncs.h"
#include "tabelaSimbolo_VO.h"
#include "auxfuncs.h"

int binSearch (VST *Table, const char *key) {
    int beg = 0, end = Table->top, mid = (end+beg)/2, comp;
    while (end > beg) {
        comp = strcmp(Table->data[mid].key, key);
        if (comp == 0)
            return mid;
        if (comp > 0)
            end = mid-1;
        else
            beg = mid+1;
        mid = (end+beg)/2;
    }
    if (mid == Table->top)
        return mid;
    comp = strcmp(Table->data[mid].key, key);
    if (comp < 0)
        return mid+1;
    return mid;
}

void OVPush (VST *Table, const char *key) {
    int i = 0, pos;
    const char errmsg[] = "A chave não pode ser adicionada na tabela\n";
    Entry *Taux;
    pos = binSearch(Table, key);
    if (pos == Table->top || strcmp(Table->data[pos].key, key) != 0) {
        if (Table->top == Table->maxPos) {
            Taux = emalloc(2*Table->maxPos*sizeof(Entry), errmsg);
            for (i = 0; i < Table->maxPos; i++)
                Taux[i] = Table->data[i];
            free(Table->data);
            Table->data = Taux;
            Table->maxPos *= 2;
        }
        for (i = Table->top; i > pos; i--) {
            Table->data[i] = Table->data[i-1];
        }
        Table->data[pos].key = estrdup(key);
        Table->data[pos].value = 0;
        (Table->top)++;
    }
    (Table->data[pos].value)++;
}

void OVPrintVal (VST *Table, int topChar) {
    int i, j, len;
    mergeSortV(Table, 0, Table->top-1, valcompV);
    for (i = 0; i < Table->top; i++) {
        len = strlen(Table->data[i].key);
        printf("%s", Table->data[i].key);
        for (j = len; j <= topChar; j++)
            printf(" ");
        printf("%d\n", Table->data[i].value);
    }
}

void OVPrintLexi (VST *Table, int topChar) {
    int i, j, len;
    for (i = 0; i < Table->top; i++) {
        len = strlen(Table->data[i].key);
        printf("%s", Table->data[i].key);
        for (j = len; j <= topChar; j++)
            printf(" ");
        printf("%d\n", Table->data[i].value);
    }
}