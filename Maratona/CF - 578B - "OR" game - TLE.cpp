#include <iostream>
#include <cmath>

using namespace std;

#define debug(args...) //cout<<args<<endl

int main(){
	int n, k, x, maior = 0, index = 0;
	long long numbers[212345], res[212345], aux = 0;
	cin >> n >> k >> x;
	for (int i = 0; i < n; i++){
		cin >> numbers[i];
	}
	for (int m = 0; m < k; m++){
		maior = 0;
		index = 0;
		for (int j = 0; j < n; j++){
			aux = 0;
			for (int i = 0; i < n; i++){
				if (i != j){
					aux = numbers[i] | aux;
				}
				else {
					aux = (numbers[i]*x) | aux;
				}
			}
			res[j] = aux;
		}
		for (int i = 0; i < n; i++){
			if (res[i] > maior){
				maior = res[i];
				index = i;
			}
		}
		numbers[index] *= x;
		debug(numbers[index]);
	}
	aux = 0;
	for (int i = 0; i < n; i++){
		aux = aux | numbers[i];
		debug(numbers[i]);
	}
	cout << aux << endl;
	return 0;
}