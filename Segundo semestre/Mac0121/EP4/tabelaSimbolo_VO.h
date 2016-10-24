/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __TABELASIMBOLO_VO_H__
#define __TABELASIMBOLO_VO_H__

#include <stdio.h>
#include "vectorfuncs.h"

void OVPush (VST *Table, const char *key);

void OVPrintFreq (VST *Table);

void OVPrintLexi (VST *Table);

void executeOV (FILE *input, char ordType);

#endif