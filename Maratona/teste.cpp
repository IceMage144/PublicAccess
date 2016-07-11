#include <iostream>

using namespace std;

int main(){
	int noBail, skills[112345];
	long long res = 0;
	cin >> noBail;
	for (int i = 0; i < noBail; i++){
		cin >> skills[i];
	}
	for (int i = 0; i < noBail; i++){
		for (int j = i+1; j < noBail; j++){
			if (skills[i] > skills[j]){
				res++;
			}
		}
	}
	cout << res << endl;
}