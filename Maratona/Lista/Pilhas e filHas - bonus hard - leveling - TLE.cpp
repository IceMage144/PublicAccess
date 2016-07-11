#include <iostream>
#include <string.h>
#include <math.h>
#include <iomanip>

using namespace std;

float pilha[1123456];
float tvm[1123456];
float res[1123456];

int main(){
	int n;
	cin>>n;
	for(int i = 0; i<n; i++){
		char terr[1123456];
		int len, R;
		cin>>len>>R;
		cin>>terr;
		int val = 0;
		float menor = 3000;
		float menor2 = 3000;
		int aux = 0;
		cout<<fixed<<setprecision(1);
		//calcula os valores das pilhas, acha o menor e acha tvm = abs(j-(j+R))
		for (int j = 0; j<len; j++){
			if (terr[j] == '/'){
				pilha[j] = val + 0.5;
				val++;
			}
			else if (terr[j] == 92){
				pilha[j] = val - 0.5;
				val--;
			}
			else {
				pilha[j] = val;
			}
			if (j >= R-1){
				tvm[j-R+1] = fabs(pilha[j] - pilha[j-R+1]);
				if (tvm[j-R+1] < menor){
					menor = tvm[j-R+1];
				}
			}
		}
		/*
		for (int j = 0; j<len-R+1; j++){
			menor2 = 3000;
			res[aux] = 0;	
			for (int k = 0; k<R; k++){
				if (pilha[j+k] < menor2){
					menor2 = pilha[j+k];
				}
			}
			if ((double)(int)menor2 != menor2){
				menor2-=0.5;
			}
			for (int k = 0; k<R; k++){
				res[aux] += pilha[j+k] - menor2;
			}
			aux++;
		}
		for(int j = 0; j<len-R+1; j++){
			if (menor > res[j]){
				menor = res[j];
			}
		}
		cout<<fixed<<setprecision(1);
		cout<<"Case #"<<i+1<<": "<<menor<<endl;
		*/

		//acha os valores para o nivelamento das pilha com o menor tvm
		for (int j = 0; j<len-R+1; j++){
			if (tvm[j] == menor){
				menor2 = 3000;
				res[aux] = 0;	
				for (int k = 0; k<R; k++){
					if (pilha[j+k] < menor2){
						menor2 = pilha[j+k];
					}
				}
				if ((float)(int)menor2 != menor2){
					menor2-=0.5;
				}
				for (int k = 0; k<R; k++){
					res[aux] += pilha[j+k] - menor2;
				}
				aux++;
				tvm[j] = 1000;
			}
		}
		//acha o menor valor de nivelamento dentre os de menor tvm
		menor = 1000;
		for(int j = 0; j<aux; j++){
			if (res[j] < menor){
				menor = res[j];
			}
		}
		//se o valor ainda pode ser menor, entao faz tudo de novo mas sem os tvm ja analizados antes
		if (menor/R > 0.5){
			menor = 1000;
			for (int j = 0; j<len-R+1; j++){
				if (tvm[j] < menor){
					menor = tvm[j];
				}
			}
			//acha os valores para o nivelamento das pilha com o menor tvm
			for (int j = 0; j<len-R+1; j++){
				if (tvm[j] == menor){
					menor2 = 3000;
					res[aux] = 0;	
					for (int k = 0; k<R; k++){
						if (pilha[j+k] < menor2){
							menor2 = pilha[j+k];
						}
					}
					if ((float)(int)menor2 != menor2){
						menor2-=0.5;
					}
					for (int k = 0; k<R; k++){
						res[aux] += pilha[j+k] - menor2;
					}
					aux++;
					tvm[j] = 1000;
				}
			}
			menor = 1000;
			//acha o menor valor de nivelamento dentre os de menor tvm
			for(int j = 0; j<aux; j++){
				if (res[j] < menor){
					menor = res[j];
				}
			}
			cout<<"Case #"<<i+1<<": "<<menor<<endl;
		}
		else {
			cout<<"Case #"<<i+1<<": "<<menor<<endl;
		}
	}
	return 0;
}