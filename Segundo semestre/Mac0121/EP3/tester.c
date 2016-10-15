#include <stdio.h>
#include <stdlib.h>

void triRotacao (int *vect, int tam, int pos1) {
	int aux, pos2;
	pos2 = (pos1+2)%tam;
	aux = vect[pos1];
	vect[pos1] = vect[pos2];
	vect[pos2] = aux;
}

int *criaVetor (int n){
	int *vect;
	vect = malloc(n*sizeof(int));
	if (vect == NULL)
		exit(1);
	return vect;
}

void imprimeVetor (int *vect, int tam) {
	int i;
	printf("[");
	for (i = 0; i < tam-1; i++)
		printf("%d, ", vect[i]);
	printf("%d]\n", vect[i]);
}

int main () {
	int tam, i, aux;
	int *vect;
	if (scanf("%d", &tam) != 1) exit(1);
	vect = criaVetor(tam);
	for (i = 0; i < tam; i++)
		if (scanf("%d", &vect[i]) != 1) exit(1);
	while (scanf("%d", &aux) != EOF){
		triRotacao(vect, tam, aux);
	}
	imprimeVetor(vect, tam);
	free(vect);
	return 0;
}