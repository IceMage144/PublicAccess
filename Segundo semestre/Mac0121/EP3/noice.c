#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *criaVetor (int n){
	int *vect, i;
	vect = malloc(n*sizeof(int));
	if (vect == NULL)
		exit(1);
	for (i = 0; i < n; i++)
		vect[i] = 0;
	return vect;
}

void imprimeVetor (int *vect, int tam) {
	int i;
	printf("[");
	for (i = 0; i < tam-1; i++)
		printf("%d, ", vect[i]);
	printf("%d]\n", vect[i]);
}

void intercala (int *vect, int ini, int meio, int fim){
	int pos = 0, aux1 = ini, aux2 = meio+1;
	int *Vaux;
	Vaux = criaVetor(fim-ini+1);
	while (aux1 <= meio && aux2 <= fim){
		if (vect[aux1] >= vect[aux2]){
			Vaux[pos] = vect[aux2];
			aux2++;
		}
		else {
			Vaux[pos] = vect[aux1];
			aux1++;
		}
		pos++;
	}
	imprimeVetor(Vaux, fim-ini+1);
	while (aux1 <= meio){
		Vaux[pos] = vect[aux1];
		aux1++;
		pos++;
	}
	while (aux2 <= fim){
		Vaux[pos] = vect[aux2];
		aux2++;
		pos++;
	}
	imprimeVetor(Vaux, fim-ini+1);
	for (aux1 = 0; aux1 < pos; aux1++)
		vect[aux1+ini] = Vaux[aux1];
	free(Vaux);
}

void mergeSort (int *vect, int ini, int fim){
	int meio;
	if (ini < fim){
		meio = (ini+fim)/2;
		mergeSort(vect, ini, meio);
		mergeSort(vect, meio+1, fim);
		intercala(vect, ini, meio, fim);
	}
}

int main () {
	int *vect, aux, topo = 0;
	vect = malloc(50*sizeof(int));
	while (scanf("%d", &aux) != EOF){
		vect[topo] = aux;
		topo++;
	}
	mergeSort(vect, 0, topo-1);
	imprimeVetor(vect, topo);
	return 0;
}