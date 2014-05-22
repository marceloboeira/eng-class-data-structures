#include<stdio.h>
#include<string.h>
 
#define FILE_NAME "data.txt"
#define MAX_CHARS 100
 
 
FILE *getFile(int write) {
  return (write == 1) ? fopen(FILE_NAME,"a+") : fopen(FILE_NAME,"r+");
}
 
void writeFile(char *b) {
  FILE *f = getFile(1);
  fputs(b,f);
  fclose(f);
}
 
int main(){
  char *buffer;
  buffer = malloc(MAX_CHARS * sizeof (char) );
  
  printf("Write the file contents:");
  scanf("\n%s",buffer);
 
  writeFile(buffer);
  printf("\nThanks!\n");
 
 
} 