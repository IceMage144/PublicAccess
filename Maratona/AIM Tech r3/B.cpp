#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
#define MAXN 1123456

int checkp[112345];

int main(){
	int noCP, start, left, right, mid, res = 0, mid2 = 0;
	cin >> noCP >> start;
	for (int i = 0; i < noCP; i++){
		cin >> checkp[i];
	}
	left = 0;
	right = noCP-1;
	sort(checkp, checkp+noCP);
	mid = (noCP-1)/2;
	while (left != right-1){
		if (start < checkp[mid]){
			right = mid;
			mid = (right+left)/2;
		}
		else {
			left = mid;
			mid = (right+left)/2;
		}
	}
	mid2 = mid;
	if (checkp[mid] > start){
		mid--;
	}
	if (checkp[mid2] < start){
		mid2++;
	}
	for (int i = 0; i < noCP-1; i++){
		while (mid2 < noCP-1 && checkp[mid2] == MAXN){
			mid2++;
		}
		while (mid > 0 && checkp[mid] == MAXN){
			mid--;
		}
		if (abs(checkp[mid]-start) < abs(checkp[mid2]-start)){
			res += abs(checkp[mid]-start);
			start = checkp[mid];
			checkp[mid] = MAXN;
		}
		else if (checkp[mid2] != MAXN){
			res += abs(checkp[mid2]-start);
			start = checkp[mid2];
			checkp[mid2] = MAXN;
		}
	}
	cout << res << endl;
	return 0;
}