#include <iostream>

using namespace std;

int main(){
	int noNum, j = 0, k = 0, noMen, index;
	cin >> noNum >> noMen;
	long long lista[112345], ord[112345], aux, menor = 1e9;
	for (int i = 0; i < noNum; i++){
		cin >> lista[i];
	}
	while (j < noMen+1 && j < noNum-1){
		k = j;
		menor = 1e9;
		index = j;
		while (k < noNum){
			if (lista[k] < menor){
				menor = lista[k];
				index = k;
			}
			k++;
		}
		//cout << index << ":" << lista[index] << "<->" << j << ":" << lista[j] << endl;
		aux = lista[index];
		lista[index] = lista[j];
		lista[j] = aux;
		j++;
	}
	cout << lista[noMen-1] << endl;
	return 0;
}