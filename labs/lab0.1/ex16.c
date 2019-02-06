#include <stdio.h>
#define MAXLINE 3

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
        int plus=len;
        while(line[plus-1]!='\n' || len<2){
            plus=getLine(line, MAXLINE);
            len+=plus;
            //printf("%d %d %d\n", line[0], line[plus-1], line[plus] );
        }
        if(len>max){
            max=len;
        }    } 
    if(max>0){
            printf("The longest line has a size of : %d\n", max);
    }
    return 0;
}