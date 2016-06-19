#include <stdio.h>
#include <math.h>

int main(){
	int n;
	scanf("%d", &n);
	int Y;
	int Cases[1123];
	int T = 1;
	while (n!=0){
		for (int i = 0; i<n; i+=1){
			scanf("%d", &Y);
			if (Y != 0){
				Cases[T] += 1;
			}
			else{
				Cases[T] -= 1;
			}
		}
		scanf("%d", &n);
		T += 1;
	}
	for (int i = 1; i<T; i+=1){
		printf("Case %d: %d\n", i, Cases[i]);
	}
}