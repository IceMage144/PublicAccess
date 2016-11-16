/*
    Biblioteca feita por João Gabriel Basi
*/

#ifndef __AUXFUNCS_H__
#define __AUXFUNCS_H__

/*Biblioteca de funções que ajudam o programa a manusear a memória e
resumir operações*/

/*Aloca espaço de tamanho "size" na memória, e, se a alocação falhar,
mostra a mensagem "msg" na saída de erros*/
void *emalloc (size_t size, const char *msg);

#endif
