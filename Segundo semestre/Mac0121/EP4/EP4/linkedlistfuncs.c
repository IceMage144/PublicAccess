/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdlib.h>
#include "linkedlistfuncs.h"
#include "auxfuncs.h"

/*Biblioteca com funções comuns entre as tabelas de símbolos implementadas
com lista ligada*/

/*Retorna um ponteiro para uma tabela de símbolos nova feita com lista
ligada*/
LLST *LLTableCreate () {
    const char errmsg[] = "A tabela de símbolos não pode ser alocada\n";
    LLST *Ret;
    Ret = emalloc(sizeof(LLST), errmsg);
    Ret->top = 0;
    Ret->head = NULL;
    return Ret;
}

/*Desaloca uma tabela de símbolos "Table" implementada com lista ligada*/
void LLTableDestroy (LLST *Table) {
    LLNode *curr, *next;
    next = Table->head;
    curr = NULL;
    free(Table);
    while (next != NULL) {
        curr = next;
        next = next->next;
        free(curr->key);
        free(curr);
    }
}