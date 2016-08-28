#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int topo;
	int **v;
} pilha;

pilha *criaPilha(int tam){
	pilha *p;
	int i, j;
	p = malloc(sizeof(pilha));
	if (p == NULL){
		printf("A pilha não pode ser alocada\n");
		free(p);
		exit(1);
	}
	p->v = malloc(tam*sizeof(int*));
	if (p->v == NULL){
		printf("A pilha não pode ser alocada\n");
		free(p->v);
		free(p);
		exit(1);
	}
	for (i = 0; i < tam; i++){
		p->v[i] = malloc(3*sizeof(int));
		if (p->v[i] == NULL){
			printf("A pilha não pode ser alocada\n");
			for (j = 0; j <= i; j++){
				free(p->v[j]);
			}
			free(p->v);
			free(p);
			exit(1);
		}
	}
	p->topo = 0;
	return p;
}

int pilhaVazia(pilha *p){
	return (p->topo == 0);
}

void empilha(pilha *p, int lin, int col, int move){
	p->v[p->topo][0] = lin;
	p->v[p->topo][1] = col;
	p->v[p->topo][2] = move;
	p->topo++;
	return ;
}

int desempilha(pilha *p, int *lin, int *col, int *move){
	if (pilhaVazia(p))
		return 0;
	p->topo--;
	*lin = p->v[p->topo][0];
	*col = p->v[p->topo][1];
	*move = p->v[p->topo][2];
	return 1;
}

int **criaMatriz(int m, int n){
	int **mat;
	int i, j;
	mat = malloc(m*sizeof(int*));
	if (mat == NULL){
		printf("A matriz não pode ser alocada\n");
		free(mat);
		exit(1);
	}
	for (i = 0; i < m; i++){
		mat[i] = malloc(n*sizeof(int));
		if (mat[i] == NULL){
			printf("A matriz não pode ser alocada\n");
			for (j = 0; j <= i; j++)
				free(mat[j]);
			free(mat);
			exit(1);
		}
	}
	return mat;
}

int concluido(int **mat, int **livres, int nLivres){
	int i, count = 0;
	for (i = 0; i < nLivres; i++){
		if (mat[livres[i][0]][livres[i][1]] == 1)
			count++;
	}
	return (count == nLivres);
}

void freeAll(pilha *p, int tam, int **mat1, int m1, int n1, int **mat2, int m2){
	int i;
	for (i = 0; i < tam; i++)
		free(p->v[i]);
	free(p->v);
	free(p);
	for (i = 0; i < m1; i++)
		free(mat1[i]);
	free(mat1);
	for (i = 0; i < m2; i++)
		free(mat2[i]);
	free(mat2);
}

int podeMexer(int lin, int col, int **mat, int m, int n, int attmove){
	if (mat[lin][col] == 1){
		if (lin-2 >= 0 && mat[lin-2][col] == -1 && mat[lin-1][col] == 1 && attmove < 0)
			return 0;
		if (col-2 >= 0 && mat[lin][col-2] == -1 && mat[lin][col-1] == 1 && attmove < 1)
			return 1;
		if (lin+2 < m && mat[lin+2][col] == -1 && mat[lin+1][col] == 1 && attmove < 2)
			return 2;
		if (col+2 < n && mat[lin][col+2] == -1 && mat[lin][col+1] == 1 && attmove < 3)
			return 3;
		return -1;
	}
	return -1;
}

void mexe(int lin, int col, int **mat, int move){
	mat[lin][col] = -mat[lin][col];
	switch (move){
		case 0:
			mat[lin-2][col] = -mat[lin-2][col];
			mat[lin-1][col] = -mat[lin-1][col];
			break;
		case 1:
			mat[lin][col-2] = -mat[lin][col-2];
			mat[lin][col-1] = -mat[lin][col-1];
			break;
		case 2:
			mat[lin+2][col] = -mat[lin+2][col];
			mat[lin+1][col] = -mat[lin+1][col];
			break;
		case 3:
			mat[lin][col+2] = -mat[lin][col+2];
			mat[lin][col+1] = -mat[lin][col+1];
			break;
	}
}

void imprimePilha(pilha *p){
	int i, lin, col, move;
	for (i = 0; i < p->topo; i++){
		lin = p->v[i][0];
		col = p->v[i][1];
		move = p->v[i][2];
		switch(move){
			case 0:
				printf("%d:%d-%d:%d\n", lin, col, lin-2, col);
				break;
			case 1:
				printf("%d:%d-%d:%d\n", lin, col, lin, col-2);
				break;
			case 2:
				printf("%d:%d-%d:%d\n", lin, col, lin+2, col);
				break;
			case 3:
				printf("%d:%d-%d:%d\n", lin, col, lin, col+2);
				break;
		}
	}
}

void imprimeMatriz(int **mat, int lin, int col, pilha *p, int total){
	int i, j;
	printf("===========================%d\n", total-p->topo);
	for (i = 0; i < lin; i++){
		for (j = 0; j < col; j++){
			printf("%d%c", mat[i][j], " \n"[j == col-1]);
		}
	}
	return ;
}

int main(){
	pilha *p;
	int **tab, **livres;
	int lin, col, i, j, k, ok;
	int nLivres = 0, nOcup = 0, attl = 0, attc = 0, attmove = 0;
	int moves = 0, working = 1;
	if (scanf("%d%d", &lin, &col) != 2)
		exit(1);
	p = criaPilha(lin*col);
	tab = criaMatriz(lin, col);
	for (i = 0; i < lin; i++){
		for (j = 0; j < col; j++){
			if (!scanf("%d", &tab[i][j]))
				exit(1);
			if (tab[i][j] == -1)
				nLivres++;
			else if (tab[i][j] == 1)
				nOcup++;
		}
	}
	livres = criaMatriz(nLivres, 2);
	if (nLivres > nOcup/2){
		printf("Impossível2\n");
		freeAll(p, lin*col, tab, lin, col, livres, nLivres);
		return 0;
	}
	for (i = 0, k = 0; i < lin && k != nLivres; i++){
		for (j = 0; j < col && k != nLivres; j++){
			if (tab[i][j] == -1){
				livres[k][0] = i;
				livres[k][1] = j;
				k++;
			}
		}
	}
	while ((p->topo != nOcup-nLivres || !concluido(tab, livres, nLivres)) && working){
		ok = 0;
		while (attl != lin && ok == 0){
			attmove = podeMexer(attl, attc, tab, lin, col, attmove);
			if (attmove != -1)
				ok = 1;
			else {
				if (attc == col-1){
					attc = 0;
					attl++;
				}
				else
					attc++;
			}
		}
		if (ok == 1){
			mexe(attl, attc, tab, attmove);
			empilha(p, attl, attc, attmove);
			/*printf("%d: %d,%d -> %d\n", moves, attl, attc, attmove);*/
			/*imprimeMatriz(tab, lin, col, p, nOcup-nLivres);*/
			attl = 0;
			attc = 0;
			attmove = -1;
		}
		else {
			if (!pilhaVazia(p)) {
				desempilha(p, &attl, &attc, &attmove);
				mexe(attl, attc, tab, attmove);
				/*printf("Desempilha\n");*/
			}
			else {
				printf("Impossível\n");
				working = 0;
			}
		}
		moves++;
		/*if (concluido(tab, livres, nLivres))
			imprimeMatriz(tab, lin, col, p, nOcup-nLivres);*/
		if (moves%10000000 == 0)
			printf("%d movimentos ja foram executados\n", moves);
	}
	imprimePilha(p);
	freeAll(p, lin*col, tab, lin, col, livres, nLivres);
	return 0;
}