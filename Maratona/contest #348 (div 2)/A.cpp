#include <cstdio>

using namespace std;

int main(){
	int noStones, res = 0, flip = 0;
	scanf("%d", &noStones);
	while (noStones >= flip+1){
		noStones -= flip+1;
		flip = !flip;
		res++;
	}
	printf("%d\n", res);
	return 0;
}