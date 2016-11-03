/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __TABELASIMBOLO_LO_H__
#define __TABELASIMBOLO_LO_H__

#include "auxfuncs.h"
#include "linkedlistfuncs.h"

InsertionResult *OLLPush (LLST *Table, const char *key);

void OLLPrintVal (LLST *Table, int topChar);

void OLLPrintLexi (LLST *Table, int topChar);

#endif