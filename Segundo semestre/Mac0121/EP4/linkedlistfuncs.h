/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __LINKEDLISTFUNCS_H__
#define __LINKEDLISTFUNCS_H__

/*Biblioteca com funções comuns entre as tabelas de símbolos implementadas
com lista ligada*/

/*Nó para lista ligada*/
typedef struct llnode_t {
    char *key;
    int value;
    struct llnode_t *next;
} LLNode;

/*Cabeça para lista ligada*/
typedef struct linkedlistst_t {
    int top;
    LLNode *head;
} LinkedListSTable;

#define LLST LinkedListSTable

/*Retorna um ponteiro para uma tabela de símbolos nova feita com lista
ligada*/
LLST *LLTableCreate ();

/*Desaloca uma tabela de símbolos "Table" implementada com lista ligada*/
void LLTableDestroy (LLST *Table);

#endif