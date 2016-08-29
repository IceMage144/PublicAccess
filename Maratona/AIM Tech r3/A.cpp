#include <iostream>

using namespace std;

int main(){
	int noOran, maxOran, wasteSize, orange, res = 0, juicer = 0;
	cin >> noOran >> maxOran >> wasteSize;
	for (int i = 0; i < noOran; i++){
		cin >> orange;
		if (orange <= maxOran){
			juicer+=orange;
			if (juicer > wasteSize){
				res++;
				juicer = 0;
			}
		}
	}
	cout << res << endl;
	return 0;
}