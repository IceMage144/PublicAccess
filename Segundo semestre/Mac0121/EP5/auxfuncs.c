/*
    Biblioteca feita por João Gabriel Basi
*/

#include <stdio.h>
#include <stdlib.h>

/*Biblioteca de funções que ajudam o programa a manusear a memória*/

/*Aloca espaço de tamanho "size" na memória, e, se a alocação falhar,
mostra a mensagem "msg" na saída de erros*/
void *emalloc (size_t size, const char *msg) {
    int *Ret;
    Ret = malloc(size);
    if (Ret == NULL) {
        fprintf(stderr, "%s", msg);
        exit(1);
    }
    return Ret;
}
