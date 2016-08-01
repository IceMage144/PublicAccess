#include <iostream>

using namespace std;

long long timer = 0;
#define addt() //timer++;

int main(){
	int noOrd, noNord, i = 0, j = 0;
	long long ord[112345], nord[30], final[112345], diff, aux, menor, index;
	cin >> noOrd;
	for(int k = 0; k < noOrd; k++){
		cin >> ord[k];
		addt();
	}
	cin >> noNord;
	for(int k = 0; k < noNord; k++){
		cin >> nord[k];
		addt();
	}
	cin >> diff;
	//Search sort para ordenar o nord
	while (j < noNord){
		i = j;
		menor = 1e9;
		index = j;
		while (i < noNord){
			if (nord[i] < menor){
				menor = nord[i];
				index = i;
				addt();
			}
			i++;
			addt();
		}
		//cout << index << ":" << nord[index] << "<->" << j << ":" << nord[j] << endl;
		aux = nord[index];
		nord[index] = nord[j];
		nord[j] = aux;
		j++;
		addt();
	}
	j = 0;
	i = 0;
	//Merge sort com ord e nord
	while (i < noOrd && j < noNord){
		if (ord[i] < nord[j]){
			final[i+j] = ord[i];
			i++;
		}
		else{
			final[i+j] = nord[j];
			j++;
		}
		addt();
		addt();
	}
	if (i == noOrd){
		for (int k = j; k < noNord; k++){
			final[i+k] = nord[k];
			addt();
		}
	}
	else{
		for (int k = i; k < noOrd; k++){
			final[j+k] = ord[k];
			addt();
		}
	}
	addt();
	j = 0;
	i = 0;
	aux = -1;
	//Achando a maior diferença (melhorar esse algoritmo)
	while (aux != diff && i < noOrd+noNord-1){
		j = i;
		while (final[j]-final[i] <= diff && j < noOrd+noNord){
			j++;
			addt();
		}
		if (aux < final[j-1]-final[i]){
			aux = final[j-1]-final[i];
			addt();
		}
		i++;
		addt();
	}
	for (int k = 0; k < noOrd+noNord; k++){
		cout << final[k] << " \n"[k == noOrd+noNord-1];
		addt();
	}
	cout << aux << endl;
	cout << timer << " loops" << endl;
	return 0;
}