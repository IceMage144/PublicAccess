#include <stdio.h>
#include <stdlib.h>

void shiftRight(int **mat, int lin){

}

int main(){
	int lin, col;
	scanf("%d%d", lin, col);
	int **matrix = (int**)calloc(lin * sizeof(*int));
	if (matrix == NULL){
		free(matrix);
		exit(1);
	}
	for (int i = 0; i < col; i++){
		matrix[i] = (int*)calloc(col * sizeof(int));
		if (matrix[i] == NULL){
			for (int j = 0; j < i; j++){
				free(matrix[j]);
			}
			free(matrix);
			exit(1);
		}
	}
	
	return 0;
}