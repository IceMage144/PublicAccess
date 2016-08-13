#include <iostream>
#include <cmath>

using namespace std;

int V[112345];

double khinNum(double num, int prec){
	V[prec] = (int)floor(num);
	if (prec == 0){
		return 1.0;
	}
	else {
		return khinNum(1/(num-floor(num)), prec-1);
	}
}

double harmMeanSum(double mean, double newFac, double qnt, double power){
	return pow((pow(mean, power)*qnt+pow(newFac, power))/(qnt+1), 1/power);
}

int main(){
	double num, res = 1.0;
	int prec, power;
	cout << "Índice da constante:" << endl;
	cin >> power;
	cout << "Número a ser avaliado:" << endl;
	cin >> num;
	cout << "Precisão (número de 1 a 100000):" << endl;
	cin >> prec;
	khinNum(num, prec);
	if (power == 0){
		for (double i = 0.0; i <= prec; i++){
			res = pow(res, i/(i+1.0))*pow((double)V[(int)i], 1.0/(i+1));
		}
	}
	else if (power < 0){
		for (double i = 0.0; i <= prec; i++){
			res = harmMeanSum(res, (double)V[(int)i], i, power);
		}
	}
	cout << res << endl;
	return 0;
}