#include <stdio.h>
#define IN 0
#define OUT 1
#define MAX_LENGTH 21 //all words with length at most 20
int main()
{
    printf("    Welcome to the frecuencies counter\n    Enter your lines one by one. The limit for the size of the word is 20. Press Enter before Ctrl + D to end\n\n");
    int c;
    int spaces=1;
    int words[MAX_LENGTH];
    int i;
    for(i=0; i<MAX_LENGTH; i++){
        words[i]=0;
    }
    int count=0;
    int morethanlimit=0;
    while((c=getchar()) != EOF){
        if(c==' '||c=='\n'||c=='\t'){
            if(spaces==IN){
                //putchar('\n');
                spaces=OUT;
                if(count<MAX_LENGTH)
                    words[count]++;
                count=0;
            }
        } else {
            //putchar(c);
            spaces=IN;
            count++;
        }
    }
    printf("    The frecuencies are the following\n\n");
    for(i=1; i<MAX_LENGTH; i++){
        printf("    %3d: %3d ", i, words[i]);
        int j;
        for(j=0; j<words[i]; j++){
            printf("*");
        }
        printf("\n");
    }
}