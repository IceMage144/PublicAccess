#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

int T[1123];
int D[1123];
int Esp[1123];
int caix[11];

int main(){
	int c;
	int n;
	int top = 0;
	long long temp = 0;
	int res = 0;
	int vago = 301;
	int k = 0;
	cin>>c>>n;
	for (int i = 0; i<n; i++){
		cin>>T[i]>>D[i];
	}
	while (top != n){
		vago = 301;
		k = top;
		for (int i = 0; i<c; i++){
			if (caix[i] < vago){
				vago = caix[i];
			}
		}
		temp += vago;
		while (temp >= T[k] && k<n){
			Esp[k] = temp - T[k];
			k++;
		}
		for (int i = 0; i<c; i++){
			caix[i] -= vago;
			if (caix[i] == 0 && temp >= T[top]){
				caix[i] = D[top];
				top++;
			}
		}
	}
	for (int i = 0; i<n; i++){
		if (Esp[i] > 20){
			res++;
		}
	}
	cout<<res<<endl;
	return 0;
}