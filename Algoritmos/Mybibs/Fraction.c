#include <stdio.h>

int mmc (int n, int s);

class fraction{
	public:
		int den, num;
		fraction (int a, int b) : den(a), num(b) {
			if (b < 0){
				a = -a;
				b = -b;
			}
		}
		fraction operator + (const fraction&);
		fraction operator - (const fraction&);
};

fraction fraction::operator + (const fraction& param){
	fraction temp, mini;
	mini = mmc(param.den, den);
	temp.den = mini;
	temp.num = param.num*param.den/mini + num*den/mini;
	return temp;
}

fraction fraction::operator - (const fraction& param){
	fraction temp, mini;
	mini = mmc(param.den, den);
	temp.den = mini;
	temp.num = num*den/mini - param.num*param.den/mini;
	return temp;
}

int mdc (int n, int s) {

}

int mmc(int n, int s) {
	int ret, gcd;
	gcd = mdc(n, s);
	ret = (n/gcd) * (s/gcd) * gcd;
	return ret;
}

int *create(int num, int den){
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