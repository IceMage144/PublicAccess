/*
EP1 - MAC0121
Nome: João Gabriel Basi
No USP: 9793801
*/

#include <stdio.h>
#include <stdlib.h>

#define sint unsigned short int

/*calcula a função de Collatz em num*/ 
long collatz(long num){
	if (num%2 == 0)
		return (num/2);
	else
		return (3*num+1);
}

/*foi guardado no vetor mem uma perte dos números que formam uma bifurcação na árvore construida pela
função de collatz. Foi determinado no relatório que tais números estão na forma (k-1)/3, para k par.
Esses números satisfazem as equações k=1(mod 3), pois k-1 tem que ser divisível por 3, e k=0(mod 2),
pois k é par; juntando as equações temos que k=4(mod 6), mas guardar todos eles ocupa muito espaço, então
selecionei apenas um quarto deles, que são os do tipo k=10(mod 24), sem nenhum motivo em especial*/

int main(){
	long aux;
	int inicio, fim, i, margin;
	sint steps;
	sint *mem;
	if (scanf("%d%d", &inicio, &fim) != 2)
		exit(1);
	mem = (sint*)calloc((fim-inicio)/24+1, sizeof(int));
	if (mem == NULL)
		exit(1);
	/*margin determina quantos números que são bifurcação da forma k=10(mod 24) estão abaixo do inicio*/
	margin = (inicio+13)/24+1;
	for (i = inicio; i <= fim; i++){
		steps = 0;
		aux = i;
		while (aux != 1){
			/*se aux estiver no vetor e seu número de passos já tiver sido calculado, esse resultado é
			somado aos passos já calculados de i*/
			if (aux <= fim && aux >= inicio && mem[(aux+14)/24-margin] != 0 && aux%24 == 10){
				steps += mem[(aux+14)/24-margin];
				aux = 1;
			}
			/*se não, calcula o próximo número e aumenta steps em 1*/
			else {
				aux = collatz(aux);
				steps++;
			}
		}
		/*se i for uma bifurcação que faz parte do vetor, seu valor de passos é guardado no vetor*/
		if (i%24 == 10)
			mem[(i+14)/24-margin] = steps;
		printf("%hu\n", steps);
	}
	free(mem);
	return 0;
}