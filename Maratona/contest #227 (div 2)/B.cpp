#include <iostream>
#include <map>

using namespace std;

int main(){
	int noProb, noGeor, j = 0;
	long long prob[3123], res = 0, aux, maior = 0, extra[3123];
	map<long long, int> check;
	cin >> noProb >> noGeor;
	for (int i = 0; i < noProb; i++){
		cin >> prob[i];
		check[prob[i]] = 0;
	}
	for (int i = 0; i < noGeor; i++){
		cin >> aux;
		check[aux] += 1;
		if (aux > maior){
			maior = aux;
		}
	}
	aux = 0;
	for (int i = 0; i < noProb; i++){
		if (check[prob[i]] == 0){
			res++;
			extra[aux] = prob[i];
			aux++;
		}
		else {
			check[prob[i]] -= 1;
		}
	}
	for (int i = 0; i < aux; i++){
		for (int j = maior; j > extra[i]; j--){
			if (check[j] >= 1){
				check[j] -= 1;
				res--;
			}
		}
	}
	cout << res << endl;
	return 0;
}