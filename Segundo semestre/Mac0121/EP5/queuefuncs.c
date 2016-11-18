
#include <stdlib.h>
#include "queuefuncs.h"
#include "auxfuncs.h"

Queue *QCreate () {
    const char errmsg[] = "A fila não pode ser alocada\n";
    Queue *ret;
    ret = emalloc(sizeof(Queue), errmsg);
    ret->vector = emalloc(200*sizeof(*Tile), errmsg);
    ret->beg = 0;
    ret->end = 0;
    return ret;
}

void QAdd (Queue *queue, const Tile *tile) {
    const char errmsg[] = "Uma posição não pode ser adicionada na fila\n";
    Tile *newTile;
    newTile = emalloc(sizeof(Tile), errmsg);
    newTile->lin = tile->lin;
    newTile->col = tile->col;
    queue->vector[queue->end] = newTile;
    (queue->end)++;
}

Tile *QRemove (Queue *queue) {
    const char errmsg[] = "Uma posição não pode ser retirada da fila\n";
    Tile *newTile;
    newTile = emalloc(sizeof(Tile), errmsg);
    newTile->lin = queue->vector[queue->beg]->lin;
    newTile->col = queue->vector[queue->beg]->col;
    (queue->beg)++;
}

void QDestroy (Queue *queue) {
    int i;
    for (i = 0; i < queue->top; i++)
        free(queue->vector[i]);
    free(queue);
}

void QReset (Queue **queue) {
    QDestroy(*queue);
    *queue = QCreate();
}
