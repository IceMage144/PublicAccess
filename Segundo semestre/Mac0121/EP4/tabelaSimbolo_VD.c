/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vectorfuncs.h"
#include "tabelaSimbolo_VD.h"
#include "auxfuncs.h"
#include "buffer.h"

void UVPush (VST *Table, const char *key) {
    int i = 0, pos = 0;
    const char errmsg[] = "A chave não pode ser adicionada na tabela\n";
    Entry *Taux;
    while (pos != Table->top && strcmp(Table->data[pos].key, key) != 0)
        pos++;
    if (pos == Table->top) {
        if (Table->top == Table->maxPos) {
            Taux = emalloc(2*Table->maxPos*sizeof(Entry), errmsg);
            for (i = 0; i < Table->maxPos; i++)
                Taux[i] = Table->data[i];
            free(Table->data);
            Table->data = Taux;
            Table->maxPos *= 2;
        }
        Table->data[pos].key = estrdup(key);
        Table->data[pos].value = 0;
        (Table->top)++;
    }
    (Table->data[pos].value)++;
}

void UVPrintFreq (VST *Table) {
    int i;
    mergeSortV(Table, 0, Table->top-1, valcompV);
    for (i = 0; i < Table->top; i++) {
        printf("%s : %d\n", Table->data[i].key, Table->data[i].value);
    }
}

void UVPrintLexi (VST *Table) {
    int i;
    mergeSortV(Table, 0, Table->top-1, strcompV);
    for (i = 0; i < Table->top; i++) {
        printf("%s : %d\n", Table->data[i].key, Table->data[i].value);
    }
}

void executeUV (FILE *input, char ordType) {
    int beg = 0, len = 0, redChars, i;
    const char errmsg[] = "A string auxiliar não pode ser alocada\n";
    char *strAux;
    VST *Table;
    Buffer *Buff;
    Table = VTableCreate();
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
            /*printf("%s\n", strAux);*/
            UVPush(Table, strAux);
            beg += len;
            len = 0;
            free(strAux);
        }
        redChars = readLine(input, Buff);
        beg = 0;
    }
    if (ordType == 'O')
        UVPrintFreq(Table);
    else
        UVPrintLexi(Table);
    BufferDestroy(Buff);
    VTableDestroy(Table);
}

