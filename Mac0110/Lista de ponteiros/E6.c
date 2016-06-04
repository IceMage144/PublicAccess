#include <stdio.h>

void troca(int *pa, int *pb){
	int tmp;
	if (*pa > *pb){
		printf("%d\n", *pa);
	}
	else {
		printf("%d\n", *pb);
	}
	tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}

int main(){
	int m;
	scanf("%d", &m);
	int n;
	scanf("%d", &n);
	int *pm, *pn;
	pm = &m;
	pn = &n;
	troca(&m, &n);
	troca(pm, pn);
	return 0;
}