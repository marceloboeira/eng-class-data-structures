#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#ifdef __unix__
    #define OS_Windows 0
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)     
    #define OS_Windows 1
    #include <windows.h>
    #include <tchar.h>
    #define DIV 1048576
    #define WIDTH 7
#endif
 
#define DEBUG_MOD 0
#define FILE_NAME "terminal.data"
#define MAX_PROCESS 500
#define MAX_STRING_SIZE 500
 
#define LINE_DELIMITER " "
#define LINE_BREAKER "\n"
 
 
typedef struct process {
  int line;
  int pid;
  char user[50];
  char content[1000];
  
} process;
 
process G_Process[MAX_PROCESS];

int G_Index = 0;

char *G_Message; 

 
#ifdef __unix__
void getch(){
  system("read a");
}
#endif
 
  
/** File Procedures */  
FILE *getFile(int write) {
  return (write == 1) ? fopen(FILE_NAME,"w") 
                      : fopen(FILE_NAME,"r");
}
 
void loadFromFile () { 
  FILE *f = getFile(0);
  char _lineBuffer[1000];
  int j = 1;
  fgets(_lineBuffer, 1000, f);
  while (fgets(_lineBuffer, 1000, f) != NULL){ 
    char *dirty = _lineBuffer;
    int i = 0;
    char *_buffer;
    
    if (strlen(_lineBuffer) > 10) {
      int size = 30;
      char *_array[size];
      strcpy(G_Process[j].content,_lineBuffer) ;
      _buffer = strtok (dirty,LINE_DELIMITER);  
      while (_buffer != NULL){
        _array[i++] = _buffer;
        _buffer = strtok (NULL, LINE_DELIMITER);
      }
      fflush(f); 
      G_Process[j].line = j;
      G_Process[j].pid = atoi(_array[1]) ;
      strcpy( G_Process[j].user, _array[0] ); 
      j++;                         
    }
   };
   G_Index = j;
   fclose(f);
}
 
 
void search(){
     int i,k,j = 0;
     char buffer[50];     
     
     printf("Please type something to search:");
     scanf("%s",&buffer);
     fflush(stdin);
     printf("\n ------------ Search Results:  -------------\n");
     
     for (i=0; i < G_Index; i++){    
         k = 0;
         char *tp;
         tp = strstr(G_Process[i].user, buffer);
         if (tp) {
	   printf("%s",G_Process[i].content);
	   j++;
	 }
     }
     (j == 0) ? printf("\nSorry, nothing found !") : getch(); 
}
 
  
int main () {
    int i = 0;
    loadFromFile();
    search();
    return 0;
}