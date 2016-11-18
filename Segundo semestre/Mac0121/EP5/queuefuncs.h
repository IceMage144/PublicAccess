#ifndef __QUEUEFUNCS_H__
#define __QUEUEFUNCS_H__

#include "auxfuncs.h"

typedef struct queue_t {
    Tile **vector;
    int beg, end;
} Queue;

Queue *QCreate ();

void QAdd (Queue *queue, Tile *tile);

Tile *QRemove (Queue *queue);

void QDestroy (Queue *queue);

void QReset (Queue **queue);

#endif
