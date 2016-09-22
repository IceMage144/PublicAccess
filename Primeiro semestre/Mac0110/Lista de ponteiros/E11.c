#include <stdio.h>

void imprimeVetor(int *p, int n){
	for (int i=0; i<10; i++){
		printf("%d\n", *(p+i));
	}
}

int main(){
	int V[100];
	int *pz;
	for (int i=0; i<100; i++){
		V[i] = 2*i;
	}
	pz = V;
	imprimeVetor(V, 100);
	return 0;
}