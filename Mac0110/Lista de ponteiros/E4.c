#include <stdio.h>

int main(){
	int m = 10;
	int n = 20;
	int p = 30;
	int *pz;
	pz = &m;
	printf("%d\n%d\n%p\n", m, *pz, pz);
	pz = &n;
	printf("%d\n%p\n", *pz, pz);
	pz = &p;
	printf("%d\n%p\n", *pz, pz);
	return 0;
}