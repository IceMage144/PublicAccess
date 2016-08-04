#include <stdio.h>
#include <math.h>
#include <time.h>

#define lld long long

//calcula o númeero de passos da função de Collatz 
int collatz(lld num, int steps){
	lld next, final;
	if (num == 1){
		return steps;
	}
	else if (num%2 == 0){
		return collatz(num/2, steps+1);
	}
	else {
		return collatz(3*num+1, steps+1);
	}
}

int main(){
	lld inicio, fim;
	scanf("%lld%lld", &inicio, &fim);
	clock_t beg, end;
	beg = clock();
	for(int i = 0; i <= fim-inicio; i++){
		printf("%d\n", collatz(i+inicio, 0));
	}
	end = clock();
	printf("Time: %lfms\n", 1000.0*(double)(end-beg)/CLOCKS_PER_SEC);
	return 0;
}