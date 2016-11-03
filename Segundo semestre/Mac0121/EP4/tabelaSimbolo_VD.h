/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __TABELASIMBOLO_VD_H__
#define __TABELASIMBOLO_VD_H__

#include "auxfuncs.h"
#include "vectorfuncs.h"

InsertionResult *UVPush (VST *Table, const char *key);

void UVPrintVal (VST *Table, int topChar);

void UVPrintLexi (VST *Table, int topChar);

#endif