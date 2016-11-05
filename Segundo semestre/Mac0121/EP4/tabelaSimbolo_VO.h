/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __TABELASIMBOLO_VO_H__
#define __TABELASIMBOLO_VO_H__

#include "auxfuncs.h"
#include "vectorfuncs.h"

/*Biblioteca com funções sobre a tabela de símbolos implementada com
vetor ordenado*/

/*Adiciona uma chave "key" à uma tablela de símbolos ordenada "Table", do
tipo vetor, e retorna um InsertionResult, com um ponteiro para o campo
"value" associado à "key" e com a variável new igual à 1 se a chave é nova,
ou 0 caso contrário*/
InsertionResult *OVAdd (VST *Table, const char *key);

/*Função que imprime a tabela de símbolos ordenada "Table", do tipo vetor,
na saída padrão, com seus elementos ordenados por ordem de ocorrência*/
void OVPrintVal (VST *Table, int topChar);

/*Função que imprime a tabela de símbolos ordenada "Table", do tipo vetor,
na saída padrão, com seus elementos ordenados por ordem alfabética*/
void OVPrintLexi (VST *Table, int topChar);

#endif