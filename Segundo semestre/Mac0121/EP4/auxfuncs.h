/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __AUXFUNCS_H__
#define __AUXFUNCS_H__

typedef struct insresll_t {
    int new;
    int *value;
} InsertionResult;

void *emalloc (size_t size, const char *msg);

char *estrdup (const char *str);

#endif