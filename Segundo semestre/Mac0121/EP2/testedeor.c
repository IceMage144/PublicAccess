#include <stdio.h>

int func1(){
	printf("1\n");
	return 1;
}

int func2(){
	printf("2\n");
	return 1;
}

int main() {
	int x = 2, y = 0;
	if((func1() || func2()) && 1)
		printf("or\n");
	return 0;
}