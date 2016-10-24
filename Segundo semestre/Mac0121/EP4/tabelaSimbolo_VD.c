/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vectorfuncs.h"
#include "tabelaSimbolo_VD.h"
#include "auxfuncs.h"

int intcmp (Entry *Entry1, Entry *Entry2) {
    if (Entry1->value == Entry2->value)
        return 0;
    if (Entry1->value < Entry2->value)
        return -1;
    return 1;
}

int keycmp (Entry *Entry1, Entry *Entry2) {
    return strcmp(Entry1->key, Entry2->key);
}


void intercala (VST *Table, int beg, int end, int (*comp)(Entry*, Entry*)){
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

void mergeSort (VST *Table, int beg, int end, int (*comp)(Entry*, Entry*)){
    int mid = (end+beg)/2;
    if (beg < end) {
        mergeSort(Table, beg, mid, comp);
        mergeSort(Table, mid+1, end, comp);
        intercala(Table, beg, end, comp);
    }
}

void adicionaVD (VST *Table, const char *chave) {
    int i = 0;
    const char errmsg[] = "A chave não pode ser adicionada na tabela\n";
    char *aux;
    Entry *Taux;
    while (i < Table->maxPos && strcmp(chave, Table->data[i].key))
        i++;
    if (i == Table->top) {
        if (Table->top == Table->maxPos) {
            Taux = emalloc(2*Table->maxPos*sizeof(Entry), errmsg);
            for (i = 0; i < Table->maxPos; i++)
                Taux[i] = Table->data[i];
            for (; i < 2*Table->maxPos; i++)
                Taux[i].value = 0;
            free(Table->data);
            Table->data = Taux;
            Table->maxPos *= 2;
        }
        aux = emalloc(strlen(chave)*sizeof(char), errmsg);
        strcpy(aux, chave);
        Table->data[i].key = aux;
    }
    (Table->data[i].value)++;
}
/*
void UVPrintFreq (VST *Table) {
    mergeSort(Table, )
}

void UVPrintLexi (VST *Table) {

}*/
