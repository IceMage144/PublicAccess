/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vectorfuncs.h"
#include "auxfuncs.h"

/*Cria funções comuns entre as tabelas de símbolo implementadas com vetor
desordenado e ordenado*/

VST *VTableCreate () {
    const char errmsg[] = "A tabela de símbolos não pode ser alocada\n";
    VST *Ret;
    int i;
    Ret = emalloc(sizeof(VST), errmsg);
    Ret->data = emalloc(1024*sizeof(Entry), errmsg);
    for (i = 0; i < 1024; i++){
        Ret->data[i].key = NULL;
        Ret->data[i].value = 0;
    }
    Ret->top = 0;
    Ret->maxPos = 1024;
    return Ret;
}

void VTableDestroy (VST *Table) {
    int i;
    for (i = 0; i < Table->top; i++) {
        free(Table->data[i].key);
    }
    free(Table->data);
    free(Table);
}

int valcompV (Entry *Entry1, Entry *Entry2) {
    if (Entry1->value > Entry2->value)
        return -1;
    if (Entry1->value < Entry2->value)
        return 1;
    return 0;
}

int strcompV (Entry *Entry1, Entry *Entry2) {
    return strcmp(Entry1->key, Entry2->key);
}

void mergeV (VST *Table, int beg, int end, int (*comp)(Entry*, Entry*)){
    int mid = (beg+end)/2;
    int pos = 0, aux1 = beg, aux2 = mid+1;
    const char errmsg[] = "Erro na impressão da tabela\n";
    Entry *Vaux;
    Vaux = emalloc((end-beg+1)*sizeof(Entry), errmsg);
    while (aux1 <= mid && aux2 <= end) {
        if (comp(&(Table->data[aux1]), &(Table->data[aux2])) > 0){
            Vaux[pos] = Table->data[aux2];
            aux2++;
        }
        else {
            Vaux[pos] = Table->data[aux1];
            aux1++;
        }
        pos++;
    }
    while (aux1 <= mid) {
        Vaux[pos] = Table->data[aux1];
        aux1++;
        pos++;
    }
    while (aux2 <= end) {
        Vaux[pos] = Table->data[aux2];
        aux2++;
        pos++;
    }
    for (aux1 = 0; aux1 < pos; aux1++)
        Table->data[aux1+beg] = Vaux[aux1];
    free(Vaux);
}

void mergeSortV (VST *Table, int beg, int end, int (*comp)(Entry*, Entry*)){
    int mid = (end+beg)/2;
    if (beg < end) {
        mergeSortV(Table, beg, mid, comp);
        mergeSortV(Table, mid+1, end, comp);
        mergeV(Table, beg, end, comp);
    }
}