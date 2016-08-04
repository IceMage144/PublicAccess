#include <stdio.h>
#include <math.h>
#include <time.h>

#define lld long long

int res[11234567];

//calcula um passo da função de Collatz 
lld collatz(lld num){
	if (num%2 == 0)
		return (num/2);
	else
		return (3*num+1);
}

int main(){
	int steps, count;
	lld aux, inicio, fim;
	scanf("%lld%lld", &inicio, &fim);
	for (int i = 0; i <= fim-inicio; i++){
		if (i+inicio > 1 && res[i] == 0){
			steps = 0;
			aux = i+inicio;
			count = 1;
			//calcula o valor da função em aux
			while (aux != 1){
				if (aux < fim){
					if (res[aux-inicio] == 0){
						aux = collatz(aux);
						steps++;
					}
					//se o valor da função em aux já tiver sido calculado, esse resultado é
					//somado aos passos já calculados do número inicial i+inicio
					else {
						steps += res[aux-inicio];
						aux = 1;
					}
				}
				else {
					aux = collatz(aux);
					steps++;
				}
			}
			res[i] = steps;
			aux = (i+inicio)*2;
			//preenche todos os valores aux*2^count, aux*2^count <= fim
			while (aux <= fim){
				res[aux-inicio] = steps+count;
				count++;
				aux *= 2;
			}
			aux = i+inicio;
			//preenche os valores dos números achados em cada passo da função de i até 1 ou até um
			//número que não tenha sido calculado ainda
			while (res[aux-inicio] == 0 && aux != 1){
				aux = collatz(aux);
				steps--;
				if (aux >= inicio && aux <= fim)
					res[aux-inicio] = steps;
			}
		}
	}
	for(int i = 0; i <= fim-inicio; i++)
		printf("%d\n", res[i]);
	return 0;
}