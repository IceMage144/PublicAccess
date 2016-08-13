#include <iosteam>

using namespace std;

typedef struct {
	int den, num;
} fraction;

int mdc(int n, int s) {

}

int* create(int num, int den){
	fraction ret;
	ret.num = num;
	ret.den = den;
	return &ret;
}

int sum(fraction fir, fraction sec){
	int gcd = mdc(sec, den);
	num = num*(den/gcd) + fir*(sec/gcd);
	den = gcd;
}

int subt(int fir, int sec){
	int gcd = mdc(sec, den);
	num = num*(den/gdc) - fir
}