#include "mybib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>


int *criaVetor (int tam) {
    int *v;
    v = malloc(tam*sizeof(int));
    if (!v)
        exit(1);
    return v;
}

void escanf (const char *msg, int *arg, int numfree, ...) {
    va_list arglist;
    int i;
    int *parg;
    va_start(arglist, numfree);
    if (!scanf(msg, arg)){
        for (i = 0; i < numfree; i++){
            parg = va_arg(arglist, int*);
            free(parg);
        }
    }
    va_end(arglist);
}