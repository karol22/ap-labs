#include <stdio.h>
#define MAXLINE 1000
#define MIN_SIZE 80

int getLine(char s[], int lim){
    int c, i;
    for(i=0; i<lim-1&&(c=getchar())!=EOF&&c!='\n'; ++i){
        s[i]=c;
    }
    if(c=='\n'){
         s[i]=c;
         i++;  
    }
    s[i]='\0';
    return i;
}
void copy(char to[], char from[]){
    int i;
    i=0;
    while((to[i]=from[i]) != '\0')
    ++i;
}

int main(){
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];
    max=0;
    while((len=getLine(line, MAXLINE)) > 0){ 
        if(len>MIN_SIZE){
            printf("%s", line);
        }
    } 
    return 0;
}