/*
    EP5 - MAC121
    Nome: João Gabriel Basi
    N° USP: 9793801
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "BoardFuncs.h"
#include "PathFinding.h"
#include "auxfuncs.h"

/*O programa implementa o jogo de tabuleiro Hex e uma IA capaz de jogá-lo*/

/*Recebe um número "num" e mostra uma mensagem de erro correspondente à ele
na saída padrão de erro*/
void show_usage (int num) {
    if (num == 0) {
        fprintf(stderr, "Uso: ep5 <cor das peças do programa> <imprime tabuleiro>\n");
    }
    if (num == 1) {
        fprintf(stderr, "Cores válidas são:\n");
        fprintf(stderr, "    - p: preto\n");
        fprintf(stderr, "    - b: branco\n");
    }
    if (num == 2) {
        fprintf(stderr, "O argumento <imprime tabuleiro> é opcional:\n");
        fprintf(stderr, "    - Se for fornecida a letra d, o programa imprime o tabuleiro a cada jogada\n");
        fprintf(stderr, "    - Se não houver argumento, o programa não imprime\n");
    }
}

/*dir = 0 -> down/left
dir = 1 -> up/right*/

/*Recebe o tabuleiro "board", o caminho achado na jogada anterior "prevpath",
uma cor "color", o turno "turn" e a última jogada do oponente ("lin","col") e
retorna uma posição vaga do tabuleiro como jogada*/
Pos *play (BTile **board, Path *prevpath, char color, int turn, int Llin, int Lcol) {
    const char errmsg[] = "Não foi possível alocar uma estrutura auxiliar\n";
    PNode *ptr;
    Pos *ret;
    Path *pathB, *pathP;
    if (turn != 0) {
        pathB = findPath(board, 'b');
        /*MEMO*/printPath(pathB);/*MEMO*/
        pathP = findPath(board, 'p');
        /*MEMO*/printPath(pathP);/*MEMO*/
        if (pathB == NULL || pathP == NULL) {
            ret = emalloc(sizeof(Pos), errmsg);
            do {
                ret->lin = rand()%N;
                ret->col = rand()%N;
            } while (!isValid(board, ret->lin, ret->col, 0));
            return ret;
        }
        if (color == 'b') {
            if (prevpath != NULL && pathcmp(pathB, prevpath)) {
                /*Attack*/
                ptr = Interssec(pathB, pathP);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
            }
            else if (prevpath != NULL) {
                /*Deffend*/
                ptr = Interssec(pathP, pathB);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
                /*MEMO*//*printf("Destroying prevpath\n");*//*MEMO*/
                PathDestroy(prevpath);
                prevpath = pathB;
            }
            else {
                /*Forced deffense*/
                ptr = Interssec(pathP, pathB);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
                prevpath = pathB;
            }
            if (ptr->next != NULL)
                if (ptr->next->color == '-')
                    ptr = ptr->next;
            ret = emalloc(sizeof(Pos), errmsg);
            /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
            ret->lin = ptr->lin;
            ret->col = ptr->col;
            /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
        }
        else {
            if (prevpath != NULL && pathcmp(pathP, prevpath)) {
                /*Attack*/
                ptr = Interssec(pathP, pathB);
            }
            else if (prevpath != NULL) {
                /*Deffend*/
                ptr = Interssec(pathB, pathP);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
                /*MEMO*//*printf("Destroying prevpath\n");*//*MEMO*/
                PathDestroy(prevpath);
                prevpath = pathP;
            }
            else {
                /*Forced deffense*/
                ptr = Interssec(pathB, pathP);
                /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
                prevpath = pathP;
            }
            if (ptr->next != NULL && ptr->next->color == '-')
                ptr = ptr->next;
            ret = emalloc(sizeof(Pos), errmsg);
            ret->lin = ptr->lin;
            ret->col = ptr->col;
            /*MEMO*//*printf("%d %d\n", ptr->lin, ptr->col);*//*MEMO*/
        }
        /*MEMO*//*printf("Destroying pathP\n");*//*MEMO*/
        PathDestroy(pathP);
        /*MEMO*//*printf("Destroying pathB\n");*//*MEMO*/
        PathDestroy(pathB);
    }
    else {
        ret = emalloc(sizeof(Pos), errmsg);
        if (color == 'b') {
            ret->lin = 7;
            ret->col = 5;
        }
        else {
            if (Llin == Lcol) {
                ret->lin = Llin;
                ret->col = Lcol;
            }
            else {
                ret->lin = rand()%N;
                ret->col = ret->lin;
            }
        }
    }
    printf("%d %d\n", ret->lin, ret->col);
    return ret;
}

/*Recebe o tabuleiro "board", uma cor "color" e o argumento "printBoard" e
começa o loop do jogo. Imprime o tabuleiro na saída de erro a cada jogada se
printBoard for 1. Retorna 0 se houve algum erro ou 1 se alguém venceu*/
int beginGameLoop (BTile **board, char color, int printBoard) {
    int turn = 0, col, lin, win = 0;
    Pos *ret, *retAux;
    Path *prevpath;
    clock_t t;
    ret = NULL;
    prevpath = NULL;
    srand(time(NULL));
    if (color == 'b') {
        retAux = play(board, prevpath, color, turn, 0, 0);
        board[retAux->lin][retAux->col].color = 'b';
        turn++;
        updateWeights(board, retAux->lin, retAux->col);
        if (printBoard) {
            printGame(board);
            /*printBo(board, N, N);*/
        }
    }
    while (!win) {
        if (color == 'p' && turn == 0 && printBoard)
            printGame(board);
        do {
            if (scanf("%d %d", &lin, &col) != 2)
                return 0;
            /*Remover-------------*/
            if (lin == EOF) {
                PathDestroy(prevpath);
                return 0;
            }
            /*--------------------*/
            if (turn == 1 && color == 'b') {
                if (lin == retAux->lin && col == retAux->col) {
                    color = 'p';
                    turn--;
                    free(retAux);
                    break;
                }
                free(retAux);
            }
        } while (!isValid(board, lin, col, 1));
        t = clock();
        board[lin][col].color = (color == 'b')? 'p' : 'b';
        updateWeights(board, lin, col);
        win = getWinner(board);
        if (!win) {
            ret = play(board, prevpath, color, turn, lin, col);
            if (ret->lin == lin && ret->col == col)
                color = (color == 'b')? 'p' : 'b';
            else {
                turn++;
                board[ret->lin][ret->col].color = color;
                updateWeights(board, ret->lin, ret->col);
                if (printBoard)
                    printGame(board);
            }
            free(ret);
        }
        else
            break;
        win = getWinner(board);
        t = clock() - t;
        printf("Runtime = %fs\n", ((float)t)/CLOCKS_PER_SEC);
    }
    if (printBoard)
        printGame(board);
    if (win == 1)
        fprintf(stderr, "b ganhou\n");
    else if (win == 2)
        fprintf(stderr, "p ganhou\n");
    /*MEMO*//*printf("Destroying prevpath\n");*//*MEMO*/
    if (prevpath != NULL)
        PathDestroy(prevpath);
    return 1;
}

int main(int argc, char *argv[]) {
    BTile **board;
    int printBoard = 0;
    board = BoardCreate(N, N);
    if (argc < 2) {
        show_usage(0);
        return 0;
    }
    if (argc == 3 && strcmp(argv[2], "d")) {
        show_usage(0);
        return 0;
    }
    else if (argc == 3)
        printBoard = 1;
    if (strcmp(argv[1], "b") && strcmp(argv[1], "p")) {
        show_usage(1);
        return 0;
    }
    /*printBo(board, N, N);*/
    beginGameLoop(board, argv[1][0], printBoard);
    freeBo(board, N, N);
    return 0;
}
