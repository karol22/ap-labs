#include <stdio.h>

void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,y,x);
}

int main(){
    int i, j;
    for(i=0; i<50; i++){
        for(j=0; j<10; j++){
            if(i==0 || j==0 || i==49 || j==49){
                gotoxy(i, j);
                printf("X");
            }
        }
    }
}