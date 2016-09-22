#include <stdio.h>

int main(){
	int V[100];
	int *pz, *pw;
	for (int i=0; i<100; i++){
		V[i] = 2*i;
	}
	pz = V+1;
	pw = &V[1];
	printf("%d\n%d\n%d\n%p\n%p\n", V[1], *pz, *pw, pz, pw);
	return 0;
}