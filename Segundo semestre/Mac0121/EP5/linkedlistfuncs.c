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
/*
LinkedList *LLCreate () {
    const char errmsg[] = "A tabela de símbolos não pode ser alocada\n";
    LinkedList *Ret;
    Ret = emalloc(sizeof(LinkedList), errmsg);
    Ret->top = 0;
    Ret->head = NULL;
    return Ret;
}*/

/*Adiciona uma chave "key" à uma tablela de símbolos desordenada "Table", do
tipo lista ligada, e retorna um InsertionResult, com um ponteiro para o campo
"value" associado à "key" e com a variável new igual à 1 se a chave é nova,
ou 0 caso contrário*/
int LLAdd (LinkedList Path, Tile *tile) {
    const char errmsg[] = "A chave não pode ser adicionada na tabela\n";
    LLNode *currNode, *newNode;
    int comp;
    currNode = Path;
    if (currNode != NULL) {
        comp = tilecmp(currNode->tile, tile);
        while (currNode->next != NULL && comp != 0){
            currNode = currNode->next;
            comp = tilecmp(currNode->tile, tile);
        }
        if (comp == 0)
            return 0;
        else {
            newNode = emalloc(sizeof(LLNode), errmsg);
            newNode->tile = tile;
            newNode->next = Path;
            newNode->prev = NULL;
            Path = newNode;
        }
    }
    else {
        newNode = emalloc(sizeof(LLNode), errmsg);
        newNode->tile = tile;
        newNode->next = NULL;
        newNode->prev = NULL;
        Path = newNode;
    }
    return 1;
}

void LLNormalize (LinkedList *Path) {
    
}

/*Desaloca uma tabela de símbolos "Table" implementada com lista ligada*/
void LLTableDestroy (LinkedList Path) {
    LLNode *curr, *next;
    next = Path;
    curr = NULL;
    while (next != NULL) {
        curr = next;
        next = next->next;
        free(curr->tile);
        free(curr);
    }
}
