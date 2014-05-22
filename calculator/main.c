#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
 
char operators[4] = {'+','-','*','/'};
 
int main(int argc, char *argv[]) {
 
   float _stack = 0;
   char _operation = ' ';
   int _operationPosition = -1;
   while(1){
                   
     char temp[30];
     system("cls");
      printf("\nStack: %f", _stack );     
     printf("\nOperation: %c \
             \nPosition: %d", _operation, _operationPosition);
     
     printf("\nString Input > %s \n\n\n\n", temp);
     
     printf("\n>");
     scanf("%s",temp);
     
     int i =0;
     
     /* Reset Operator */
     
     _operation = ' ';
     for (i = 0; i < (strlen(temp)); i++) {
        int j = 0;
        printf("\n Temp: %i ", i);
        bool _already = false;
        while (!_already && (j < 4)){
              if (temp[i] == operators[j]){
                 _already = true;
                 _operation = operators[j];
                 _operationPosition = j;
                 
                 printf("\n True_: %i ", j);
              }
              printf("\n Loop: %i ", j);
               j++;
        }
     } 
     
     if ((_operation == ' ') || (_operationPosition < 0)) {
    
        _stack = atof(temp);
     }
     else {
          float opA,opB;
          char opp[30];
          
          for (i = 0; i < _operationPosition; i++) {
              strcat(opp,temp[i]);
              printf("\n\n -> %s",temp[i]);
          }
          _stack = atof(opp);
         // printf("TESTE > %s",opp);
         // system("pause");
     }
   } 
  system("PAUSE");   
  return 0;
}