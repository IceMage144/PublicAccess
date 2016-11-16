#ifndef __PLAYERFUNCTIONS_H__
#define __PLAYERFUNCTIONS_H__

typedef struct tile_t {
    int lin, col;
} Tile;

int isValid (int **tab, int lin, int col);

int noWinner (int **tab);

Tile *play (int **tab);

void printGame (int **tab);

int beginGame (int **tab, int color, int printTab);

#endif
