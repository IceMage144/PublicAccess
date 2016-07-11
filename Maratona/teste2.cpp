#include <iostream>
#include <cmath>

using namespace std;

double sum(double i, double n){
  if (i != n){
    cout << log(i) << endl;
    return log(i)+sum(i+1.0,n);
  }
  else{
    return log(n);
  }
}

int main(){
  double n;
  cin >> n;
  double res = sum(1.0,2.0*n)-2.0*sum(1.0,n);
  cout << round(res) << endl;
  return 0;
}