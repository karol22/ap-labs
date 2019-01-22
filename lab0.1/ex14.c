#include <stdio.h>
#define MAX_LENGTH 127
int main()
{
    printf("    Welcome to the frecuencies counter\n");
    printf("    Only counts letters, numbers and punctuation marks.\n    Enter your lines one by one. Press Enter before Ctrl + D to end\n\n");
    int chars[MAX_LENGTH];
    int i;
    for(i=0; i<MAX_LENGTH; i++){
        chars[i]=0;
    }
    int c;
    while((c=getchar()) != EOF){
        if(c<MAX_LENGTH)
            chars[c]++;
    }
    printf("    The frecuencies are the following\n\n");
    for(i=33; i<126; i++){
        printf("    %3c: %3d ", i, chars[i]);
        int j;
        for(j=0; j<chars[i]; j++){
            printf("*");
        }
        printf("\n");
    }
}