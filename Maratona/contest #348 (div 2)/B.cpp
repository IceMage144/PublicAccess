#include <cstdio>

using namespace std;

#define debug(args...) //printf(args)

char dir[112345];
int jmp[112345];

int main(){
	int noCell, gh = 0, noInstructions, temp;
	scanf("%d", &noCell);
	scanf("%s", dir);
	for(int i = 0; i < noCell; i++){
		scanf("%d", &jmp[i]);
	}
	while (gh >= 0 && gh < noCell && jmp[gh] != 0){
		if (dir[gh] == '>'){
			temp = gh;
			gh += jmp[gh];
			jmp[temp] = 0;
		}
		else {
			temp = gh;
			gh -= jmp[gh];
			jmp[temp] = 0;
		}
		debug("%d", gh);
	}
	if (gh >= 0 && gh < noCell)
		printf("INFINITE\n");
	else
		printf("FINITE\n");
	return 0;
}