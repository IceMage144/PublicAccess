#include <cstdio>
#define debug(args...) //printf(args)


int main(){
	int noBoys, noMoves, move, shift, aux, count = 0, troca = 0; 
	scanf("%d%d", &noBoys, &noMoves);
	int roda[noBoys];
	int roda2[noBoys];
	for (int i = 0; i < noBoys; i++){
		roda[i] = i+1;
		roda2[i] = i+1;
	}
	for (int i = 0; i < noMoves; i++) {
		scanf("%d", &move);
		if (move == 1){
			debug("c = %d t = %d\n", count, troca);
			scanf("%d", &shift);
			count += shift;
			if(troca) {
				for (int j = 0; j < noBoys; j+=2){
					aux = roda[j];
					roda[j] = roda[j+1];
					roda[j+1] = aux;
					troca = 0;
				}
			}
		}
		else if (move == 2){
			debug("c = %d t = %d\n f = %d\n", count, troca, roda[0]);
			troca = !troca;
			if(count != 0) {
				shift = count;
				for (int j = 0; j < noBoys; j++){
					while (shift < 0){
						shift = noBoys + shift;	
					}
					aux = (j+shift)%noBoys;
					roda2[aux] = roda[j];
				}
				for (int j = 0; j < noBoys; j++){
					roda[j] = roda2[j];
				}
				count = 0;
			}
		}
	}
	debug("c = %d t = %d\n", count, troca);
	if(count != 0) {
		shift = count;
		for (int j = 0; j < noBoys; j++){
			while (shift < 0){
				shift = noBoys + shift;	
			}
			aux = (j+shift)%noBoys;
			roda2[aux] = roda[j];
		}
		for (int j = 0; j < noBoys; j++){
			roda[j] = roda2[j];
		}
		count = 0;
	}
	if(troca) {
		for (int j = 0; j < noBoys; j+=2){
			aux = roda[j];
			roda[j] = roda[j+1];
			roda[j+1] = aux;
			troca = 0;
		}
	}
	debug("c = %d t = %d\n", count, troca);
	for (int i = 0; i < noBoys; i++){
		printf("%d%c", roda[i], " \n"[i == noBoys-1]);
	}
	return 0;
}