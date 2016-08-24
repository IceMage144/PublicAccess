#include <stdio.h>

int main(){
	int dig, sum;
	scanf("%d%d", &dig, &sum);
	if (dig > 1 && sum == 0){
		printf("No solution\n");
	}
	else {
		printf("%d", sum);
		dig -= 1;
		while (dig > 0){
			printf("0");
			dig -= 1;
		}
		printf("\n");
	}
	return 0;
}