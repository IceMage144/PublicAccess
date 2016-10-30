/*
	EP4 - MAC0121
	João Gabriel Basi
	N° USP: 9793801
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabelaSimbolo_VO.h"
#include "tabelaSimbolo_VD.h"
#include "tabelaSimbolo_LO.h"
#include "tabelaSimbolo_LD.h"
/*#include "tabelaSimbolo_AB.h"*/
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
/*
	else if (strcmp(argv[2], "AB") == 0)
		executeBST(input, argv[3][0]);
*/
	else {
		show_usage(1);
		exit(1);
	}
	fclose(input);
	return 0;
}