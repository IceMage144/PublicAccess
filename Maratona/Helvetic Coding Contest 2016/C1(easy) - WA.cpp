#include <iostream>

using namespace std;

int main(){
	int noBrain, noCon;
	cin >> noBrain >> noCon;
	if (noBrain == noCon+1){
		cout << "yes" << endl;
	}
	else{
		cout << "no" << endl;
	}
	return 0;
}