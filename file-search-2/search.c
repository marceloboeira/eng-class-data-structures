#include <stdio.h>
#include <string.h>
 
#define FILE_NAME "data.txt"
#define MAX_CHARS 10000
 
 
FILE *getFile(int write) {
   return (write == 1) ? fopen(FILE_NAME,"w") : fopen(FILE_NAME,"r");
}
 
char *loadFile () {
  FILE *f = getFile(0);
  char *final,_lineBuffer[500];
  int j = 0;
  final = malloc(MAX_CHARS * sizeof(char));
  while (fgets(_lineBuffer, 500, f)!= NULL){
    strcat (final, _lineBuffer);
  }
  fclose(f);
  return final;
}
 
int main(){
  char *bf,*sc, *fc = loadFile();
  
  printf("The File Contents: \n%s\n",fc);
  bf = malloc(100 * sizeof (char) );
  printf("\nType something:");
  scanf("%s",bf);
  
  sc = strstr(fc, bf);
  if (sc) {
    printf("\n\"%s\" was found in the file!\n",bf);
  }
  else {
    printf("\n\"%s\" was NOT found in the file!\n",bf);
  }
  
  
 
}