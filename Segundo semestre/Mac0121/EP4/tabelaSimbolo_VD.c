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

/*Biblioteca com funções sobre a tabela de símbolos implementada com
vetor desordenado*/

/*Adiciona uma chave "key" à uma tablela de símbolos desordenada "Table", do
tipo vetor, e retorna um InsertionResult, com um ponteiro para o campo
"value" associado à "key" e com a variável new igual à 1 se a chave é nova,
ou 0 caso contrário*/
InsertionResult *UVAdd (VST *Table, const char *key) {
    const char errmsg1[] = "A chave não pode ser adicionada na tabela\n";
    const char errmsg2[] = "Uma estrutura auxiliar não pode ser alocada\n";
    int i = 0, pos = 0;
    InsertionResult *res;
    Entry *Taux;
    res = emalloc(sizeof(InsertionResult), errmsg2);
    while (pos != Table->top && strcmp(Table->data[pos].key, key) != 0)
        pos++;
    if (pos == Table->top) {
        if (Table->top == Table->maxPos) {
            Taux = emalloc(2*Table->maxPos*sizeof(Entry), errmsg1);
            for (i = 0; i < Table->maxPos; i++)
                Taux[i] = Table->data[i];
            free(Table->data);
            Table->data = Taux;
            Table->maxPos *= 2;
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

/*Função que imprime a tabela de símbolos desordenada "Table", do tipo vetor,
na saída padrão, com seus elementos ordenados por ordem de ocorrência*/
void UVPrintVal (VST *Table, int topChar) {
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

/*Função que imprime a tabela de símbolos desordenada "Table", do tipo vetor,
na saída padrão, com seus elementos ordenados por ordem alfabética*/
void UVPrintLexi (VST *Table, int topChar) {
    int i, j, len;
    mergeSortV(Table, 0, Table->top-1, strcompV);
    for (i = 0; i < Table->top; i++) {
        len = strlen(Table->data[i].key);
        printf("%s", Table->data[i].key);
        for (j = len; j <= topChar; j++)
            printf(" ");
        printf("%d\n", Table->data[i].value);
    }
}