/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdio.h>

/*Cria as funções sobre uma struct Buffer, que guarda caracteres lidos da
entrada padrão*/

typedef struct {
  char *data;
  int maxPos, top;
} Buffer;

Buffer *BufferCreate();


void BufferDestroy(Buffer *Buff);


void BufferReset(Buffer *Buff);


void BufferPush(Buffer *Buff, char c);


int readLine(FILE *input, Buffer *Buff);

#endif
