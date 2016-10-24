/*
	Biblioteca feita por João Gabriel Basi
*/

#include <stdlib.h>
#include "vectorfuncs.h"
#include "auxfuncs.h"

/*Cria funções comuns entre as tabelas de símbolo implementadas com vetor
desordenado e ordenado*/

VST *VTableCreate () {
	const char errmsg[] = "A tabela de símbolos não pode ser alocada\n";
	VST *Ret;
	int i;
	Ret = emalloc(sizeof(VST), errmsg);
	Ret->data = emalloc(1024*sizeof(Entry), errmsg);
	for (i = 0; i < 1024; i++){
		Ret->data[i].key = NULL;
		Ret->data[i].value = 0;
	}
	Ret->top = 0;
	Ret->maxPos = 1024;
	return Ret;
}

void VTableDestroy (VST *Table) {
	int i;
	for (i = 0; i < Table->top; i++) {
		free(Table->data[i].key);
	}
	free(Table->data);
	free(Table);
}