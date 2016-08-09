#include <iosteam>

using namespace std;

int mdc(int, int);

class fraction {
	int den, num;
	public:
		int create(int fir, int sec){
			num = fir;
			den = sec;
		}
		int sum(int fir, int sec){
			int gcd = mdc(sec, den);
			num = num*(den/gcd) + fir*(sec/gcd);
			den = gcd;
		}
		int subt(int fir, int sec){
			int gcd = mdc(sec, den);
			num = num*
		}
};