#include <stdio.h>
#define MAXLINE 1000
#define TABS 7
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

int main(){
    int len;
    int i, j;
    char line[MAXLINE];
    int spaces=0;
    while((len=getLine(line, MAXLINE)) > 0){ 
        for(i=0; i<len; i++){
            if(line[i]==' '){
                spaces++;
                if(spaces==TABS){
                    printf("\t");
                    spaces=0;
                }
            }else{
                for(j=0; j<spaces; j++){
                    printf(" ");
                }
                spaces=0;
                printf("%c", line[i]);
            }
        }
    } 
    return 0;
}
