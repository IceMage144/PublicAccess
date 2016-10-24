/*
EP3 - MAC0121
João Gabriel Basi
No USP: 9793801
*/

/*O programa recebe um vetor desordenado de n posições e o ordena usando
3-reversões. Quando é possível ordená-lo, o programa imprime uma sequência
de movimentos que o fazem, quando não é possível, o programa imprime "Nao
e possivel".*/

#include <stdio.h>
#include <stdlib.h>
#include "myvector.h"

/*Parte da função "mergeSort" que junta dois vetores. A função calcula a
posição do número no vetor original com base na paridade "par" do vetor,
que pode ser 1 se o vetor for ímpar ou 0 se for par, e as imprime se
print != 0*/
void intercala (int v[], int ini, int meio, int fim, int par, int print){
    int pos = 0, aux1 = ini, aux2 = meio+1, i;
    int *Vaux;
    Vaux = criaVetor(fim-ini+1);
    while (aux1 <= meio && aux2 <= fim){
        if (v[aux1] > v[aux2]){
            Vaux[pos] = v[aux2];
            aux2++;
            if (print)
                for (i = meio-aux1+pos+ini; i >= pos+ini; i--)
                    printf("%d\n", 2*i+par);
        }
        else {
            Vaux[pos] = v[aux1];
            aux1++;
        }
        pos++;
    }
    while (aux1 <= meio){
        Vaux[pos] = v[aux1];
        aux1++;
        pos++;
    }
    while (aux2 <= fim){
        Vaux[pos] = v[aux2];
        aux2++;
        pos++;
    }
    for (aux1 = 0; aux1 < pos; aux1++)
        v[aux1+ini] = Vaux[aux1];
    free(Vaux);
}

/*Algoritmo recursivo de ordenação "merge"*/
void mergeSort (int v[], int ini, int fim, int par, int print){
    int meio;
    if (ini < fim){
        meio = (ini+fim)/2;
        mergeSort(v, ini, meio, par, print);
        mergeSort(v, meio+1, fim, par, print);
        intercala(v, ini, meio, fim, par, print);
    }
}

/*Retorna o índice do maior valor de um vetor "v" de tamanho "tam"*/
int pMaior (int v[], int tam) {
    int i, maior = v[0], ind = 0;
    for (i = 1; i < tam; i++)
        if (v[i] > maior || (v[i] == maior && i%2 != tam%2)){
            maior = v[i];
            ind = i;
        }
    return ind;
}

/*Recebe um vetor "v" e seu tamanho "tam" e retorna 1 se ele estiver
ordenado ou 0 caso contrário*/
int vetorOrdenado (int v[], int tam) {
    int i = 0;
    while (v[i] <= v[i+1] && i < tam-2)
        i++;
    return (v[i] <= v[i+1]);
}

/*Faz uma 3-reversão na posição "pos1" do vetor "v" de tamanho "tam" e
imprime pos1*/
void triReversao (int v[], int tam, int pos1) {
    int aux, pos2 = (pos1+2)%tam;
    aux = v[pos1];
    v[pos1] = v[pos2];
    v[pos2] = aux;
    printf("%d\n", pos1);
}

/*Separa os elementos do vetor "v" de tamanho "tam" em dois vetores "imp"
e "par" de acordo com a paridade de seus índices*/
void separa (int v[], int tam, int imp[], int par[]) {
    int i;
    for (i = 0; i < tam; i++)
        if (i%2)
            imp[i/2] = v[i];
        else
            par[i/2] = v[i];
}

/*Intercala os elementos dos vetores "imp" e "par" no vetor "v" de tamanho
"tam" de acordo com a paridade de seus índices*/
void junta (int v[], int tam, int imp[], int par[]) {
    int i;
    for (i = 0; i < tam; i++)
        if (i%2)
            v[i] = imp[i/2];
        else
            v[i] = par[i/2];
}

/*Realiza a ordenação de um vetor "v" de tamanho "tam" através de
3-reversões*/
void triSort (int v[], int tam) {
    int maior, desord, ini, i;
    int *par, *impar, *Vaux;
    desord = tam-1;
    if (tam%2){
        while (desord){
            ini = pMaior(v, desord+1);
            maior = ini;
            if (maior%2 == desord%2)
                while (maior != desord){
                    triReversao(v, tam, maior);
                    maior = (maior+2)%tam;
                }
            else {
                while (maior != desord) {
                    maior = (maior+tam-2)%tam;
                    triReversao(v, tam, maior);
                }
                maior = (maior+2)%tam;
                while (maior > desord) {
                    triReversao(v, tam, maior);
                    maior = (maior+2)%tam;
                }
            }
            desord--;
        }
    }
    else {
        par = criaVetor(tam/2);
        impar = criaVetor(tam/2);
        Vaux = criaVetor(tam);
        for (i = 0; i < tam; i++)
            Vaux[i] = v[i];
        separa(Vaux, tam, impar, par);
        mergeSort(impar, 0, (tam/2)-1, 1, 0);
        mergeSort(par, 0, (tam/2)-1, 0, 0);
        junta(Vaux, tam, impar, par);
        if (vetorOrdenado(Vaux, tam)){
            separa(v, tam, impar, par);
            mergeSort(impar, 0, (tam/2)-1, 1, 1);
            mergeSort(par, 0, (tam/2)-1, 0, 1);
            junta(v, tam, impar, par);
        }
        else
            printf("Nao e possivel\n");
        free(par);
        free(impar);
        free(Vaux);
    }
}

int main () {
    int tam, i;
    int *v;
    if (!scanf("%d", &tam))
        exit(1);
    if (tam <= 1)
        return 0;
    v = criaVetor(tam);
    for (i = 0; i < tam; i++){
        if (!scanf("%d", &v[i])){
            free(v);
            exit(1);
        }
    }
    triSort(v, tam);
    free(v);
    return 0;
}