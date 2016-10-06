/*
EP3 - MAC0121
Nome: João Gabriel Basi
No USP: 9793801
*/

#include <stdio.h>
#include <stdlib.h>

#define sqr(arg) arg*arg

int *criaVetor (int n){
	int *vect;
	vect = malloc(n*sizeof(int));
	if (vect == NULL)
		exit(1);
	return vect;
}

/*------------------------------------------*/
void imprimeVetor (int *vect, int tam) {
	int i;
	printf("[");
	for (i = 0; i < tam-1; i++)
		printf("%d, ", vect[i]);
	printf("%d]\n", vect[i]);
}
/*------------------------------------------*/

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
	for (aux1 = 0; aux1 < pos; aux1++)
		vect[aux1+1] = Vaux[aux1];
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

/*
int buscaBin (int *vect, int tam, int num) {
	int ini = 0, fim = tam, meio;
	meio = (fim+ini)/2;
	while (ini <= fim) {
		if (num == vect[meio])
			return meio;
		if (num < vect[meio]){
			fim = meio-1;
			meio = (fim+ini)/2;
		}
		else {
			ini = meio+1;
			meio = (fim+ini)/2;
		}
	}
	if (meio < tam && vect[meio] < num)
		return meio+1;
	return meio;
}

void triRotacao (int *vect, int tam, int pos1) {
	int aux, pos2;
	pos2 = (pos1+2)%tam;
	aux = vect[pos1];
	vect[pos1] = vect[pos2];
	vect[pos2] = aux;
}

void troca (int *num1, int *num2) {
	*num1 ^= *num2;
	*num2 ^= *num1;
	*num1 ^= *num2;
}
*/
int vetorOrdenado (int *vect, int tam) {
	int count = 0;
	while (count != tam-1){
		if (vect[count] > vect[count+1])
			return 0;
		count++;
	}
	return 1;
}

int triSort (int *vect, int *ord, int tam) {
	int i, paux, aux1, aux2;
	int *parit;
	parit = criaVetor(tam);
	/*par = criaVetor(tam/2);
	impar = criaVetor(tam/2 + ((tam%2 == 1)? 1 : 0));*/
	for (i = 0; i < tam; i++){
		paux = buscaBin(ord, tam, vect[i]);
		parit[i] = paux%2;
	}
	imprimeVetor(parit, tam);
	for (i = tam-1; i >= 0; i--){
		if (i%2 != parit[i]){
			aux1 = i;
			aux2 = (aux1+2)%tam;
			printf("%d\n", vect[i]);
			while (parit[aux1] != parit[aux2]){
				triRotacao(vect, tam, aux1);
				triRotacao(parit, tam, aux1);
				aux1 = aux2;
				aux2 = (aux2+2)%tam;
				imprimeVetor(vect, tam);
				imprimeVetor(parit, tam);
			}
		}
	}
	imprimeVetor(vect, tam);
	imprimeVetor(parit, tam);
	free(parit);
	return 1;
}

int main() {
	int tam, i, j, aux, paux;
	int *vect, *ord;
	if (scanf("%d", &tam) != 1)
		exit(1);
	vect = criaVetor(tam);
	ord = criaVetor(tam);
	/*par = criaVetor(tam);*/
	for (i = 0; i < tam; i++){
		if (scanf("%d", &aux) != 1){
			free(vect);
			exit(1);
		}
		vect[i] = aux;
		paux = buscaBin(ord, i, aux);
		for (j = i-1; j >= paux; j--)
			ord[j+1] = ord[j];
		ord[paux] = aux;
	}
	imprimeVetor(ord, tam);
	imprimeVetor(vect, tam);
	if (!triSort(vect, ord, tam))
		printf("Nao e possivel\n");
	free(vect);
	return 0;
}