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

int main(){
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];
    max=0;
    while((len=getLine(line, MAXLINE)) > 0){ 
        int j=len-2;
        while(line[j]==' '|| line[j]=='\t'){
            //line[j]='\n';
            line[j]='\0';
            j--;
        }
        line[j+1]='\0';
        printf("%s.\n", line);
    } 
    return 0;
}