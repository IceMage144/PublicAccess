/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *emalloc (size_t size, const char *msg) {
    int *Ret;
    Ret = malloc(size);
    if (Ret == NULL) {
        fprintf(stderr, "%s", msg);
        exit(1);
    }
    return Ret;
}

char *estrdup (const char *str) {
    char *aux;
    int len;
    const char errmsg[] = "A string auxiliar não pode ser alocada";
    len = strlen(str);
    aux = emalloc(len*sizeof(char), errmsg);
    strcpy(aux, str);
    return aux;
}