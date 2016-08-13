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
	long steps, aux, inicio, fim, i;
	int *res;
	if (scanf("%ld%ld", &inicio, &fim) != 2)
		exit(1);
	res = (int*)malloc((fim-inicio+1) * sizeof(int));
	if (res == NULL)
		exit(1);
	for (i = inicio; i <= fim; i++){
		if (i > 1 && res[i-inicio] == 0){
			steps = 0;
			aux = i;
			/*calcula o número de passos de i*/
			while (aux != 1){
				/*se o número de passos em aux já tiver sido calculado, esse resultado é
				somado aos passos já calculados de i*/
				if (aux <= fim && aux >= inicio && res[aux-inicio] != 0){
					steps += res[aux-inicio];
					aux = 1;
				}
				else {
					aux = collatz(aux);
					steps++;
				}
			}
			res[i-inicio] = steps;
			aux = i;
			/*preenche os passos dos números achados em cada iteração da função de
			i até 1 ou até um número que não tenha sido calculado ainda*/
			while (res[aux-inicio] == 0 && aux != 1){
				aux = collatz(aux);
				steps--;
				if (aux >= inicio && aux <= fim)
					res[aux-inicio] = steps;
			}
		}
	}
	for (i = 0; i <= fim-inicio; i++)
		printf("%ld: %d\n", i+1, res[i]);
	free(res);
	return 0;
}