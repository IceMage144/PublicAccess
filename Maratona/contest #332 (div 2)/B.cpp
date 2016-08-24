#include <iostream>

using namespace std;

#define debug(args...) cout << args << endl;

int sbSeq[112345], newSeq[112345], res[112345];

int main(){
	int n, m, possible = 1;
	cin >> n >> m;
	for (int i = 0; i < n; i++){
		cin >> sbSeq[i];
	}
	for (int i = 0; i < m; i++){
		cin >> newSeq[i];
	}
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			if (newSeq[i] == sbSeq[j]){
				if (res[i] == 0 && possible == 1){
					res[i] = j+1;
				}
				else if (res[i] != j && possible == 1){
					possible = 0;
				}
			}
		}
		if (res[i] == 0 && possible == 1){
			possible = -1;
		}
	}
	if (possible == 1){
		cout << "Possible" << endl;
		for (int i = 0; i < m; i++){
			cout << res[i] << " \n"[i == m-1];
		}
	}
	else if (possible == 0){
		cout << "Ambiguity" << endl;
	}
	else {
		cout << "Impossible" << endl;
	}
	return 0;
}