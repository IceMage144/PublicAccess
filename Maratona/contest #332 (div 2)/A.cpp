#include <iostream>

using namespace std;

int main(){
	long long toS1, toS2, toHome, res[4], menor = 400000000;
	cin >> toS1 >> toS2 >> toHome;
	res[0] = 2*toS1+2*toS2;
	res[1] = toS1+toS2+toHome;
	res[2] = 2*toHome+2*toS2;
	res[3] = 2*toS1+2*toHome;
	for (int i = 0; i < 4; i++){
		if (res[i] < menor){
			menor = res[i];
		}
	}
	cout << menor << endl;
	return 0;
}