#include <stdio.h>
#include <math.h>
#include <time.h>

#define lld long long

int res[11234567];

//calcula o valor da função de Collatz 
int collatz(lld num, int steps, lld inicio){
	lld index;
	int final;
	if (num == 1){
		return steps;
	}
	else if (num%2 == 0){
		index = (num/2)-inicio;
		if (index < 11234567){
			if (res[index] == 0){
				final = collatz(num/2, steps+1, inicio);
				res[index] = final-steps-1;
				return final;
			}
			else {
				return res[index]+steps+1;
			}
		}
		else {
			final = collatz(num/2, steps+1, inicio);
			return final;
		}
	}
	else {
		index = 3*num+1-inicio;
		if (index < 11234567){
			if (res[index] == 0){
				final = collatz(3*num+1, steps+1, inicio);
				res[index] = final-steps-1;
				return final;
			}
			else {
				return res[index]+steps+1;
			}
		}
		else {
			final = collatz(3*num+1, steps+1, inicio);
			return final;
		}
	}
}

int main(){
	int steps, count;
	lld aux, inicio, fim;
	scanf("%lld%lld", &inicio, &fim);
	clock_t beg, end;
	beg = clock();
	for(int i = 0; i <= fim-inicio; i++){
		if (i+inicio > 1 && res[i] == 0){
			res[i] = collatz(i+inicio, 0, inicio);
		}
	}
	for(int i = 0; i <= fim-inicio; i++){
		printf("%d\n", res[i]);
	}
	end = clock();
	printf("Time: %lfms\n", 1000.0*(double)(end-beg)/CLOCKS_PER_SEC);
	return 0;
}