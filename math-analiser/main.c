#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct stack  {
  char value;
  struct stack *next;
} *sep;

int q = 0;

void init() {
   sep = (struct stack *) malloc(sizeof(struct stack));
   sep->next= NULL ;
}
void add(char v) {
  struct stack *new = (struct stack *) malloc(sizeof(struct stack));
  new->value = v;
  new->next = sep->next;
  sep->next = new;
  q++;
}
char delete()  {
 if (sep->next == NULL){
   return 0;
 }
 else {
   struct stack *new = (struct stack *) malloc(sizeof(struct stack));
   new = sep->next;
   sep = sep->next;
   q--;
   return new->value;
 }
}
int check(char c) {
char s;
  if ((c == '{')||(c == '[')||(c == '(')) {
    add(c);
  }
  else if ((c == '}')||(c == ']')||(c == ')')) {
    s = delete();
    if (((s == '(')&&(c==')'))||((s == '[' )&&(c==']'))||((s == '{')&&(c=='}'))){
      return 1;
    }
    else return 0;
  }
  return 1;
}

int main() {
  char buffer[512];
  int valid = 1;
  init();
  printf("\n Type some math stuff: ");
  scanf("%s",buffer);
  int i = 0;
  for( i = 0; i < strlen(buffer); i++) {
    valid = check(buffer[i]);
    if (valid == 0 ) break;
  }
  printf("%s\n", ((valid) && (q==0)) ? "Valid\n" : "Invalid\n" );

  return 1;
}
