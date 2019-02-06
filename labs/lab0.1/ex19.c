#include <stdio.h>
#define MAXLINE 1000

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
void reverse(char to[], int size, char from[]){
    int i;
    i=0;
    while(i<size-1){
        //printf("%d\n", from[size-2]);
        to[i]=from[size-i-2];
        i++;
    }
}

int main(){
    int len;
    int max;
    char line[MAXLINE];
    char reversed[MAXLINE];
    max=0;
    while((len=getLine(line, MAXLINE)) > 0){ 
        //printf("%d\n", line[len-1]);
        reverse(reversed, len, line);
        printf("%s\n", reversed);
    } 
    return 0;
}