
#include <stdio.h>
#include <stdlib.h>
#include "auxfuncs.h"
#include "PlayerFunctions.h"

int isValid (int **tab, int lin, int col) {
    if (lin >= 0 && lin < 14 && col >= 0 && col < 14) {
        if (tab[lin][col] == '-')
            return 1;
        fprintf(stderr, "A posição escolhida já está ocupada. Faça outra jogada.\n");
        return 0;
    }
    fprintf(stderr, "A posição escolhida não está no tabuleiro. Faça outra jogada.\n");
    return 0;
}

int noWinner (int **tab) {
    return 1;
}

Tile *play (int **tab) {
    const char errmsg[] = "Não foi possível alocar uma estrutura auxiliar\n";
    Tile *ret;
    ret = emalloc(sizeof(Tile), errmsg);
    ret->lin = rand()%14;
    ret->col = rand()%14;
    printf("%d %d\n", ret->lin, ret->col);
    return ret;
}

void printGame (int **tab) {
    int i, j;
    for (i = 13; i >= 0; i--) {
        for (j = 0; j < i; j++)
            fprintf(stderr, " ");
        for (j = 0; j < 14; j++)
            fprintf(stderr, "%c%c", tab[i][j], "\n "[j != 13]);
    }
}

int beginGame (int **tab, int color, int printTab) {
    int turn = 0, col, lin;
    Tile *ret = NULL;
    if (color == 1) {
        ret = play(tab);
        tab[ret->lin][ret->col] = 'b';
        turn++;
    }
    while (noWinner(tab)) {
        do {
            if (scanf("%d %d", &lin, &col) != 2)
                return 0;
            if (turn == 2 && color == 1)
                if (lin == ret->lin && col == ret->col) {
                    color = 2;
                    turn--;
                    free(ret);
                    break;
                }
        } while (!isValid(tab, lin, col));
        turn++;
        tab[lin][col] = (color == 1)? 'p' : 'b';
        ret = play(tab);
        tab[ret->lin][ret->col] = (color == 1)? 'b' : 'p';
        if (printTab)
            printGame(tab);
        free(ret);
    }
    return 1;
}
