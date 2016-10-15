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

/*------------------------------------------*/
void imprimeVetor (int *vect, int tam) {
	int i;
	printf("[");
	for (i = 0; i < tam-1; i++)
		printf("%d, ", vect[i]);
	printf("%d]\n", vect[i]);
}
/*------------------------------------------*/

void intercala (int *vect, int *ord, int ini, int meio, int fim){
	int pos = 0, aux1 = ini, aux2 = meio+1, acc = 0;
	int *Vaux/*, *Oaux*/;
	Vaux = criaVetor(fim-ini+1);
	/*Oaux = criaVetor(fim-ini+1);*/
	while (aux1 <= meio && aux2 <= fim){
		if (vect[aux1] >= vect[aux2]){
			Vaux[pos] = vect[aux2];
			aux2++;
			pos++;
			acc = aux2;
			while (acc > pos+ini+1){
				printf("%d\n", ord[acc-1]);
				acc--;
			}
		}
		else {
			Vaux[pos] = vect[aux1];
			aux1++;
			pos++;
			acc = aux1;
			while (acc < pos+ini){
				printf("%d\n", ord[acc]);
				acc++;
			}
		}
	}
	/*imprimeVetor(Vaux, fim-ini+1);*/
	while (aux1 <= meio){
		Vaux[pos] = vect[aux1];
		aux1++;
		pos++;
		acc = aux1;
		while (acc != pos+ini){
			printf("%d\n", ord[acc]);
			acc++;
		}
	}
	while (aux2 <= fim){
		Vaux[pos] = vect[aux2];
		aux2++;
		pos++;
		/*printf("NOICE\n");*/
	}
	/*printf("========\n");*/
	/*imprimeVetor(Vaux, fim-ini+1);*/
	for (aux1 = 0; aux1 < pos; aux1++)
		vect[aux1+ini] = Vaux[aux1];
	free(Vaux);
}

void mergeSort (int *vect, int *ord, int ini, int fim){
	int meio;
	if (ini < fim){
		meio = (ini+fim)/2;
		mergeSort(vect, ord, ini, meio);
		mergeSort(vect, ord, meio+1, fim);
		intercala(vect, ord, ini, meio, fim);
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
/*
int triSort (int *vect, int tam) {
	int i, j;
	int *Vaux, *origPos;
	if (tam%2 == 1){
		Vaux = criaVetor(tam);
		origPos = criaVetor(tam);
		for (i = 0, j = 0; j < tam; i = (i+2)%tam, j++){
			Vaux[j] = vect[i];
			origPos[j] = i;
		}
		imprimeVetor(Vaux, tam);
		imprimeVetor(origPos, tam);
		mergeSort(Vaux, origPos, 0, tam);
		imprimeVetor(Vaux, tam);
		free(Vaux);
		free(origPos);
	} 
	else {
		printf("Nao deu....");
	}
	return 1;
}*/

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
	int tam, i, j = 0, aux;
	int *vect;
	if (scanf("%d", &tam) != 1)
		exit(1);
	printf("%d\n", tam);
	vect = criaVetor(tam);
	for (i = 0; i < tam; i++){
		if (scanf("%d", &aux) != 1){
			free(vect);
			exit(1);
		}
		vect[j] = aux;
		printf("%d\n", vect[j]);
		j++;
	}
	/*printf("%c", EOF);*/
	imprimeVetor(vect, tam);
	if (!triSort(vect, tam))
		printf("Nao e possivel\n");
	free(vect);
	return 0;
}