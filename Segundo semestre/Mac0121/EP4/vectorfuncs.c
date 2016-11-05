/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vectorfuncs.h"
#include "auxfuncs.h"

/*Biblioteca com funções comuns entre as tabelas de símbolos implementadas
com vetor*/

/*Retorna um ponteiro para uma tabela de símbolos nova feita com vetor*/
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

/*Desaloca uma tabela de símbolos "Table" implementada com vetor*/
void VTableDestroy (VST *Table) {
    int i;
    for (i = 0; i < Table->top; i++) {
        free(Table->data[i].key);
    }
    free(Table->data);
    free(Table);
}

/*Adiciona uma "key" e um valor "value", associado à ela, no topo da
tabela de símbolos "Table" implementada com vetor*/
void VTablePush (VST *Table, const char *key, int value) {
    const char errmsg[] = "A tabela não pode ser impressa\n";
    Entry *auxEntry, *EntryList;
    int i;
    if (Table->top == Table->maxPos) {
        EntryList = emalloc(2*Table->maxPos*sizeof(Entry), errmsg);
        for (i = 0; i < Table->maxPos; i++)
            EntryList[i] = Table->data[i];
        free(Table->data);
        Table->data = EntryList;
        Table->maxPos *= 2;
    }
    auxEntry = emalloc(sizeof(Entry), errmsg);
    auxEntry->key = estrdup(key);
    auxEntry->value = value;
    Table->data[Table->top] = *auxEntry;
    (Table->top)++;
    free(auxEntry);
}

/*Recebe duas Entries e compara o campo "value" delas. Retorna 1 se o
"value" da segunda for maior que o da primeira, -1 se o contrário
acontecer e 0 se eles forem iguais*/
int valcompV (Entry *Entry1, Entry *Entry2) {
    if (Entry1->value > Entry2->value)
        return -1;
    if (Entry1->value < Entry2->value)
        return 1;
    return 0;
}

/*Recebe duas Entries e compara o campo "key" delas. Retorna um valor
positivo se o "key" da primeira for lexicograficamente maior que o da
segunda, -1 se o contrário acontecer e 0 se eles forem iguais*/
int strcompV (Entry *Entry1, Entry *Entry2) {
    return strcmp(Entry1->key, Entry2->key);
}

/*Função auxiliar do mergeSortV, que recebe uma tabela de símbolos "Table"
implementada com vetor, o começo "beg" do primeiro vetor ordenado, o fim "end"
do segundo vetor ordenado, e junta dois vetores ordenados de acordo com a
função fornecida*/
void mergeV (VST *Table, int beg, int end, int (*comp)(Entry*, Entry*)){
    const char errmsg[] = "Erro na impressão da tabela\n";
    int mid = (beg+end)/2;
    int pos = 0, aux1 = beg, aux2 = mid+1;
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

/*Organiza uma tabela "Table", implementada com vetor, da posição "beg" até
a posição "end", de acordo com a função "comp"*/
void mergeSortV (VST *Table, int beg, int end, int (*comp)(Entry*, Entry*)){
    int mid = (end+beg)/2;
    if (beg < end) {
        mergeSortV(Table, beg, mid, comp);
        mergeSortV(Table, mid+1, end, comp);
        mergeV(Table, beg, end, comp);
    }
}