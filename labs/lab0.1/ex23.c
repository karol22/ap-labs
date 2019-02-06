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

int main(){
    int len;
    int max;
    char line[MAXLINE];
    printf("Enter your code, press Ctrl+D to exit:\n");
    int inside=0;
    int last1=0;
    int last2=0;
    while((len=getLine(line, MAXLINE)) > 0){ 
        for(int i=0; i<len; i++){
            if(inside!=1){
                if(line[i]=='*'){
                    if(last1 ==1){
                        inside=1;
                        last1=0;
                    }else {
                       printf("*");
                    }
                }else if(line[i]=='/'){
                    last1=1;
                }else{
                    if(last1==1){
                        printf("/");
                    }
                    last1=0;
                    printf("%c", line[i]);
                }
            } else{
                if(line[i]=='*'){
                    last2=1;
                } else if(line[i]=='/'){
                    if(last2==1){
                        last2=0;
                        inside=0;
                    }
                }else{
                    last2=0;
                }
            }
        }
    } 
    return 0;
}