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
#define MOVIES_FILE_NAME "movies.db"
#define MOVIES_MAX 500
#define MOVIES_MAX_STRING_SIZE 100
#define MAX_FIELDS 5
 
#define S_NAME "Movies Core v 0.1 Alpha"
#define S_DEV_NAME "Marcelo Boeira - MarceloBoeira.com"
 
#define LINE_DELIMITER "|"
#define LINE_BREAKER "\n"
 
 
 
 
typedef union date {
  int day ;
  int month ;
  int year ;
} date;
 
typedef struct movie {
  int id;
  char name[MOVIES_MAX_STRING_SIZE];
  int minAge;
  char kind[MOVIES_MAX_STRING_SIZE];
  char mainActor[MOVIES_MAX_STRING_SIZE];
 
  date released;
} movie;
 
typedef struct user {
  char name[100];
  int age;
} user;
 
/** Global Databases */ 
movie G_Movies[MOVIES_MAX];
int G_MoviesIndex = 0;
user G_User;
char *G_Message; 
 
/* Core Procedures */ 
int isWindows(){
    return OS_Windows;  
}
 
#ifdef __unix__
void getch(){
  system("read a");
}
#endif
 
int isDebugging(){
  return DEBUG_MOD;
}
 
char *getMessage(){
  return G_Message;
}
void setMessage(char m[]){
  G_Message = m;
}
 
/** Screen Procedures **/
void screenHeader() {
     printf("_______________________________________ \n");
     printf("------ ");
     printf(S_NAME);
     printf(" ------ \n");
     printf("_______________________________________ \n\n");
}
 
void screenClear(){
  (isWindows()) ? system("cls") : system("clear");
 
}
 
/** File Procedures */  
FILE *getFile(int write) {
  return (write == 1) ? fopen(MOVIES_FILE_NAME,"w") 
                      : fopen(MOVIES_FILE_NAME,"r");
}
 
void loadMoviesFromFile () { 
  FILE *f = getFile(0);
  char _lineBuffer[500];
  int j = 0;
  while (fgets(_lineBuffer, 500, f)!= NULL){ 
    char *dirty = _lineBuffer;
    int i = 0;
    char *_buffer;
    
    if (strlen(_lineBuffer) > 10) {
      _buffer = strtok (dirty,LINE_DELIMITER);  
      int size = MAX_FIELDS;
      char *_array[size];
      while (_buffer != NULL){
        _array[i++] = _buffer;
        _buffer = strtok (NULL, LINE_DELIMITER);
      }
      /** Importing fields from File to MOVIES Union*/
      G_Movies[j].id = atoi(_array[0]);
      strcpy( G_Movies[j].name, _array[1] );
      G_Movies[j].released.year = atoi(_array[2]);
      G_Movies[j].minAge = atoi(_array[3]);
      strcpy( G_Movies[j].kind, _array[4] );
      strcpy( G_Movies[j].mainActor, _array[5] );    
      j++;                         
    }
   };
   G_MoviesIndex = j;
   fclose(f);
}
 
void saveMoviesOnFile() {
      FILE *f = getFile(1);
      int i;
      for (i=0; i < G_MoviesIndex; i++){
          fprintf(f,
                 "%i|%s|%i|%i|%s|%s",             
                  G_Movies[i].id, 
                  G_Movies[i].name, 
                  G_Movies[i].released.year, 
                  G_Movies[i].minAge, 
                  G_Movies[i].kind, 
                  G_Movies[i].mainActor);
          fprintf(f,LINE_BREAKER);
      }  
      fclose(f);
}
 
void searchMovies(int mod){
     int i,k,j = 0;
     char buffer[50];     
 
     screenClear();
     screenHeader();
     if (mod != 0) {
        printf("Please type something to search:");
        scanf("%s",&buffer);
        fflush(stdin);
     }
     screenClear();
     screenHeader();
     printf("\n Search Results: \n");
     
     for (i=0; i < G_MoviesIndex; i++){
         if (mod == 0){
            k = 1;
         } 
         else {
              k = 0;
              char *tp;
              if (mod == 1) tp = strstr(G_Movies[i].name, buffer);
              else if (mod == 2) tp = strstr(G_Movies[i].kind, buffer);
              else if (mod == 3) tp = strstr(G_Movies[i].mainActor, buffer);
              if (tp) k = 1;
         }
          
         if (k && (G_User.age >= G_Movies[i].minAge)) {
            j++;
            printf("-----------\nID: %i\nName: %s\nReleased Year: %i\nMinimum Age: %i\nKind: %s\nMain Actor:%s\n", 
                   G_Movies[i].id, 
                   G_Movies[i].name, 
                   G_Movies[i].released.year, 
                   G_Movies[i].minAge, 
                   G_Movies[i].kind, 
                   G_Movies[i].mainActor);
         }
     }
     (j == 0) ? setMessage("Sorry, nothing found !") : getch();
}
 
void newMovie(){
     movie tM;
     tM.id = G_MoviesIndex ;
     screenClear();  
     screenHeader();    
     printf("\nType a name Name:");
     scanf("%s",&tM.name);
     fflush(stdin);
     printf("\nType the Minimum Age:");
     scanf("%i",&tM.minAge);
     fflush(stdin);
     printf("\nType the Release Year:");
     scanf("%i",&tM.released.year);
     fflush(stdin);
     printf("\nType the kind:");
     scanf("%s",&tM.kind);
     fflush(stdin);
     printf("\nType the Main Actor:");
     scanf("%s",tM.mainActor);
     fflush(stdin);
     G_Movies[tM.id] = tM;
     G_MoviesIndex++;
     saveMoviesOnFile();
     setMessage("Movie added to the database!");
}
 
void setupUser(){
     char *buffer;
     screenClear();  
     screenHeader();    
     printf("Type your name:");
     scanf("%s",&G_User.name);
     printf("Type your age:");
     scanf("%i",&G_User.age);
     fflush(stdin);
     setbuf(stdin, NULL);
 
}  
   
int main () {
    int _opt = 0;
    int _exit = 0;
    setMessage(" ");
    loadMoviesFromFile();
    setupUser();
 
    while(!_exit) {
       screenClear();
       screenHeader();
              
       printf("\nWelcome %s, - %s \n                        (%i Movies on Database)", G_User.name, getMessage(), G_MoviesIndex);
       printf("\nMenu:\n1) List Movies\n2) New Movie\n3) Search Movies by name\n4) Search Movies by kind\n5) Search Movies by main actor\n9) Exit\n\n Type you option:");
       
       setMessage(" ");
       scanf("%d", &_opt);
       fflush(stdin);
       switch (_opt) { 
              case 1: searchMovies(0); break;
              case 2: newMovie(); break;
              case 3: searchMovies(1); break;
              case 4: searchMovies(2); break;                                      
              case 5: searchMovies(3); break;                                                         
              case 9: exit(0); break;                   
              default: setMessage("Invalid Option!"); break;                   
       }
    }
    return 0;
}