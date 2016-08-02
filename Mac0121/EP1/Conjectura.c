#include <stdio.h>
#include <math.h>

#define lld long long

int res[112345];

lld collatz(lld num){
	if (num%2 == 0){
		return (num/2);
	}
	else{
		return (3*num+1);
	}
}

int main(){
	int inicio, fim, steps, mem;
	lld aux;
	scanf("%d%d", &inicio, &fim);
	for(int i = inicio; i <= fim; i++){
		steps = 0;
		aux = i;
		if (i > 1 && res[i] == 0){
			while(aux != 1){
				aux = collatz(aux);
				steps++;
			}
			res[i] = steps;
			mem = i*2;
			while(mem <= fim){
				res[mem] = steps+aux;
				aux++;
				mem *= 2;
			}
			aux = i;
			while(aux != 1){
				aux = collatz(aux);
				steps--;
				if (aux >= inicio && aux <= fim && res[aux] == 0){
					res[aux] = steps;
				}
			}
		}
	}
	for(int i = inicio; i <= fim; i++){
		printf("%d%c", res[i], " \n"[i == fim]);
	}
}

//numeros iguais consecutivos vem um numero impar de vezes 