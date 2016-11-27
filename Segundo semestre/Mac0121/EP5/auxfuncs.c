/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include "auxfuncs.h"

/*Biblioteca de funções que ajudam o programa a manusear a memória e
resumir operações*/

/*Aloca espaço de tamanho "size" na memória, e, se a alocação falhar,
mostra a mensagem "msg" na saída de erros*/
void *emalloc (size_t size, const char *msg) {
    int *Ret;
    Ret = malloc(size);
    if (Ret == NULL) {
        fprintf(stderr, "%s", msg);
        exit(1);
    }
    return Ret;
}

/*Aloca uma matriz com "m" linhas e "n" colunas e devolve um ponteiro para
ela*/
int **criaMatriz (int m, int n) {
    const char errmsg[] = "A matriz não pode ser alocada\n";
    int **mat;
    int i;
    mat = emalloc(m*sizeof(int*), errmsg);
    for (i = 0; i < m; i++)
        mat[i] = emalloc(n*sizeof(int), errmsg);
    return mat;
}

/*Desaloca uma matriz "mat" com "m" linhas*/
void freeMatriz (int **mat, int m) {
    int i;
    for (i = 0; i < m; i++)
        free(mat[i]);
    free(mat);
}

/*-----------------------------Retirar----------------------------------------*/
void imprimeMatriz (int **mat, int m, int n) {
    int i, j;
    printf("[");
    for (i = 0; i < m; i++) {
        printf("[");
        for (j = 0; j < n-1; j++)
            printf("%d, ", mat[i][j]);
        printf("%d]%c", mat[i][j], "\n]"[i == m-1]);
    }
    printf("\n");
}

/*Aloca uma vetor de tamanho "tam" e devolve um ponteiro para ele*/
int *criaVetor (int tam) {
    const char errmsg[] = "O vetor não pode ser alocado\n";
    int *v;
    v = emalloc(tam*sizeof(int), errmsg);
    return v;
}

/*-----------------------------Retirar----------------------------------------*/
void imprimeVetor (int *v, int tam) {
    int i;
    printf("[");
    for (i = 0; i < tam-1; i++)
        printf("%d, ", v[i]);
    printf("%d]\n", v[i]);
}

/*Transforma um char, que representa uma cor, em um inteiro. Se "color" for
'p' ela retorna 0, se for 'b' ela retorna 1*/
int coltoi (char color) {
    if (color == 'b')
        return 1;
    if (color == 'p')
        return 0;
    return -1;
}

/*Troca o conteúdo de duas posições de memória "num1" e "num2"*/
void troca (int *num1, int *num2) {
	*num1 ^= *num2;
	*num2 ^= *num1;
	*num1 ^= *num2;
}
