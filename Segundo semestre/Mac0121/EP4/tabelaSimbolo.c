/*
    EP4 - MAC0121
    João Gabriel Basi
    N° USP: 9793801
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "vectorfuncs.h"
#include "linkedlistfuncs.h"
#include "buffer.h"
#include "tabelaSimbolo_VO.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_LO.h"
#include "tabelaSimbolo_LD.h"
#include "tabelaSimbolo_AB.h"
#include "auxfuncs.h"

static void show_usage (int num){
    if (num == 0)
        fprintf(stderr, "uso: ep4 <arquivo> <tipo da tabela> <ordem>\n");
    else if (num == 1) {
        fprintf(stderr, "Os tipos de tabela podem ser:\n");
        fprintf(stderr, "   VO: Vetor ordenado\n");
        fprintf(stderr, "   VD: Vetor desordenado\n");
        fprintf(stderr, "   LO: Lista ligada ordenada\n");
        fprintf(stderr, "   LD: Lista ligada desordenada\n");
        fprintf(stderr, "   AB: Árvore de busca binária\n");
    }
    else {
        fprintf(stderr, "A ordenação da saída pode ser:\n");
        fprintf(stderr, "   O: Ordem de ocorrência\n");
        fprintf(stderr, "   A: Ordem alfabética\n");
    }
}

void executeOV (FILE *input, char ordType) {
    int beg = 0, len = 0, redChars, i, topChar = 0;
    const char errmsg[] = "A string auxiliar não pode ser alocada\n";
    char *strAux;
    VST *Table;
    Buffer *Buff;
    Table = VTableCreate();
    Buff = BufferCreate();
    redChars = readLine(input, Buff);
    while (redChars) {
        while (beg < Buff->top) {
            while (beg < Buff->top && !isalpha(Buff->data[beg]))
                beg++;
            while (beg+len < Buff->top && isalnum(Buff->data[beg+len]))
                len++;
            if (!len)
                break;
            if (len > topChar)
                topChar = len;
            strAux = emalloc((len+1)*sizeof(char), errmsg);
            strAux[len] = 0;
            for (i = 0; i < len; i++)
                strAux[i] = tolower(Buff->data[beg+i]);
            OVPush(Table, strAux);
            beg += len;
            len = 0;
            free(strAux);
        }
        redChars = readLine(input, Buff);
        beg = 0;
    }
    if (ordType == 'O')
        OVPrintVal(Table, topChar);
    else
        OVPrintLexi(Table, topChar);
    BufferDestroy(Buff);
    VTableDestroy(Table);
}

void executeUV (FILE *input, char ordType) {
    int beg = 0, len = 0, redChars, i, topChar = 0;
    const char errmsg[] = "A string auxiliar não pode ser alocada\n";
    char *strAux;
    VST *Table;
    Buffer *Buff;
    Table = VTableCreate();
    Buff = BufferCreate();
    redChars = readLine(input, Buff);
    while (redChars) {
        while (beg < Buff->top) {
            while (beg < Buff->top && !isalpha(Buff->data[beg]))
                beg++;
            while (beg+len < Buff->top && isalnum(Buff->data[beg+len]))
                len++;
            if (!len)
                break;
            if (len > topChar)
                topChar = len;
            strAux = emalloc((len+1)*sizeof(char), errmsg);
            strAux[len] = 0;
            for (i = 0; i < len; i++)
                strAux[i] = tolower(Buff->data[beg+i]);
            UVPush(Table, strAux);
            beg += len;
            len = 0;
            free(strAux);
        }
        redChars = readLine(input, Buff);
        beg = 0;
    }
    if (ordType == 'O')
        UVPrintVal(Table, topChar);
    else
        UVPrintLexi(Table, topChar);
    BufferDestroy(Buff);
    VTableDestroy(Table);
}

void executeOLL (FILE *input, char ordType) {
    int beg = 0, len = 0, redChars, i, topChar = 0;
    const char errmsg[] = "A string auxiliar não pode ser alocada\n";
    char *strAux;
    LLST *Table;
    Buffer *Buff;
    Table = LLTableCreate();
    Buff = BufferCreate();
    redChars = readLine(input, Buff);
    while (redChars) {
        while (beg < Buff->top) {
            while (beg < Buff->top && !isalpha(Buff->data[beg]))
                beg++;
            while (beg+len < Buff->top && isalnum(Buff->data[beg+len]))
                len++;
            if (!len)
                break;
            if (len > topChar)
                topChar = len;
            strAux = emalloc((len+1)*sizeof(char), errmsg);
            strAux[len] = 0;
            for (i = 0; i < len; i++)
                strAux[i] = tolower(Buff->data[beg+i]);
            OLLPush(Table, strAux);
            beg += len;
            len = 0;
            free(strAux);
        }
        redChars = readLine(input, Buff);
        beg = 0;
    }
    if (ordType == 'O')
        OLLPrintVal(Table, topChar);
    else
        OLLPrintLexi(Table, topChar);
    BufferDestroy(Buff);
    LLTableDestroy(Table);
}

void executeULL (FILE *input, char ordType) {
    int beg = 0, len = 0, redChars, i, topChar = 0;
    const char errmsg[] = "A string auxiliar não pode ser alocada\n";
    char *strAux;
    LLST *Table;
    Buffer *Buff;
    Table = LLTableCreate();
    Buff = BufferCreate();
    redChars = readLine(input, Buff);
    while (redChars) {
        while (beg < Buff->top) {
            while (beg < Buff->top && !isalpha(Buff->data[beg]))
                beg++;
            while (beg+len < Buff->top && isalnum(Buff->data[beg+len]))
                len++;
            if (!len)
                break;
            if (len > topChar)
                topChar = len;
            strAux = emalloc((len+1)*sizeof(char), errmsg);
            strAux[len] = 0;
            for (i = 0; i < len; i++)
                strAux[i] = tolower(Buff->data[beg+i]);
            ULLPush(Table, strAux);
            beg += len;
            len = 0;
            free(strAux);
        }
        redChars = readLine(input, Buff);
        beg = 0;
    }
    if (ordType == 'O')
        ULLPrintVal(Table, topChar);
    else
        ULLPrintLexi(Table, topChar);
    BufferDestroy(Buff);
    LLTableDestroy(Table);
}

void executeBST (FILE *input, char ordType) {
    int beg = 0, len = 0, redChars, i, topChar = 0;
    const char errmsg[] = "A string auxiliar não pode ser alocada\n";
    char *strAux;
    BTST *Table;
    Buffer *Buff;
    Table = BSTTableCreate();
    Buff = BufferCreate();
    redChars = readLine(input, Buff);
    while (redChars) {
        while (beg < Buff->top) {
            while (beg < Buff->top && !isalpha(Buff->data[beg]))
                beg++;
            while (beg+len < Buff->top && isalnum(Buff->data[beg+len]))
                len++;
            if (!len)
                break;
            if (len > topChar)
                topChar = len;
            strAux = emalloc((len+1)*sizeof(char), errmsg);
            strAux[len] = 0;
            for (i = 0; i < len; i++)
                strAux[i] = tolower(Buff->data[beg+i]);
            BSTPush(Table, strAux);
            beg += len;
            len = 0;
            free(strAux);
        }
        redChars = readLine(input, Buff);
        beg = 0;
    }
    if (ordType == 'O')
        BSTPrintVal(Table, topChar);
    else
        BSTPrintLexi(Table->root, topChar);
    BufferDestroy(Buff);
    BSTTableDestroy(Table);
}


int main (int argc, char **argv) {
    FILE *input;
    if (argc != 4) {
        show_usage(0);
        exit(1);
    }
    if (argv[3][0] != 'A' && argv[3][0] != 'O') {
        show_usage(2);
        exit(1);
    }
    input = fopen(argv[1], "r");
    if (strcmp(argv[2], "VO") == 0)
        executeOV(input, argv[3][0]);

    else if (strcmp(argv[2], "VD") == 0)
        executeUV(input, argv[3][0]);

    else if (strcmp(argv[2], "LO") == 0)
        executeOLL(input, argv[3][0]);

    else if (strcmp(argv[2], "LD") == 0)
        executeULL(input, argv[3][0]);

    else if (strcmp(argv[2], "AB") == 0)
        executeBST(input, argv[3][0]);

    else {
        show_usage(1);
        exit(1);
    }
    fclose(input);
    return 0;
}