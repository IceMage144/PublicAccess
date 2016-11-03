/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __TABELASIMBOLO_VO_H__
#define __TABELASIMBOLO_VO_H__

#include "auxfuncs.h"
#include "vectorfuncs.h"

InsertionResult *OVPush (VST *Table, const char *key);

void OVPrintVal (VST *Table, int topChar);

void OVPrintLexi (VST *Table, int topChar);

#endif