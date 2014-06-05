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
  char user[50];
  char content[1000];

} process;


typedef struct sr {
   process p;
} sr;

process G_Process[MAX_PROCESS];
sr GSR[MAX_PROCESS];

int GSR_B = 0;
int GSR_E = 0;

int GP_Index = 0;

void srInsert(process p) {
  GSR[GSR_E++].p = p;
}

void srRemove(){
  GSR_B++;
}


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


      G_Process[j].line = j;
      strcpy( G_Process[j].user, _array[0] );
      j++;

    }
   };
   GP_Index = j;
   fclose(f);
}


void search(){
     int i,j = 0;
     char buffer[50];

     printf("Please type something to search:");
     scanf("%s",buffer);
     fflush(stdin);
     printf("\n ------------ Search Results:  -------------\n");

     for (i=0; i < GP_Index; i++){
        char *tp;
        tp = strstr(G_Process[i].user, buffer);
        if (tp) {
           srInsert(G_Process[i]);
           j++;
        }
     }
     if (j == 0)  printf("\nSorry, nothing found !");
}


int main () {
  loadFromFile();
  search();

  int i = GSR_B;
  for (i = GSR_B; i < GSR_E; i++){
    printf("%s\n",GSR[i].p.content);
    srRemove();
  }
  getch();
  return 0;
}
