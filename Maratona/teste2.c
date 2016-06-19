#include <stdio.h>
#include <stdlib.h>

void * mallocc(unsigned int nbytes) {
    void *ptr ;
    ptr = malloc (nbytes) ;
    if (ptr==NULL) {
       printf("Socorro! malloc devolveu NULL em mallocc!\n") ;
       exit(EXIT_FAILURE) ;
    }
    return ptr ;
}

unsigned int *CriaIdentidade(unsigned int m) {
    unsigned int p, dim ;
    unsigned int *V ;
    /* ponteiro para armazenar o endereço da primeira posição da memória alocada
    Aloca a memória para o vetor do tamanho de uma matriz m x n */
    V = (unsigned int *) mallocc(m*m*sizeof(int)) ;
    dim = m*m ;
    /* Inicializa a matriz */
    for (p=0; p<dim; p++)
        V[p] = 0 ;
    /* Preenche a diagonal */
    for (p=0; p < m; p++)
        V[p*m+p] = 1;
    return V ;
}

int main(){
	unsigned int M = *CriaIdentidade(3);
	printf("[");
	for (int i = 0; i<3; i+=1){
		printf("[");
		for (int j = 0; j<3; j+=1){
			printf("%u, ", *(&M+j));
		}
		printf("],%c", "\n\0"[i = 3]);
	}
	printf("]\n");
}