#include <iostream>

using namespace std;

int main(){
	int side, maiX = 0, maiY = 0, menX = 60, menY = 60, res = 0;
	cin >> side;
	char grid[side][side];
	for (int i = 0; i < side; i++){
		cin >> grid[i];
	}
	for (int i = 0; i < side; i++){
		for (int j = 0; j < side; j++){
			if (grid[i][j] == '1'){
				if (i > maiY){
					maiY = i;
				}
				if (i < menY){
					menY = i;
				}
				if (j > maiX){
					maiX = j;
				}
				if (j < menX){
					menX = j;
				}
			}
		}
	}
	for (int i = 0; i < side; i++){
		if (grid[i][maiX] == '1'){
			res++;
		}
		if (grid[i][menX] == '1'){
			res++;
		}
		if (grid[maiY][i] == '1'){
			res++;
		}
		if (grid[menY][i] == '1'){
			res++;
		}
	}
	if (res == 8){
		cout << "Yes" << endl;
	}
	else{
		cout << "No" << endl;
	}
	return 0;
}