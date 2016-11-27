/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __AUXFUNCS_H__
#define __AUXFUNCS_H__

/*Biblioteca de funções que ajudam o programa a manusear a memória e
resumir operações*/

/*Define o tamanho do tabuleiro*/
#define N 14

/*Define infinito como 2^30*/
#define INF 1073741824

/*Struct que armazena uma posição do tabuleiro e sua cor*/
typedef struct pos_t {
    int lin, col;
    char color;
} Pos;

/*Aloca espaço de tamanho "size" na memória, e, se a alocação falhar,
mostra a mensagem "msg" na saída de erros*/
void *emalloc (size_t size, const char *msg);

/*Aloca uma matriz com "m" linhas e "n" colunas e devolve um ponteiro para
ela*/
int **criaMatriz (int m, int n);

/*Desaloca uma matriz "mat" com "m" linhas*/
void freeMatriz (int **mat, int m);

/*-----------------------------Retirar----------------------------------------*/
void imprimeMatriz (int **mat, int m, int n);

/*Aloca uma vetor de tamanho "tam" e devolve um ponteiro para ele*/
int *criaVetor (int tam);

/*-----------------------------Retirar----------------------------------------*/
void imprimeVetor (int *v, int tam);

/*Transforma um char, que representa uma cor, em um inteiro. Se "color" for
'p' ela retorna 0, se for 'b' ela retorna 1*/
int coltoi (char color);

/*Troca o conteúdo de duas posições de memória "num1" e "num2"*/
void troca (int *num1, int *num2);

#endif
