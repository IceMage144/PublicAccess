#include <stdio.h>
#include <stdlib.h>

#define STEP 100000000

/*=====================Funções sobre pilhas=====================*/
/*Define uma pilha como sendo uma estrutura com uma matriz para
guardar a pilha em si e uma variável inteira para guardar a posição
de seu topo*/
typedef struct {
    int topo;
    int **v;
} pilha;

/*Aloca a pilha, sua matriz, com três colunas e tam linhas, zera o
topo e retorna um ponteiro para pilha*/
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

/*retorna 1 se a pilha p estiver vazia (ou seja, seu topo = 0), ou
0 caso contrário*/
int pilhaVazia(pilha *p){
    return (p->topo == 0);
}

/*empilha uma posição com linha = lin e coluna = col e um movimento
move na pilha p, além de aumentar o topo da pilha*/
void empilha(pilha *p, int lin, int col, int move){
    p->v[p->topo][0] = lin;
    p->v[p->topo][1] = col;
    p->v[p->topo][2] = move;
    p->topo++;
    return ;
}

/*Desempilha os elementos do topo da pilha p e guarda-os em lin,
col e move. Retorna 1 se conseguiu desempilhar ou 0 caso contrário*/
int desempilha(pilha *p, int *lin, int *col, int *move){
    if (pilhaVazia(p))
        return 0;
    p->topo--;
    *lin = p->v[p->topo][0];
    *col = p->v[p->topo][1];
    *move = p->v[p->topo][2];
    return 1;
}

/*Imprime os movimentos guardados na pilha p*/
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

/*=====================Funções sobre matrizes======================*/
/*Aloca uma matriz com lin linhas e col colunas e retorna um ponteiro
para ela*/
int **criaMatriz(int lin, int col){
    int **mat;
    int i, j;
    mat = malloc(lin*sizeof(int*));
    if (mat == NULL){
        printf("A matriz não pode ser alocada\n");
        free(mat);
        exit(1);
    }
    for (i = 0; i < lin; i++){
        mat[i] = malloc(col*sizeof(int));
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

/*Analiza a última posição de linha attl e coluna attc, o último
movimento, attmove, e a matriz mat de lin linhas e col colunas e decide
se há um movimento possível. Retorna 0 se o movimento for para
cima, 1 para a esquerda, 2 para baixo, 3 para a direita e -1 se não
há movimentos possíveis*/
int podeMexer(int **mat, int lin, int col, int attl, int attc, int attmove){
    if (mat[attl][attc] == 1){
        if (attl-2 >= 0 && mat[attl-2][attc] == -1 && mat[attl-1][attc] == 1 && attmove < 0)
            return 0;
        if (attc-2 >= 0 && mat[attl][attc-2] == -1 && mat[attl][attc-1] == 1 && attmove < 1)
            return 1;
        if (attl+2 < lin && mat[attl+2][attc] == -1 && mat[attl+1][attc] == 1 && attmove < 2)
            return 2;
        if (attc+2 < col && mat[attl][attc+2] == -1 && mat[attl][attc+1] == 1 && attmove < 3)
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

int concluido(int **mat, int **livres, int nLivres){
    int i, count = 0;
    for (i = 0; i < nLivres; i++){
        if (mat[livres[i][0]][livres[i][1]] == 1)
            count++;
    }
    return (count == nLivres);
}

void freeAll(pilha *p, int tam, int **mat1, int m1, int **mat2, int m2){
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

void freeAll2(int **mat, int m, int *v1, int *v2){
    int i;
    for (i = 0; i < m; i++)
        free(mat[i]);
    free(mat);
    free(v1);
    free(v2);
}

void imprimeMatriz(int **mat, int lin, int col){
    int i, j;
    printf("============================\n");
    for (i = 0; i < lin; i++){
        for (j = 0; j < col; j++){
            printf("%d%c", mat[i][j], " \n"[j == col-1]);
        }
    }
    return ;
}

void imprimeVetor(int *v, int len){
	int i;
	printf("[");
	for (i = 0; i < len; i++){
		printf("%d%c", v[i], " ]"[i == len-1]);
	}
	printf("\n");
	return ;
}

int *criaVetor(int len, int val){
    int *v, i;
    v = malloc(len*sizeof(int));
    if (v == NULL){
        printf("O vetor não pode ser alocado\n");
        free(v);
        exit(1);
    }
    for (i = 0; i < len; i++){
        v[i] = val;
    }
    return v;
}

void dfs(int **mat, int attl, int attc, int lin, int col){
    if (attl+1 < lin && mat[attl+1][attc] == 1){
        mat[attl+1][attc] = 2;
        dfs(mat, attl+1, attc, lin, col);
    }
    if (attc+1 < col && mat[attl][attc+1] == 1){
        mat[attl][attc+1] = 2;
        dfs(mat, attl, attc+1, lin, col);
    }
    if (attl-1 >= 0 && mat[attl-1][attc] == 1){
        mat[attl-1][attc] = 2;
        dfs(mat, attl-1, attc, lin, col);
    }
    if (attc-1 >= 0 && mat[attl][attc-1] == 1){
        mat[attl][attc-1] = 2;
        dfs(mat, attl, attc-1, lin, col);
    }
    return ;
}

int ehPossivel(int **mat, int lin, int col, int nOcup, int nLivres, int **livres){
    int **matAux;
    int *eptClass, *fullClass;
    int i, j, auxl, auxc, ok = 0;
    matAux = criaMatriz(lin, col);
    eptClass = criaVetor(6, nLivres%2);
    fullClass = criaVetor(6, nOcup%2);
    for (i = 0; i < lin; i++){
        for (j = 0; j < col; j++){
            matAux[i][j] = mat[i][j];
            if (mat[i][j] == 1){
                if ((i+j)%3 == 0){
                    fullClass[0] = !fullClass[0];
                }
                else if ((i+j)%3 == 1){
                    fullClass[1] = !fullClass[1];
                }
                else {
                    fullClass[2] = !fullClass[2];
                }
                if ((i+col-j)%3 == 0){
                    fullClass[5] = !fullClass[5];
                }
                else if ((i+col-j)%3 == 1){
                    fullClass[4] = !fullClass[4];
                }
                else {
                    fullClass[3] = !fullClass[3];
                }
            }
            else if (mat[i][j] == -1){
                if ((i+j)%3 == 0){
                    eptClass[0] = !eptClass[0];
                }
                else if ((i+j)%3 == 1){
                    eptClass[1] = !eptClass[1];
                }
                else {
                    eptClass[2] = !eptClass[2];
                }
                if ((i+col-j)%3 == 0){
                    eptClass[5] = !eptClass[5];
                }
                else if ((i+col-j)%3 == 1){
                    eptClass[4] = !eptClass[4];
                }
                else {
                    eptClass[3] = !eptClass[3];
                }
            }
        }
    }
    printf("full: ");
    imprimeVetor(fullClass, 6);
    printf("empty: ");
    imprimeVetor(eptClass, 6);
    i = 0;
    while (i != 6){
        if (eptClass[i] != fullClass[i]){
            freeAll2(matAux, lin, eptClass, fullClass);
            return 0;
        }
        i++;
    }
    for (i = 0; i < nLivres; i++){
        auxl = livres[i][0];
        auxc = livres[i][1];
        matAux[auxl][auxc] = 2;
        dfs(matAux, auxl, auxc, lin, col);
    }
    imprimeMatriz(matAux, lin, col);
    i = 0;
    j = 0;
    while (ok == 0 && i < lin){
        j = 0;
        while (ok == 0 && j < col){
            if (matAux[i][j] == 1){
                ok = 1;
            }
            j++;
        }
        i++;
    }
    freeAll2(matAux, lin, eptClass, fullClass);
    if (ok == 1){
    	return 0;
    }
    else {
    	return 1;
    }
}

int main(){
    pilha *p;
    int **tab, **livres;
    int lin, col, i, j, k, ok;
    int nLivres = 0, nOcup = 0, attl = 0, attc = 0, attmove = 0;
    int working = 1;
    long moves = 0;
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
    for (i = 0, k = 0; i < lin && k != nLivres; i++){
        for (j = 0; j < col && k != nLivres; j++){
            if (tab[i][j] == -1){
                livres[k][0] = i;
                livres[k][1] = j;
                k++;
            }
        }
    }
    if (nLivres > nOcup/2 || !ehPossivel(tab, lin, col, nOcup, nLivres, livres)){
        printf("Impossível2\n");
        freeAll(p, lin*col, tab, lin, livres, nLivres);
        return 0;
    }
    printf("Pré-testes concluídos\n");
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
        if (moves%STEP == 0)
            printf("%d movimentos ja foram executados\n", moves);
    }
    imprimePilha(p);
    freeAll(p, lin*col, tab, lin, livres, nLivres);
    return 0;
}