/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__

#include "BoardFuncs.h"

/*Biblioteca de funções que ajudam o programa na criação e no manuseio de
caminhos pelo tabuleiro*/

/*Vetor que indica o peso de cada visinho em função da cor e da direção
em que o tabuleiro é percorrido (mais sobre esse vetor no relatório)*/
static const int macro[2][2][6] = {{{10, 1, 0, 0, 1, 10}, {0, 1, 10, 10, 1, 0}},
                                   {{0, 0, 1, 10, 10, 1}, {10, 10, 1, 0, 0, 1}}};

/*Vetor auxiliar que indica a ordem que os pesos devem ser aplicados no
vetor "macro" (mais sobre esse vetor no relatório)*/
static const int macroAux[2][6] = {{5, 4, 3, 2, 1, 0}, {1, 0, 5, 4, 3, 2}};

/*Nó de lista ligada que guarda uma posição do tabuleiro ("lin","col"), sua cor
"color" e sua posição "pos" na lista ligada*/
typedef struct pathnode_t {
    int lin, col, pos;
    char color;
    struct pathnode_t *next;
} PNode;

/*Struct que guarda um caminho de peças em uma lista ligada apontada por
"head" e o peso "value" desse caminho*/
typedef struct path_t {
    PNode *head;
    int value;
} Path;

/*Desaloca um caminho "path"*/
void PathDestroy (Path *path);

/*Devolve o primeiro nó pertencente ao "path1" que é comum aos caminhos "path1"
e "path2"*/
PNode *Intersec (Path *path1, Path *path2);

/*Recebe o tabuleiro "board" e uma cor "color" e devolve um caminho entre as
laterais do tabuleiro pertencentes a cor fornecida (Obs.: o caminho devolvido
não é o melhor possível, mas é um dos melhores)*/
Path *findPath (BTile **board, char color);

/*Recebe dois caminhos "path1" e "path2" e devolve 1 se eles forem iguais ou
0 caso contrário (Obs.: só compara a linha e a coluna de cada posição, não
compara a cor)*/
int pathcmp (Path *path1, Path *path2);

#endif
