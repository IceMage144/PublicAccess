/*
EP3 - MAC0121
Nome: João Gabriel Basi
No USP: 9793801
*/

#include <stdio.h>
#include <stdlib.h>

int *criaVetor (int n){
	int *vect;
	vect = malloc(n*sizeof(int));
	if (vect == NULL)
		exit(1);
	return vect;
}

void triReversao (int *vect, int tam, int pos) {
	int aux, pos2;
	pos2 = (pos+2)%n;
	aux = vect[pos];
	vect[pos] = vect[pos2];
	vect[pos2] = vect[pos];
}

int vetorOrdenado (int *vect, int tam) {
	int count = 0;
	while (count != tam-1){
		if (vect[count] > vect[count+1])
			return 0;
	}
	return 1;
}

int main() {
	int tam, i;
	int *vect;
	if (scanf("%d", &tam) != 1)
		exit(1);
	vect = criaVetor(tam);
	for (i = 0; i < tam; i++)
		if (scanf("%d", &vect[i]) != 1){
			free(vect); 
			exit(1);
		}
	
}