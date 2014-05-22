#include<stdio.h>

#define SIZE 21
 
void qs(int *v, int a, int b){
   int p, aux, i = a, j = b, m;
   m = (int) ((i + j) / 2);
   p = v[m];
   while(j > i) {
      while (v[i] < p) i = i + 1;
      while (v[j] > p) j = j - 1;
      if(i <= j){
         aux = v[i];
         v[i] = v[j];
         v[j] = aux;
         i++;
         j--;
      }
   }
    
   if(a < j) qs(v, a, j);
   if(i < b) qs(v, i, b);   
 
}
 

int main(){
   int v[SIZE] = {10, 72, 55, 39, 7, 9, 4, 3, 6, 1, 18, 21, 10, 12, 13, 17 ,21 , 32, 33, 34, 35};
   int i = 0;   
   printf("Dirty:\n");
   for(i = 0; i < SIZE; i++){
      printf("%d ", v[i]);
   }
   printf("\n");   
   qs(v, 0, SIZE-1);
   printf("After QuickSort:\n");
   for(i = 0; i < SIZE; i++){
      printf("%d ", v[i]);
   }
   printf("\n");   
}