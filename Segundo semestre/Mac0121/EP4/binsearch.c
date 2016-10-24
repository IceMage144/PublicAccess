#include <stdio.h>

int buscaBin (int v[], int topo, int chave) {
    int pos = 0;
    while (v[pos] < chave && pos < topo) {
       	pos++;
    }
    return pos;
}

int main () {
	int topo = 0, pos, aux;
	int v[100];
	while (scanf("%d", &aux) != EOF) {
		pos = buscaBin(v, topo, aux);
		if (v[pos] != aux) {
			for (int i = topo; i > pos; i--)
				v[i] = v[i-1];
			v[pos] = aux;
			topo++;
		}
		for (int i = 0; i < topo; i++)
			printf("%d, ", v[i]);
		printf("\n");
	}
	for (int i = 0; i < topo; i++)
		printf("%d, ", v[i]);
	printf("\n");
	return 0;
}
