#include <stdio.h>

int main(){
	double x = 1.0/3.0;
	double y = 1.0/5.0;
	double *pd;
	pd = &x;
	printf("%f\n%f\n%f\n%p\n%p\n", x, y, *pd, pd, &pd);
	return 0;
}