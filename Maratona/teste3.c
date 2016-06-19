#include <stdio.h>
#include <string.h>

long long res[501];

int main(){
   int n;
   scanf("%d", &n);
   for (int i = 0; i<n; i++){
      char S[501];
      scanf("%s", S);
      int size = strlen(S);
      for (int j = 0; j<size; j++){
         if (S[j] == '<' && j < size-1){
            int next = j+1;
            while(S[next] != '>' && next < size){
               next++;
            }
            if (S[next] == '>'){
               res[i] += 2;
            }
         }
      }
   }
   for (int i = 0; i<n; i++){
      printf("%lld\n", res[i]);
   }

}