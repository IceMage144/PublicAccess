#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define lld long

/*calcula o número de passos da função de Collatz*/ 
int collatz(lld num, int steps){
	if (num == 1)
		return steps;
	else if (num%2 == 0)
		return collatz(num/2, steps+1);
	else
		return collatz(3*num+1, steps+1);
}

int main(){
	lld inicio, fim;
	int i;
	clock_t beg, end;
	if (scanf("%ld%ld", &inicio, &fim) != 2) exit(1);
	beg = clock();
	for (i = 0; i <= fim-inicio; i++){
		/*printf("%d\n", collatz(i+inicio, 0));*/
		collatz(i+inicio, 0);
		if (i == 100000000) printf("10 percent\n");
		else if (i == 200000000) printf("20 percent\n");
		else if (i == 300000000) printf("30 percent\n");
		else if (i == 400000000) printf("40 percent\n");
		else if (i == 500000000) printf("50 percent\n");
		else if (i == 600000000) printf("60 percent\n");
		else if (i == 700000000) printf("70 percent\n");
		else if (i == 800000000) printf("80 percent\n");
		else if (i == 900000000) printf("90 percent\n");
		else if (i == 1000000000) printf("100 percent\n");
	}
	end = clock();
	printf("Time: %fms\n", 1000.0*(float)(end-beg)/CLOCKS_PER_SEC);
	return 0;
}