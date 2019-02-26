
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char auxi[10];

struct element{
char word[50];
char lines[2000];
int counter;
struct element* next;
};

struct element *new_foo(char *s){
struct element *obj = ( struct element*)malloc(sizeof(struct element)) ;
strcpy(obj->word, s);
strcpy(obj->lines, "Lines: ");
obj->counter = 0;
return obj;
}

void insert(struct element* obj, char* newword, int numberline){
//printf("El primer elemento es %s\n", obj ->word);
if(strlen(newword) < 2){
//printf("CASO RARO\n");
return;
}
struct element* aux = obj;
//printf("insertado %s\n", newword);
while(aux -> next != NULL){
if(strcmp(newword, aux->word)==0){
//printf("AQUI :%s: %d\n", newword, numberline);
aux->counter = aux->counter+1;
sprintf(auxi, "%d ", numberline);
strcat(aux ->lines, auxi);
return;
}
aux = aux -> next;
}
if(strcmp(newword, aux->word)==0){
//printf("ALLA :%s:, %d\n", newword, numberline);
aux->counter = aux->counter+1;
sprintf(auxi, "%d ", numberline);
strcat(aux ->lines, auxi);
return;
}
//printf("final :%s: %d\n", newword, numberline);
aux->next = new_foo(newword);
aux = aux -> next;
aux->counter = 1;
sprintf(auxi, "%d ", numberline);
strcat(aux ->lines, auxi);
return;
}

void print(struct element* obj){
if(strlen(obj -> word) > 0){
printf(":%s: %d times\n ", obj -> word, obj ->counter);
printf("%s\n\n", obj -> lines);
}
if(obj -> next !=NULL) print(obj -> next);
}


int main(int argc, char **argv){
char ll[2];
char word[50];
ll[1] = 0;
char ch;
int numpage = 1;

struct element* list = new_foo("");
FILE *fp;
fp = fopen(argv[1], "r"); // read mode
while((ch = fgetc(fp)) != EOF){
if ((ch <='Z' && ch >= 'A') || (ch <='z' && ch >= 'a')){
ll[0] = ch;
strcat(word, ll);
} else {
//printf("%s\n", word);
if(strlen(word) > 3){
insert(list, word, numpage);
}
if(ch == '\n'){
numpage++;
}
strcpy(word, "");
}
}
fclose(fp);
print(list);
}
