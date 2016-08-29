#include <iostream>
#include <string>

using namespace std;

int main(){
	string word;
	int lower = 0;
	cin >> word;
	while (word[lower] == 'a'){
		lower++;
	}
	while (word[lower] != '\0' && word[lower] != 'a'){
		word[lower]--;
		lower++;
	}
	cout << word << endl;
	return 0;
}