#include <iostream>
#include <string.h>
using namespace std;

long long res[501];
long long vres[345678];

int main(){
	int n;
	cin>>n;
	for (int i = 0; i<n; i++){
		char S[1123456];
		char Sc[1123456];
		cin>>S;
		long long size = strlen(S);
		long long k = 0;
		long long x = 0;
		int finish = 0;
		long long comb = 0;
		for (long long j = 0; j<size; j++){
			Sc[j] = S[j];
		}
		if (S[0] == '<'){
			while (x<size-1){
				k=x+1;
				if (S[x] == '<' && S[k] == '>'){
					S[x] = '{';
					S[k] = '}';
				}
				x++;
			}
			while (finish == 0) {
				x = 0;
				finish = 1;
				for (long long j = 0; j<size; j++){
					Sc[j] = S[j];
				}
				while (x<size-1){
					k=x+1;
					if (S[x] == '<'){
						while (k<size && S[k] != '<' && S[k] != '>'){
							k++;
						}
						if (S[k] == '>'){
							S[x] = '{';
							S[k] = '}';
						}
						x = k-1;
					}
					x++;
				}
				x = 0;
				while (x<size && finish == 1){
					if (Sc[x] != S[x]){
						finish = 0;
					}
					x++;
				}
			}
			x = 0;
			while (x<size-1){
				k=x+1;
				if ((S[x] == '{' || S[x] == '}') && S[0] != '<'){
					while (k<size && (S[k] == '{' || S[k] == '}')){
						k++;
					}
					vres[comb] = k-x;
					x = k-1;
					comb++;
				}
				x++;
				if (x == size-1 && comb == 0){
					vres[0] = 0;
				}
			}
			res[i] = vres[0];
		}
		else{
			res[i] = 0;
		}
	}
	for (int i = 0; i<n; i++){
		cout<<res[i]<<endl;
	}
	return 0;
}