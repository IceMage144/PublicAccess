#include <iostream>

using namespace std;

int main(){
	int noNum, j = 0, k = 0;
	cin >> noNum;
	long long lista[1123], ord[1123], aux;
	for (int i = 0; i < noNum; i++){
		cin >> lista[i];
	}
	while (j < noNum-1){
		k = j;
		while (k >= 0 && lista[k] > lista[k+1]){
			aux = lista[k];
			lista[k] = lista[k+1];
			lista[k+1] = aux;
			k--;
		}
		j++;
	}
	for (int i = 0; i < noNum; i++){
		cout << lista[i] << " \n"[i == noNum-1];
	}
	return 0;
}