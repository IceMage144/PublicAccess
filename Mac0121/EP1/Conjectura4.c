/*
EP1 - MAC0121
Nome: João Gabriel Basi
No USP: 9793801
*/

#include <stdio.h>
#include <stdlib.h>

/*calcula a função de Collatz*/ 
long collatz(long num){
	if (num%2 == 0)
		return (num/2);
	else
		return (3*num+1);
}

int main(){
	long aux;
	int steps, inicio, fim, i, margin;
	int *res;
	if (scanf("%d%d", &inicio, &fim) != 2)
		exit(1);
	res = (int*)calloc((fim-inicio)/16+1, sizeof(int));
	if (res == NULL)
		exit(1);
	margin = (inicio-1)/16+1;
	for (i = inicio; i <= fim; i++){
		if (i != 1){
			steps = 0;
			aux = i;
			if (res[i/16-margin] != 0 && i%16 == 0){
				/*printf("%d: %d\n", i, res[i/16-1]);*/
			}
			else {
				/*calcula o número de passos de i*/
				while (aux != 1){
					/*se o número de passos em aux já tiver sido calculado, esse resultado é
					somado aos passos já calculados de i*/
					if (aux <= fim && aux >= inicio && res[aux/16-margin] != 0 && aux%16 == 0){
						steps += res[aux/16-margin];
						aux = 1;
					}
					else {
						aux = collatz(aux);
						steps++;
					}
				}
				if (i%16 == 0)
					res[i/16-margin] = steps;
				/*printf("%d: %d\n", i, steps);*/
			}
		}
		else
			printf("1: 0\n");
		if (i == 250000000) printf("25 percent\n");
		else if (i == 500000000) printf("50 percent\n");
		else if (i == 750000000) printf("75 percent\n");
		else if (i == 1000000000) printf("100 percent\n");
	}
	free(res);
	return 0;
}