#include <iostream>

using namespace std;

int main(){
	int n, blocks = 1, maxBlocks = 1, maior = 0;
	long long castles[112345];
	cin >> n;
	cin >> castles[0];
	for (int i = 1; i < n; i++){
		cin >> castles[i];
		if (castles[i-1] < castles[i]){
			blocks++;
		}
	}
	cout << blocks << endl;
	return 0;
}