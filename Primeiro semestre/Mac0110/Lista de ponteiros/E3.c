#include <stdio.h>

int main(){
	double x = 1.0/3.0;
	double y = 1.0/5.0;
	double *pd;
	pd = &y;
	printf("%f\n%p\n%p\n", *pd, pd, &pd);
	*pd = *pd * x;
	printf("%f\n%p\n%p\n%f\n%f\n", *pd, pd, &pd, x, y);
	return 0;
}