#include <stdio.h>

#define MAXLINE 1000
#define N 10
#define LINE_WIDTH 10

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
void copy2(char to[], char from[], int t){
    int i;
    i=0;
    while((to[i]=from[i+t]) != '\0')
    ++i;
}

int main(){
    char line[MAXLINE];
    char aux[MAXLINE];
    int len;
    printf("Input the lines, press Ctrl + D to exit:\n");
    while((len=getLine(line, MAXLINE)) > 0){
        int l=len;
        int i, j;
        while(l>1){
            for(i=0; i<N && line[i]!=' ' && line[i]!='\n' && line[i]!='\t'; i++);
            //printf("%d", i);
            for(j=0; j<i; j++){
                printf("%c", line[j]);
            }
            if(i==N)
            printf("%%");
            printf("\n");
        
            while(line[i]==' ' || line[i]=='\n' || line[i]=='\t') i++;
            copy2(aux, line, i);
            copy(line, aux);
            l-=i;
        }

    }  
}
