#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define debug(args...) cout << args << endl

int fib[151234];
int save[151234];
int pian = 150000;

int main(){
	int noImp, A[112], B[112], j = 0, index;
	long long menor = 111000;
	int aux = 0;
	fib[0] = 0;
	fib[1] = 1;
	save[0] = 0;
	save[1] = 1;
	cin >> noImp;
	for (int i = 0; i < noImp; i++){
		cin >> A[i] >> B[i];
	}
	for (int i = 2; i < 150100; i++){
		fib[i] = (fib[i-1] + fib[i-2])%100000;
		save[i] = fib[i];
	}
	for (int i = 0; i < noImp; i++){
		cout << "Case " << i+1 << ": ";
		j = 0;
		if (A[i] + B[i] <= pian){
			while (j <= B[i] && j < 100){
				menor = 111000; 
				for (int k = A[i]-1; k < A[i]+B[i]; k++){
					if (fib[k] < menor && fib[k] >= 0){
						menor = fib[k];
						index = k;
					}
				}
				cout << fib[index] << " \n"[j == B[i] || j == 99];
				j++;
				fib[index] = -1;
			}
		}
		else {
			while (j <= B[i] && j < 100){
				menor = 111000;
				for (int k = 0; k < pian; k++){
					if (fib[k] < menor && fib[k] >= 0){
						menor = fib[k];
						index = k;
					}
				}
				if (index < (B[i]+A[i])%pian || index > A[i]){
					aux = (A[i]+B[i])/pian;
				}
				else {
					aux = (A[i]+B[i])/pian - 1;
				}
				for (int k = 0; k < aux; k++){
					if (j <= B[i] && j < 100){
						cout << fib[index] << "/" << index << " \n"[j == B[i] || j == 99];
						j++;
					}
				}
				fib[index] = -1;
			}
		}
		for (int k = 0; k <= pian; k++){
			fib[k] = save[k];
		}
	}
	return 0;
}