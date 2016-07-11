#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define debug(args...) cout << args << endl

vector<int> list;
vector<int> list2;
//fib = sum e aaa = seq de fibonacci
//10^6 impossibru
int fib[112345];
vector<int> aaa;

int main(){
	int noImp, A[112], B[112], maior = 0;
	long long menor = 111000;
	int count = 0;
	aaa[0] = 0;
	aaa[1] = 1;
	cin >> noImp;
	for (int i = 0; i < noImp; i++){
		cin >> A[i] >> B[i];
		if (B[i] + A[i] > maior){
			maior = B[i] + A[i];
		}
	}
	for (int i = 2; i < maior+1; i++){
		aaa[i] = (aaa[i-1] + aaa[i-2])%100000;
	}
	for (int i = 0; i < noImp; i++){
		maior = 0;
		menor = 111000;
		cout << "Case " << i+1 << ": ";
		for (int j = 0; j <= B[i]; j++){
			list[j] = aaa[A[i] + j - 1];
			fib[list[j]]++;
			if (list[j] > maior){
				maior = list[j];
			}
			if (list[j] < menor){
				menor = list[j];
			}
		}
		fib[menor] = 0;
		for (int j = menor + 1; j <= maior; j++){
			fib[j] += fib[j-1];
		}
		for (int j = 0; j <= B[i]; j++){
			list2[fib[list[j]]] = list[j];
			fib[list[j]]--;
		}
		for (int j = 0; j <= B[i] && j < 100; j++){
			cout << list2[j] << " \n"[j == B[i] || j == 99];
		}
		for (int j = menor; j <= maior; j++){
			fib[j] = 0;
		}
	}
	return 0;
}