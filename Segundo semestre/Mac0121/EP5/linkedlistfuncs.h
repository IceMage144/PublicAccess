/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __LINKEDLISTFUNCS_H__
#define __LINKEDLISTFUNCS_H__

#include "auxfuncs.h"

/*Biblioteca com funções comuns entre as tabelas de símbolos implementadas
com lista ligada*/

/*Nó para lista ligada*/
typedef struct llnode_t {
    Tile *tile;
    struct llnode_t *next;
    struct llnode_t *prev;
} LLNode;

/*Cabeça para lista ligada*/
typedef LLNode* LinkedList;

typedef struct path_t {
    LLNode *node;
    int tiles;
    int stones;
} Path;

/*Retorna um ponteiro para uma tabela de símbolos nova feita com lista
ligada*/
/*LinkedList *LLCreate ();*/

/*Adiciona uma chave "key" à uma tablela de símbolos desordenada "Table", do
tipo vetor, e retorna um InsertionResult, com um ponteiro para o campo
"value" associado à "key" e com a variável new igual à 1 se a chave é nova,
ou 0 caso contrário*/
void LLAdd (LinkedList Path, Tile *tile);

void LLNormalize (LinkedList Path);

/*Desaloca uma tabela de símbolos "Table" implementada com lista ligada*/
void LLDestroy (LinkedList Path);

#endif
