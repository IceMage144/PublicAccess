#include <iostream>
#include <map>

using namespace std;

int main(){
	long long noCards, noRes, cards[1123456], res = 0, aux;
	cin >> noCards >> noRes;
	map<long long, long long> ordem;
	for (int i = 0; i < noCards; i++){
		cin >> cards[i];
		ordem[cards[i]] = i;
	}
	for (int i = 0; i < noRes; i++){
		cin >> aux;
		if (aux == 1){
			res += noCards;
			cards[ordem[1]] = -1;
		}
		for (int i = 0)
	}
	return 0;
}