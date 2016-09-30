/*
EP2 - MAC0121
Nome: João Gabriel Basi
No USP: 9793801
*/

/*O programa recebe as dimensões de um tabuleiro e as peças de cada
posição do tabuleiro de "resta um" e imprime uma sequência de
movimentos que resolvem o tabuleiro. Caso não há uma solução, o
progrma imprime "Impossivel"*/

#include <stdio.h>
#include <stdlib.h>

#define STEP 100000000

/*======================Funções sobre pilhas=======================*/
/*Define uma pilha como sendo uma estrutura com uma matriz para
guardar a pilha em si, uma variável inteira para guardar a posição
de seu topo e uma para guardar o seu tamanho máximo*/
typedef struct {
    int topo, pMax;
    int **v;
} pilha;

/*Aloca a pilha, sua matriz, com três colunas e "tam" linhas, e zera o
topo. Retorna um ponteiro para pilha*/
pilha *criaPilha (int tam){
    pilha *p;
    int i, j;
    p = malloc(sizeof(pilha));
    if (p == NULL){
        free(p);
        exit(1);
    }
    p->v = malloc(tam*sizeof(int*));
    if (p->v == NULL){
        free(p->v);
        free(p);
        exit(1);
    }
    for (i = 0; i < tam; i++){
        p->v[i] = malloc(3*sizeof(int));
        if (p->v[i] == NULL){
            for (j = 0; j <= i; j++)
                free(p->v[j]);
            free(p->v);
            free(p);
            exit(1);
        }
    }
    p->topo = 0;
    p->pMax = tam - 1;
    return p;
}

/*retorna 1 se a pilha "p" estiver vazia (ou seja, seu "topo" = 0), ou
0 caso contrário*/
int pilhaVazia (pilha *p){
    return (p->topo == 0);
}

/*Retorna 1 se a pilha estiver cheia ou 0 caso contrário*/
int pilhaCheia (pilha *p){
    return (p->topo == p->pMax);
}

/*Retorna 1 se a pilha tem mais camadas do que seu máximo e 0 caso
contrário*/
int pilhaEstourou (pilha *p){
    return (p->topo > p->pMax);
}

/*empilha uma posição com linha "lin" e coluna "col" e um movimento
"move" na pilha "p", além de aumentar o topo da pilha*/
void empilha (pilha *p, int lin, int col, int move){
    p->v[p->topo][0] = lin;
    p->v[p->topo][1] = col;
    p->v[p->topo][2] = move;
    p->topo++;
    return ;
}

/*Desempilha os elementos do topo da pilha "p" e guarda-os em "lin",
"col" e "move"*/
void desempilha (pilha *p, int *lin, int *col, int *move){
    p->topo--;
    *lin = p->v[p->topo][0];
    *col = p->v[p->topo][1];
    *move = p->v[p->topo][2];
    return ;
}

/*Imprime os movimentos guardados na pilha "p"*/
void imprimePilha (pilha *p){
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

/*Desaloca uma pilha de tamanho tam*/
void freePilha (pilha *p, int tam){
    int i;
    for (i = 0; i < tam; i++)
        free(p->v[i]);
    free(p->v);
    free(p);
    return;
}

/*=====================Funções sobre matrizes======================*/
/*Aloca uma matriz com "m" linhas e "n" colunas e retorna um ponteiro
para ela*/
int **criaMatriz (int m, int n){
    int **mat;
    int i, j;
    mat = malloc(m*sizeof(int*));
    if (mat == NULL){
        free(mat);
        exit(1);
    }
    for (i = 0; i < m; i++){
        mat[i] = malloc(n*sizeof(int));
        if (mat[i] == NULL){
            for (j = 0; j <= i; j++)
                free(mat[j]);
            free(mat);
            exit(1);
        }
    }
    return mat;
}

/*Analiza a última posição de linha "lin" e coluna "col", o último
movimento, "move", e a matriz "mat" de "m" linhas e "n" colunas e decide
se há um movimento possível. Retorna 0 se o movimento for para
cima, 1 para a esquerda, 2 para baixo, 3 para a direita ou -1 se não
há movimentos possíveis*/
int podeMexer (int **mat, int m, int n, int lin, int col, int move){
    if (mat[lin][col] == 1){
        if (move < 0 && lin-2 >= 0 && mat[lin-2][col] == -1 && mat[lin-1][col] == 1)
            return 0;
        if (move < 1 && col-2 >= 0 && mat[lin][col-2] == -1 && mat[lin][col-1] == 1)
            return 1;
        if (move < 2 && lin+2 < m && mat[lin+2][col] == -1 && mat[lin+1][col] == 1)
            return 2;
        if (move < 3 && col+2 < n && mat[lin][col+2] == -1 && mat[lin][col+1] == 1)
            return 3;
        return -1;
    }
    return -1;
}

/*Executa o movimento "move" na peça da linha "lin" e coluna "col".
O valor de "move" segue as mesmas regras da função podeMexer*/
void mexe (int lin, int col, int **mat, int move){
    /*Como as peças e os buracos são representados por 1 e -1 respectivamente
    e, depois do movimento, as peças são substituidas por buracos e vice-versa,
    a função nega os números das posições em que o movimento aconteceu, o que
    permite voltar o movimento também*/
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

/*Desaloca uma matriz de m linhas*/
void freeMatriz (int **mat, int m){
    int i;
    for (i = 0; i < m; i++)
        free(mat[i]);
    free(mat);
    return;
}

/*==========================Miscelânea=============================*/
/*Recebe o tabuleiro "mat", uma matriz com as posições dos espaços livres
no começo do jogo "livres" e seu número de linhas "nLivres" e verifica se
todas as posições que estavam livres no começo do jogo estão ocupadas.
Retorna 1 se sim ou 0 caso contrário*/
int concluido (int **mat, int **livres, int nLivres){
    int i, count = 0;
    for (i = 0; i < nLivres; i++)
        if (mat[livres[i][0]][livres[i][1]] == 1)
            count++;
    return (count == nLivres);
}

/*Cria um vetor "v" com tamanho "len" preenchido com "val" em cada
posição e retorna um ponteiro para ele*/
int *criaVetor (int len, int val){
    int *v, i;
    v = malloc(len*sizeof(int));
    if (v == NULL){
        printf("O vetor não pode ser alocado\n");
        free(v);
        exit(1);
    }
    for (i = 0; i < len; i++)
        v[i] = val;
    return v;
}

/*Executa um algoritmo flood fill recursivo (parecido com uma dfs
(depth-first search)) para identificar se há partes desconexas no
tabuleiro. Se entrou em ao menos um if retorna 1, caso contrário
retorna 0*/
int floodFill (int **mat, int m, int n, int lin, int col){
    int loop = 0;
    if (lin+1 < m && mat[lin+1][col] == 1){
        mat[lin+1][col] = 2;
        floodFill(mat, m, n, lin+1, col);
        loop = 1;
    }
    if (col+1 < n && mat[lin][col+1] == 1){
        mat[lin][col+1] = 2;
        floodFill(mat, m, n, lin, col+1);
        loop = 1;
    }
    if (lin-1 >= 0 && mat[lin-1][col] == 1){
        mat[lin-1][col] = 2;
        floodFill(mat, m, n, lin-1, col);
        loop = 1;
    }
    if (col-1 >= 0 && mat[lin][col-1] == 1){
        mat[lin][col-1] = 2;
        floodFill(mat, m, n, lin, col-1);
        loop = 1;
    }
    return loop;
}

/*Faz alguns testes no tabuleiro (que são descritos melhor no corpo da
função e no relatório) para saber se ele tem chance de ser resolvido
ou é impossível resolvê-lo. Retorna 1 se passou nos testes ou 0 caso
contrário*/
int ehPossivel (int **mat, int m, int n, int nOcup, int nLivres, int **livres){
    int **matAux;
    int *endClass, *begClass;
    int i, j, auxl, auxc, aux1, aux2;
    /*Teste 1 (mais informações sobre os testes no relatório)*/
    if (nLivres > nOcup/2)
        return 0;
    matAux = criaMatriz(m, n);
    /*Cria os vetores das classes já com a paridade do número de peças
    e do número de espaços livres*/
    endClass = criaVetor(6, nLivres%2);
    begClass = criaVetor(6, nOcup%2);
    /*Calcula a classe do tabuleiro inicial (begClass) e a classe do
    tabuleiro final (endClass), e também copia o tabuleiro para "matAux"*/
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            matAux[i][j] = mat[i][j];
            /*"aux1" guarda se a posição de linha i e coluna j deve ser
            marcada com 0, 1 ou 2 e o "aux2", se deve ser marcada
            com 3, 4, ou 5. Para isso utilizo a propriedade que a soma
            i+j é constante para as diagonais que vão do canto direito
            de cima ao canto esquerdo de baixo, então calculo o módulo
            3 dessa soma para os números de 0 a 2. Para 3, 4 e 5 eu 
            inverti a numeração das colunas para inverter as diagonais,
            então a soma fica i+(n-j)*/
            aux1 = (i+j)%3;
            aux2 = 5 - (i+n-j)%3;
            if (mat[i][j] == 1){
                /*Como as classes são definidas pela paridade de seus
                números, podemos interpretá-las como números módulo
                2 (com 0 = par e 1 = ímpar) assim, ao adicionarmos ou
                subtrairmos 1 de uma posição do vetor, estamos negando
                seu valor (pois (1-1)%2 = (1+1)%2 = 0 = !1 e
                (0-1)%2 = (0+1)%2 = 1 = !0)*/
                begClass[aux1] = !begClass[aux1];
                begClass[aux2] = !begClass[aux2];
            }
            else if (mat[i][j] == -1){
                endClass[aux1] = !endClass[aux1];
                endClass[aux2] = !endClass[aux2];
            }
        }
    }
    /*Teste 2*/
    for (i = 0; i < 6; i++){
        if (endClass[i] != begClass[i]){
            freeMatriz(matAux, m);
            free(endClass);
            free(begClass);
            return 0;
        }
    }
    /*Executa a função floodFill em todas as posições livres para verificar
    se o tabuleiro tem partes desconexas sem espaços vazios e substitui
    as posições verificadas por 2*/
    for (i = 0; i < nLivres; i++){
        auxl = livres[i][0];
        auxc = livres[i][1];
        if (floodFill(matAux, m, n, auxl, auxc))
            matAux[auxl][auxc] = 2;
    }
    /*Teste 3*/
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            if (matAux[i][j] == 1){
                freeMatriz(matAux, m);
                free(endClass);
                free(begClass);
                return 0;
            }
    return 1;
}

int main (){
    pilha *p;
    int **tab, **livres;
    int lin, col, i, j, k, ok;
    int nLivres = 0, nOcup = 0, attl = 0, attc = 0, attmove = 0;
    int working = 1;
    if (scanf("%d%d", &lin, &col) != 2)
        exit(1);
    tab = criaMatriz(lin, col);
    for (i = 0; i < lin; i++)
        for (j = 0; j < col; j++){
            if (!scanf("%d", &tab[i][j]))
                exit(1);
            if (tab[i][j] == -1)
                nLivres++;
            else if (tab[i][j] == 1)
                nOcup++;
        }
    p = criaPilha(nOcup-nLivres+1);
    livres = criaMatriz(nLivres, 2);
    for (i = 0, k = 0; i < lin && k != nLivres; i++)
        for (j = 0; j < col && k != nLivres; j++)
            if (tab[i][j] == -1){
                livres[k][0] = i;
                livres[k][1] = j;
                k++;
            }
    if (!ehPossivel(tab, lin, col, nOcup, nLivres, livres)){
        printf("Impossivel\n");
        freePilha(p, nOcup-nLivres+1);
        freeMatriz(tab, lin);
        freeMatriz(livres, nLivres);
        return 0;
    }
    while ((!pilhaCheia(p) || !concluido(tab, livres, nLivres)) && working){
        ok = 0;
        while (attl != lin && ok == 0){
            attmove = podeMexer(tab, lin, col, attl, attc, attmove);
            if (attmove != -1)
                ok = 1;
            else
                if (attc == col-1){
                    attc = 0;
                    attl++;
                }
                else
                    attc++;
        }
        if (ok == 1){
            mexe(attl, attc, tab, attmove);
            empilha(p, attl, attc, attmove);
            attl = 0;
            attc = 0;
            attmove = -1;
        }
        else /*Backtracking*/
            if (!pilhaVazia(p)){
                desempilha(p, &attl, &attc, &attmove);
                mexe(attl, attc, tab, attmove);
            }
            else {
                printf("Impossivel\n");
                working = 0;
            }
        if (pilhaEstourou(p)){
            desempilha(p, &attl, &attc, &attmove);
            mexe(attl, attc, tab, attmove);
        }
    }
    imprimePilha(p);
    freePilha(p, nOcup-nLivres+1);
    freeMatriz(tab, lin);
    freeMatriz(livres, nLivres);
    return 0;
}