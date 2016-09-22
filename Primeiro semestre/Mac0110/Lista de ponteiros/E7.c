#include <stdio.h>

int main(){
	int V[100];
	int *pz;
	for (int i=0; i<100; i++){
		V[i] = 2*i;
	}
	pz = V;
	printf("%d\n%d\n", *pz, V[0]);
	return 0;
}