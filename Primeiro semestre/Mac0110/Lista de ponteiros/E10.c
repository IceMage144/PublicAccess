#include <stdio.h>

int main(){
	int V[100];
	int *pz;
	for (int i=0; i<100; i++){
		V[i] = 2*i;
	}
	pz = V;
	for (int i=0; i<10; i++){
		printf("%d\n", *(pz+i));
	}
	return 0;
}