#include <stdio.h>

int buses[1123];
int trolleys[11234];

int main(){
	int one, allOne, allKind, all, noBus, noTroll, i;
	int sumBus = 0, sumTroll = 0, res = 0, count = 0, sum = 0;
	scanf("%d%d%d%d%d%d", &one, &allOne, &allKind, &all, &noBus, &noTroll);
	for (i = 0; i < noBus; i++){
		scanf("%d", &buses[i]);
		sumBus += buses[i];
	}
	for (i = 0; i < noTroll; i++){
		scanf("%d", &trolleys[i]);
		sumTroll += trolleys[i];
	}
	if (all < 2*allKind){
		if (all < allOne*(noBus+noTroll)){
			if (all < one*(sumBus+sumTroll)){
				res += all;
			}
			else {
				res += one*(sumBus+sumTroll);
			}
		}
		else {
			if (noBus*allOne < sumBus*one){
				res += noBus*allOne
			}
			else {
				count = 0;
				while (one*sum < allOne*count){
					
				}
			}
			if (noTroll*allOne < sumTroll*one){
				res += noTroll*allOne
			}
			else {

			}
		}
	}
	else {
		if (allKind < allOne*noBus){
			if (allKind < one*sumBus){
				res += allkind;
			}
			else {

			}
		}
		else {
			//bin search
		}
		if (allKind < allOne*noTroll){
			if (allKind < one*sumTroll){
				res += allKind;
			}
			else {

			}
		}
		else {

		}
	}
	return 0;
}