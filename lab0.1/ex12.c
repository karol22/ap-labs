#include <stdio.h>
#define IN 0
#define OUT 1
int main()
{
    int c;
    int spaces=1;
    while((c=getchar()) != EOF){
        if(c==' '||c=='\n'||c=='\t'){
            if(spaces==IN){
                putchar('\n');
                spaces=OUT;
            }
        } else {
            putchar(c);
            spaces=IN;
        }
    }
}