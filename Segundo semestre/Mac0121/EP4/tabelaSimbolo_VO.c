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

/*Biblioteca com funções sobre a tabela de símbolos implementada com
vetor ordenado*/

/*Função auxiliar da função OVAdd. Recebe uma tabela "Table", implementada
com vetor, e uma chave "key". A função procura a chave na tabela. Se
encontrá-la, retorna a posição da chave, caso contrário, retorna a posição
em que a chava deveria estar*/
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

/*Adiciona uma chave "key" à uma tablela de símbolos ordenada "Table", do
tipo vetor, e retorna um InsertionResult, com um ponteiro para o campo
"value" associado à "key" e com a variável new igual à 1 se a chave é nova,
ou 0 caso contrário*/
InsertionResult *OVAdd (VST *Table, const char *key) {
    const char errmsg1[] = "A chave não pode ser adicionada na tabela\n";
    const char errmsg2[] = "Uma estrutura auxiliar não pode ser alocada\n";
    int i = 0, pos;
    Entry *Taux;
    InsertionResult *res;
    res = emalloc(sizeof(InsertionResult), errmsg2);
    pos = binSearch(Table, key);
    if (pos == Table->top || strcmp(Table->data[pos].key, key) != 0) {
        if (Table->top == Table->maxPos) {
            Taux = emalloc(2*Table->maxPos*sizeof(Entry), errmsg1);
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
        res->new = 1;
        res->value = &(Table->data[pos].value);
        (Table->top)++;
    }
    else {
        res->new = 0;
        res->value = &(Table->data[pos].value);
    }
    return res;
}

/*Função que imprime a tabela de símbolos ordenada "Table", do tipo vetor,
na saída padrão, com seus elementos ordenados por ordem de ocorrência*/
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

/*Função que imprime a tabela de símbolos ordenada "Table", do tipo vetor,
na saída padrão, com seus elementos ordenados por ordem alfabética*/
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