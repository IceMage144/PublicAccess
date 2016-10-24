/*
	Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "auxfuncs.h"

/*Cria as funções sobre uma struct Buffer, que guarda caracteres lidos da
entrada padrão*/

Buffer *BufferCreate (){
	const char errmsg[] = "O Buffer não pode ser criado\n";
	Buffer *Buff;
	Buff = emalloc(sizeof(Buffer), errmsg);
	Buff->data = emalloc(1024 * sizeof(char), errmsg);
	Buff->top = 0;
	Buff->maxPos = 1024;
	return Buff;
}

void BufferDestroy (Buffer *Buff){
	free(Buff->data);
	free(Buff);
}


void BufferReset(Buffer *Buff){
	int i;
	for (i = 0; i < Buff->top; i++){
		Buff->data[i] = 0;
	}
	Buff->top = 0;
}

void BufferPush(Buffer *Buff, char c){
	int i;
	char *Vaux;
	const char errmsg[] = "O Buffer não pode ser extendido\n";
	Buff->data[Buff->top] = c;
	(Buff->top)++;
	if (Buff->top == Buff->maxPos){
		Vaux = emalloc(2 * Buff->maxPos * sizeof(char), errmsg);
		for (i = 0; i < Buff->maxPos; i++)
			Vaux[i] = Buff->data[i];
		free(Buff->data);
		Buff->data = Vaux;
		Buff->maxPos *= 2;
	}
}


int readLine(FILE *input, Buffer *Buff){
	char c = fgetc(input);
	int charCount = 0;
	BufferReset(Buff);
	while (c != EOF && c != '\n'){
		BufferPush(Buff, c);
		charCount++;
		c = fgetc(input);
	}
	if (c == '\n'){
		BufferPush(Buff, c);
		charCount++;
	}
	return charCount;
}