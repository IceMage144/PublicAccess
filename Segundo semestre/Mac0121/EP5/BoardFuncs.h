/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __BOARDFUNCS_H__
#define __BOARDFUNCS_H__

/*Biblioteca de funções que implemntam o tabuleiro e ajudam a manuseá-lo*/

/*Struct que guarda as informações de uma casa do tabuleiro*/
typedef struct btile_t {
    int lin, col;
    char color;
    struct btile_t **Neigh;
    int *weights;
} BTile;

/*Recebe os números "m" e "n" e retrona um ponteiro para um novo tabuleiro
com "m" linhas e "n" colunas*/
BTile **BoardCreate (int m, int n);

/*-----------------------------Retirar----------------------------------------*/
void printBo (BTile **board, int m, int n);

/*Desaloca um tabuleiro "board" com "m" linhas e "n" colunas*/
void freeBo (BTile **board, int m, int n);

/*-----------------------------Retirar----------------------------------------*/
void printPath (Path *path);

/*Imprime o tabuleiro "board"*/
void printGame (BTile **board);

/*Recebe o tabuleiro "board", uma posição ("lin","col") e um argumento "print"
e retorna 1 se a posição pertence ao tabuleiro e não está ocupada ou 0 caso
contrário. Caso "print" for 1 e a função for retornar 0, imprime uma mensagem
de erro*/
int isValid (BTile **board, int lin, int col, int print);

/*Recebe o tabuleiro "board" e retorna 0 se ningém venceu, 1 se as peças
brancas venceram ou 2 se as peças pretas venceram*/
int getWinner (BTile **board);

/*Recebe o tabuleiro "board" e uma posição ("lin","col") e atualiza os pesos
ao redor dessa posição*/
void updateWeights (BTile **board, int lin, int col);

#endif
