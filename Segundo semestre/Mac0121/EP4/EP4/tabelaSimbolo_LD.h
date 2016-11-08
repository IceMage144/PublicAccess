/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __TABELASIMBOLO_LD_H__
#define __TABELASIMBOLO_LD_H__

#include "linkedlistfuncs.h"
#include "auxfuncs.h"

/*Biblioteca com funções sobre a tabela de símbolos implementada com
lista ligada desordenada*/

/*Adiciona uma chave "key" à uma tablela de símbolos desordenada "Table",
do tipo lista ligada, e retorna um InsertionResult, com um ponteiro para o
campo "value" associado à "key" e com a variável new igual à 1 se a chave é
nova, ou 0 caso contrário*/
InsertionResult *ULLAdd (LLST *Table, const char *key);

/*Função que imprime a tabela de símbolos desordenada "Table", do tipo lista
ligada, na saída padrão, com seus elementos ordenados por ordem de ocorrência*/
void ULLPrintVal (LLST *Table, int topChar);

/*Função que imprime a tabela de símbolos desordenada "Table", do tipo lista
ligada, na saída padrão, com seus elementos ordenados por ordem alfabética*/
void ULLPrintLexi (LLST *Table, int topChar);

#endif
 