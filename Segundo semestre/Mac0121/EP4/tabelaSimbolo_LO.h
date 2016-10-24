/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __TABELASIMBOLO_LO_H__
#define __TABELASIMBOLO_LO_H__

#include <stdio.h>
#include "linkedlistfuncs.h"

void OLLPush (LLST *Table, const char *key);

void OLLPrintFreq (LLST *Table);

void OLLPrintLexi (LLST *Table);

void executeOLL (FILE *input, char ordType);

#endif