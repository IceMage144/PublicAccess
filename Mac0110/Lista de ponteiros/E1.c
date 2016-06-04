#include <stdio.h>

int main(){
	int n;
	int *pn;
	pn = &n;
	scanf("%d", &n);
	while (n != -99999){
		printf("%d\n%d\n", n, *pn);
		scanf("%d", &n);
	}
	return 0;
}