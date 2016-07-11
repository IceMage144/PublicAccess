#include <iostream>

using namespace std;

int main(){
	char sleepC[7], clockC[7];
	int sleep[2], clock[2], res[2];
	cin >> clockC >> sleepC;
	sleep[0] = (int)(sleepC[0])*10+(int)(sleepC[1]);
	sleep[1] = (int)(sleepC[3])*10+(int)(sleepC[4]);
	clock[0] = (int)(clockC[0])*10+(int)(clockC[1]);
	clock[1] = (int)(clockC[3])*10+(int)(clockC[4]);
	res[0] = (clock[0]-sleep[0])%24;
	res[1] = (clock[1]-sleep[1])%60;
	if (res[1] < 0){
		res[1] += 60;
		res[0]--;
	}
	if (res[0] < 0){
		res[0] += 24;
	}
	if (res[0] < 10){
		cout << "0" << res[0] << ":";
	}
	else{
		cout << res[0] << ":";
	}
	if (res[1] < 10){
		cout << "0" << res[1] << endl;
	}
	else{
		cout << res[1] << endl;
	}
	return 0;
} 