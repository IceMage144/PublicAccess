#ifndef __PLAYERFUNCTIONS_H__
#define __PLAYERFUNCTIONS_H__

#include "auxfuncs.h"

int isValid (int **tab, int lin, int col);

int noWinner (int **tab);

TreeNode *findPath (int **tab, Tile *tile, char color, int uod);

Tile *play (int **tab);

void printGame (int **tab);

int beginGame (int **tab, char color, int printTab);

#endif
