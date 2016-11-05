/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __VECTORFUNCS_H__
#define __VECTORFUNCS_H__

/*Biblioteca com funções comuns entre as tabelas de símbolos implementadas
com vetor*/

/*Registro para vetor*/
typedef struct entry_t {
    char *key;
    int value;
} Entry;

/*Base para vetor*/
typedef struct vectorst_t {
    int top, maxPos;
    Entry *data;
} VectorSTable;

#define VST VectorSTable

/*Retorna um ponteiro para uma tabela de símbolos nova feita com vetor*/
VST *VTableCreate ();

/*Desaloca uma tabela de símbolos "Table" implementada com vetor*/
void VTableDestroy (VST *Table);

/*Adiciona uma "key" e um valor "value", associado à ela, no topo da
tabela de símbolos "Table" implementada com vetor*/
void VTablePush (VST *Table, const char *key, int value);

/*Recebe duas Entries e compara o campo "value" delas. Retorna 1 se o
"value" da segunda for maior que o da primeira, -1 se o contrário
acontecer e 0 se eles forem iguais*/
int valcompV (Entry *Entry1, Entry *Entry2);

/*Recebe duas Entries e compara o campo "key" delas. Retorna um valor
positivo se o "key" da primeira for lexicograficamente maior que o da
segunda, -1 se o contrário acontecer e 0 se eles forem iguais*/
int strcompV (Entry *Entry1, Entry *Entry2);

/*Organiza uma tabela "Table", implementada com vetor, da posição "beg" até
a posição "end", de acordo com a função "comp"*/
void mergeSortV (VST *Table, int beg, int end, int (*comp)(Entry*, Entry*));

#endif