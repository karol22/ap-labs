#include <stdio.h>

int main(int argc, char **argv){
    char* a = argv[1];
    char* b = argv[2];
    printf("Initial Lenght      : %d\n", mystrlen(a));
    char* str = (char*)calloc((mystrlen(a)+mystrlen(b)+1), 1);
    stradd(str,a);
    stradd(str,b);
    printf("New String          : %s\n", str);
   
    int x = mystrfind(str, argv[3]);
    if(x){
        printf("SubString was found : yes\n", str);
    }else{
        printf("SubString was found : no\n", str);
    }

    return 0;
}