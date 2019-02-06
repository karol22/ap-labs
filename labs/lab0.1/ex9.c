#include <stdio.h>
int main()
{
    int c;
    int last_is_blank=0;
    while((c=getchar()) != EOF){
        if(c==' '){
            if(last_is_blank==0){
                putchar(c);
                last_is_blank=1;
            }
        }else {
            putchar(c);
            last_is_blank=0;
        }
    }
}