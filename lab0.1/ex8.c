#include <stdio.h>
int main()
{
    int c;
    int blanks=0, tabs=0, newlines=0;
    while((c=getchar()) != EOF){
        if(c==' ') blanks++;
        if(c=='\t') tabs++;
        if(c=='\n') newlines++;
    }
    printf("There are %d blanks, %d tabs and %d newlines.\n", blanks, tabs, newlines);
}